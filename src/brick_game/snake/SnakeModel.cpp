#ifndef SNAKE_MODEL_CPP
#define SNAKE_MODEL_CPP


#include "SnakeModel.h"


    /// @brief устанавливает направление (только под прямым углом)
    /// @param newDirection 
    void SnakeModel::setDirection(Direction newDirection){
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
        if (newHead == food) eatFood();
        else snake.pop_back();
    }

    /// @brief ушаем еду: обновляем счет и шаманим новую еду
    void SnakeModel::eatFood(){
        increaseScore();
        addFood();
    }

    /// @brief обновляем счет: обновляем уровень и рекорд
    void SnakeModel::increaseScore(){
        score++;
        increaseLevel();
        increaseHighScore();
    }

    /// @brief обновляем уровень
    void SnakeModel::increaseLevel(){
        if (level < 10 && score % 5 == 0) level++;
    }

    /// @brief обновляем рекорд
    void SnakeModel::increaseHighScore(){
        if (score > highScore) highScore = score;
    }

    /// @brief обновляем модель на с учетом команды пользователя (FSM)
    /// @param userAction 
    void SnakeModel::updateModel(UserAction userAction, bool* flagExit) {
        if (state == GameState::Paused){
            if (userAction == UserAction::Pause) state = GameState::Playing;
            if (userAction == UserAction::Terminate) state = GameState::GameOver;
        } else if (state == GameState::Playing){
            if (userAction == UserAction::Pause) state = GameState::Paused;
            if (userAction == UserAction::Terminate) state = GameState::GameOver;
            if (userAction == UserAction::Up) updateSnake(Direction::Up);
            if (userAction == UserAction::Right) updateSnake(Direction::Right);
            if (userAction == UserAction::Down) updateSnake(Direction::Down);
            if (userAction == UserAction::Left) updateSnake(Direction::Left);
            if (userAction == UserAction::Action) updateSnake(direction);
        }
        *flagExit = state == GameState::GameOver;
    }

    /// @brief конвертирует сишное перечисление команды пользователя в перечисление-класс
    /// @param src сишное значение
    /// @return перечисление-класс
    UserAction SnakeModel::convertUserAction(UserAction_t src) {
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

    // /// @brief 
    // void SnakeModel::newGame(){
    //     initGame();
    //     state = GameState::Playing;
    // }

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
    void SnakeModel::startGame(){
        loadRecord();
        initGame();
    }

    /// @brief заканчиваем игру: записываем рекорд
    void SnakeModel::exitGame(){
        saveRecord();
        state = GameState::GameOver;
    }

    /// @brief обновляем модель
    /// @param newDirection новое направление
    void SnakeModel::updateSnake(Direction newDirection){
        setDirection(newDirection);
        std::pair<int, int> newHead = getNewHead();
        if (!checkIsCollapse(newHead)){ 
            moveSnake(newHead);
            if (score == height * width) state = GameState::GameOver;
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
    Direction SnakeModel::getDirection() const {
        return direction;
    }

    /// @brief возвращает вектор со змеей
    /// @return вектор
    const std::vector<std::pair<int, int>>& SnakeModel::getSnake() const {
        return snake;
    }

    /// @brief возвращает координаты еды
    /// @return пара координат
    std::pair<int, int> SnakeModel::getFood() const {
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
    /// @param gameInfo указатель на структуру
    void SnakeModel::getGameInfo(GameInfo_t* gameInfo){
        clearField(gameInfo);
        saveSnake(gameInfo);
        saveFood(gameInfo);
        gameInfo->score = score;
        gameInfo->high_score = highScore;
        gameInfo->level = level;
        gameInfo->pause = state == GameState::Paused;
        gameInfo->speed = getSpeed();
    }

    /// @brief возвращает значение скорости (задержка в миллисекундах)
    /// @return задержка в миллисекундах
    int SnakeModel::getSpeed(){
        return 400 - level * 30;
    }

    /// @brief обновляет игровое поле (field) в структуре для отображения 
    /// @param gameInfo указатель на структуру
    void SnakeModel::saveSnake(GameInfo_t* gameInfo){
        for (const std::pair<int, int>& segment : snake) {
            gameInfo->field[segment.second][segment.first] = 1;
        }
    }

    /// @brief обновляет поле next в структуре для отображения (для отображения еды)
    /// @param gameInfo указатель на структуру
    void SnakeModel::saveFood(GameInfo_t* gameInfo){
        gameInfo->field[food.second][food.first] = 1;
    }

    /// @brief очищает игровое поле (field) в структуре на отображение
    /// @param gameInfo указатель на структуру
    void SnakeModel::clearField(GameInfo_t* gameInfo){
        for (int y = 0; y < BOARD_HEIGHT; y++){
            for (int x = 0; x < BOARD_WIDTH; x++){
                gameInfo->field[y][x] = 0;
            }
        }
    }


    // /// @brief 
    // /// @return 
    // PlayerState_t SnakeModel::getState(){
    //     PlayerState_t result;
    //     if (state == GameState::Playing) result = sPlaying;
    //     if (state == GameState::Win) result = sWin;
    //     if (state == GameState::Exit) result = sExitGame;
    //     if (state == GameState::GameOver) result = sGameOver;
    //     if (state == GameState::Paused) result = sPause;
    //     return result;
    // }


#endif // SNAKE_MODEL_CPP