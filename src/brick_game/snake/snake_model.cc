#include "snake_model.h"

namespace s21 {

    /// @brief устанавливает направление (только под прямым углом)
    /// @param newDirection новое направление
    void SnakeModel::update_direction(Direction newDirection){
        direction = static_cast<int>(direction) % 2 == static_cast<int>(newDirection) % 2 ? direction : newDirection;
    }

    /// @brief опредляет новое положение головы на следующем шаге как шах от текущего
    /// @return новый сегмент (пара координат)
    std::pair<int, int>  SnakeModel::getNewHead(){
        std::pair<int, int>  newHead = snake.front();
        switch (direction) {
            case Direction::Up:    newHead.second--; break;
            case Direction::Down:  newHead.second++; break;
            case Direction::Left:  newHead.first--;  break;
            case Direction::Right: newHead.first++;  break;
        }    
        return newHead;    
    }

    /// @brief проверяет столкновение с собой или стенками
    /// @param newHead новая голова (сегмент)
    /// @return истина - столкновение неизбежно
    bool SnakeModel::checkIsCollapse(std::pair<int, int>  newHead){
        return (newHead.first < 0 || newHead.first >= width || newHead.second < 0 || newHead.second >= height ||
            std::find(snake.begin(), snake.end(), newHead) != snake.end());
    }

    /// @brief движение змеи: без еды отрезаем хвост
    /// @param newHead новая голова (сегмент)
    void SnakeModel::moveSnake(std::pair<int, int>  newHead){
        snake.insert(snake.begin(), newHead);
        if (newHead == food) eat_food();
        else snake.pop_back();
    }

    /// @brief ушаем еду: обновляем счет и шаманим новую еду
    void SnakeModel::eat_food(){
        update_score();
        addFood();
    }

    /// @brief обновляем счет: обновляем уровень и рекорд
    void SnakeModel::update_score(){
        score++;
        updateLevel();
        updateHighScore();
    }

    /// @brief обновляем уровень
    void SnakeModel::updateLevel(){
        if (level < 10 && score % 5 == 0) level++;
    }

    /// @brief обновляем рекорд
    void SnakeModel::updateHighScore(){
        if (score > highScore) highScore = score;
    }

    /// @brief обновляем модель на с учетом команды пользователя (FSM)
    /// @param user_action действие пользователя
    void SnakeModel::update_model(UserAction user_action, bool* flag_exit) {
        if (state == GameState::Paused){
            if (user_action == UserAction::Pause) state = GameState::Playing;
            if (user_action == UserAction::Terminate) state = GameState::GameOver;
        } else if (state == GameState::Playing){
            if (user_action == UserAction::Pause) state = GameState::Paused;
            if (user_action == UserAction::Terminate) state = GameState::GameOver;
            if (user_action == UserAction::Up) update_snake(Direction::Up);
            if (user_action == UserAction::Right) update_snake(Direction::Right);
            if (user_action == UserAction::Down) update_snake(Direction::Down);
            if (user_action == UserAction::Left) update_snake(Direction::Left);
            if (user_action == UserAction::Action) update_snake(direction);
        }
        *flag_exit = (state == GameState::GameOver || state == GameState::Win);
    }

    /// @brief конвертирует сишное перечисление команды пользователя в перечисление-класс
    /// @param src сишное значение
    /// @return перечисление-класс
    UserAction SnakeModel::convert_user_action(UserAction_t src) {
        switch (src) {
            case Start: return UserAction::Start;
            case Pause: return UserAction::Pause;
            case Terminate: return UserAction::Terminate;
            case Left: return UserAction::Left;
            case Right: return UserAction::Right;
            case Up: return UserAction::Up;
            case Down: return UserAction::Down;
            case Action: return UserAction::Action;
            case NUM_ACTIONS: return UserAction::NUM_ACTIONS;
            default: return UserAction::Start;
        }
    }

    /// @brief сбрасывает до начального состояния параметры модели
    void SnakeModel::initGame(){
        snake.clear();
        level = 0;
        score = 0;
        state = GameState::Playing;
        direction = Direction::Right;
        initSnake();
        addFood();
    }

    /// @brief начинаем игру: инициализируем параметы, загружаем рекорд
    void SnakeModel::start_game(){
        loadRecord();
        initGame();
    }

    /// @brief заканчиваем игру: записываем рекорд
    void SnakeModel::exit_game(){
        saveRecord();
        state = GameState::GameOver;
    }

    /// @brief обновляем модель
    /// @param newDirection новое направление
    void SnakeModel::update_snake(Direction newDirection){
        update_direction(newDirection);
        std::pair<int, int> newHead = getNewHead();
        if (!checkIsCollapse(newHead)){ 
            moveSnake(newHead);
            if (score == height * width) state = GameState::Win;
        } else state = GameState::GameOver;
    }

    /// @brief загружаем рекорд из файла
    void SnakeModel::loadRecord() {
    FILE *p_file = fopen(RECORD_SNAKE_FILE_NAME, "rb");
    if (!!p_file) {
        fread(&highScore, sizeof(int), 1, p_file);
        fclose(p_file);
    } else highScore = 0;
    };

    /// @brief записываем рекород в файл
    void SnakeModel::saveRecord() {
    FILE *p_file = fopen(RECORD_SNAKE_FILE_NAME, "wb");
    if (!!p_file) {
        fwrite(&highScore, sizeof(int), 1, p_file);
        fclose(p_file);
    };
    };  

    /// @brief возвращает текущее направление
    /// @return текущее направление
    Direction SnakeModel::get_direction() const {
        return direction;
    }

    /// @brief возвращает вектор со змеей
    /// @return вектор
    const std::vector<std::pair<int, int>>& SnakeModel::get_snake() const {
        return snake;
    }

    /// @brief возвращает координаты еды
    /// @return пара координат
    std::pair<int, int> SnakeModel::get_food() const {
        return food;
    }


    /// @brief добавляет еду (случайно)
    void SnakeModel::addFood() {
        if (score < height * width){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> disX(0, width - 1);
            std::uniform_int_distribution<> disY(0, height - 1);

            do {
                food = {disX(gen), disY(gen)};
            } while (std::find(snake.begin(), snake.end(), food) != snake.end());
        }
    }

    /// @brief возвращает начальное состояние змейки
    void SnakeModel::initSnake(){
        snake.push_back({3, height / 2});
        snake.push_back({2, height / 2});
        snake.push_back({1, height / 2});
        snake.push_back({0, height / 2});
    }


    /// @brief обновляет структуру для отображения
    /// @param game_info указатель на структуру
    void SnakeModel::get_game_info(GameInfo_t* game_info){
        clearField(game_info);
        saveSnake(game_info);
        saveFood(game_info);
        game_info->score = score;
        game_info->high_score = highScore;
        game_info->level = level;
        game_info->pause = state == GameState::Paused;
        game_info->speed = get_speed();
    }

    /// @brief возвращает значение скорости (задержка в миллисекундах)
    /// @return задержка в миллисекундах
    int SnakeModel::get_speed(){
        return 400 - level * 30;
    }

    /// @brief обновляет игровое поле (field) в структуре для отображения 
    /// @param game_info указатель на структуру
    void SnakeModel::saveSnake(GameInfo_t* game_info){
        for (const std::pair<int, int>& segment : snake) {
            game_info->field[segment.second][segment.first] = 1;
        }
    }

    /// @brief обновляет поле next в структуре для отображения (для отображения еды)
    /// @param game_info указатель на структуру
    void SnakeModel::saveFood(GameInfo_t* game_info){
        game_info->field[food.second][food.first] = 1;
    }

    /// @brief очищает игровое поле (field) в структуре на отображение
    /// @param game_info указатель на структуру
    void SnakeModel::clearField(GameInfo_t* game_info){
        for (int y = 0; y < BOARD_HEIGHT; y++){
            for (int x = 0; x < BOARD_WIDTH; x++){
                game_info->field[y][x] = 0;
            }
        }
    }
    /// @brief отрабатывает срабатывание по таймеру
    /// @param flag_exit указатель на флаг выхода из игры
    void SnakeModel::update_model_by_timer(bool* flag_exit){
        update_model(UserAction::Action, flag_exit);
    }

    /// @brief возвращает текущее состояние игры
    /// @return state - текущее состояние (GameState)
    GameState SnakeModel::get_state() const {
        return state;
    }

    /// @brief возвращает текущий уровень
    /// @return текущий уровнь (int)
    int SnakeModel::get_level() const{
        return level;
    }

    /// @brief возвращает текущий счет
    /// @return текущий счет (int)
    int SnakeModel::get_score() const{
        return score;
    };

    /// @brief возвращает рекорд
    /// @return рекорд (int)
    int SnakeModel::get_high_score() const{
        return highScore;
    };

    /// @brief добавить еду в указанном месте
    /// @param newFood (pair<int, int> ) - место для расположения еды
    void SnakeModel::set_food(std::pair<int, int> newFood) {
    food = newFood;
    }

} // namespace s21

