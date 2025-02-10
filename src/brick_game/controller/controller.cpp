// #include "controller.h"

// // Статический объект модели
// static SnakeModel* modelSnake = nullptr;
// static Parameters_t* modelTetris = nullptr;
// static FiniteStateMachine_t fsm_;

// #ifndef USE_QT
// extern "C" {
//     void mainLoop();
// }

// extern "C" void updateModel(UserAction_t userActionSource, bool hold, bool* flagExit, MenuItem_t selectedGame) {
//     if (selectedGame == MENU_SNAKE) {
//         if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
//         UserAction userAction = modelSnake->convertUserAction(userActionSource);
//         modelSnake->updateModel(userAction, flagExit);
//     }
//     if (selectedGame == MENU_TETRIS) {
//         updateModelTetris(userActionSource, hold, flagExit, modelTetris, &fsm_);
//     }
// }

// extern "C" void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame) {
//     if (selectedGame == MENU_SNAKE) {
//         if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
//         modelSnake->getGameInfo(gameInfo);
//     }
//     if (selectedGame == MENU_TETRIS) getGameInfoTetris(gameInfo, modelTetris);
// }

// extern "C" void startGame(MenuItem_t selectedGame) {
//     if (selectedGame == MENU_SNAKE) {
//         if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
//         modelSnake->startGame();
//     }
//     if (selectedGame == MENU_TETRIS) {
//         initModelTetris(&modelTetris);
//         initFSM(&fsm_);
//         startTetrisGame(modelTetris);
//     }
// }

// extern "C" void exitGame(MenuItem_t selectedGame) {
//     if (selectedGame == MENU_SNAKE) {
//         modelSnake->exitGame();
//     }
//     if (selectedGame == MENU_TETRIS) cleanupParameters(&modelTetris);
// }

// extern "C" void startApp() {
//     mainLoop();
// }
// #endif // USE_QT

// #ifdef USE_QT
// Controller::Controller(QObject *parent) : QObject(parent) {
//     // Инициализация моделей, если нужно
// }

// void Controller::handleUserAction(UserAction_t userAction) {
//     bool hold = false; // Для Qt удержание не используется
//     updateModel(userAction, hold, &flagExit, selectedGame);
// }

// void Controller::handleRequestGameInfo() {
//     GameInfo_t gameInfo;
//     getGameInfo(&gameInfo, selectedGame);
//     emit gameInfoUpdated(gameInfo);
// }
// #endif // USE_QT


#include "controller.h"

// Статические объекты моделей
static SnakeModel* modelSnake = nullptr;
static Parameters_t* modelTetris = nullptr;
static FiniteStateMachine_t fsm_;

#ifndef USE_QT
extern "C" {
    void mainLoop();
}

extern "C" void updateModel(UserAction_t userActionSource, bool hold, bool* flagExit, MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE) {
        if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        UserAction userAction = modelSnake->convertUserAction(userActionSource);
        modelSnake->updateModel(userAction, flagExit);
    }
    if (selectedGame == MENU_TETRIS) {
        updateModelTetris(userActionSource, hold, flagExit, modelTetris, &fsm_);
    }
}

extern "C" void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE) {
        if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        modelSnake->getGameInfo(gameInfo);
    }
    if (selectedGame == MENU_TETRIS) getGameInfoTetris(gameInfo, modelTetris);
}

extern "C" void startGame(MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE) {
        if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        modelSnake->startGame();
    }
    if (selectedGame == MENU_TETRIS) {
        initModelTetris(&modelTetris);
        initFSM(&fsm_);
        startTetrisGame(modelTetris);
    }
}

extern "C" void exitGame(MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE) {
        modelSnake->exitGame();
    }
    if (selectedGame == MENU_TETRIS) cleanupParameters(&modelTetris);
}

extern "C" void startApp() {
    mainLoop();
}
#endif // USE_QT

#ifdef USE_QT
Controller::Controller(QObject *parent) : QObject(parent) {
    // Инициализация моделей, если нужно
}

void Controller::handleUserAction(UserAction_t userAction) {
    bool hold = false; // Для Qt удержание не используется
    updateModel(userAction, hold, &flagExit, selectedGame);
}

void Controller::handleRequestGameInfo() {
    GameInfo_t gameInfo;
    getGameInfo(&gameInfo, selectedGame);
    emit gameInfoUpdated(gameInfo);
}
#endif // USE_QT