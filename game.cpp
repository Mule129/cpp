#include <ctime>

#include "game.h"
#include "console/console.h"
#include "tetromino.h"


Game::Game() {
    score = 0;
    startTime = time(NULL);

    exit = false;
    
    thisTetromino = createTetromino(randInt());
    nextTetromino = createTetromino(randInt());
    holdTetromino = nullptr;

    x = BOARD_WIDTH/2 + thisTetromino->size()/2;
    y = 2 + thisTetromino->size()/2;
}

Tetromino *Game::createTetromino(int rand) {
    switch (rand)
    {
    case 0:
        dump = Tetromino::I;
        return &dump;
    case 1:
        dump = Tetromino::O;
        return &dump;
    case 2:
        dump = Tetromino::T;
        return &dump;
    case 3:
        dump = Tetromino::S;
        return &dump;
    case 4:
        dump = Tetromino::Z;
        return &dump;
    case 5:
        dump = Tetromino::J;
        return &dump;
    case 6:
        dump = Tetromino::O;
        return &dump;
    };
    return &dump;
}

void Game::inputController() {
    if (console::key(console::K_ESC)) {
        exit = true;
    }

    if (console::key(console::K_DOWN)) {
        delay *= 2;  // delay limit delete
    } if (console::key(console::K_LEFT) && x > 0 && board_[x-1][y] == false) {
        x--;
    } if (console::key(console::K_RIGHT) && x < BOARD_WIDTH-1) {
        x++;
    } if (console::key(console::K_UP)) {
        y = underBlock();
    }

    if (console::key(console::K_Z)) {
        dump = thisTetromino->rotatedCCW();
    } else if (console::key(console::K_X)) {
        dump = thisTetromino->rotatedCW();
    } else if (console::key(console::K_SPACE)) {
        holdBlock();
    }

    thisTetromino = &dump;
}

int Game::boardX() {
    return x-1;
}

int Game::boardY() {
    return y-1;
}

int Game::calculateTromino() {
    return thisTetromino->size()/2;
}

int Game::randInt() {
    return rand() % 7;
}

int Game::underBlock() {
    int under_y = BOARD_HEIGHT;
    for (int y = BOARD_HEIGHT; y > 0; y--) {
        for (int x = 0; x < thisTetromino->size(); x++) {
            if (board_[this->x + x][this->y] && under_y > y) {
                under_y = y;
            }
        }
    }

    return under_y;
}

void Game::nextBlock() {
    x = BOARD_WIDTH/2 + calculateTromino();
    y = 2 + calculateTromino();

    thisTetromino = nextTetromino;
    nextTetromino = createTetromino(randInt());
}

void Game::holdBlock() {
    Tetromino hold = Tetromino::I;
    if (holdTetromino == nullptr) {
        holdTetromino = thisTetromino;
        thisTetromino = createTetromino(randInt());
    } else {
        hold = *thisTetromino;
        thisTetromino = holdTetromino;
        holdTetromino = &dump;
        holdCheck = true;
    }
    
    
}

void Game::clearBlock() {
    bool lineCheck = true;
    for (int i = BOARD_HEIGHT-1; i >= 0; i--) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (!board_[j][i]) {
                lineCheck = false;
                break;
            }
        }
        if (lineCheck == true) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                for (int h = i; h > 0; h--) {
                    board_[j][h] = board_[j][h-1];
                }
            }
            score++;
            i--;
        }

        lineCheck = true;
    }
}


void Game::checkBlock() {  // TODO: 다음 클록에 넘어가기 직전 체크해야한다
    if (board_[x+1][y+1]) {  // TODO: use Tetromino::check
        addBlock();
        nextBlock();
    }
    if (y >= BOARD_HEIGHT) {
        addBlock();
        nextBlock();
    }
    clearBlock();
}

void Game::addBlock() {
    for (int i = 0; i < thisTetromino->size(); i++) {
        for (int j = 0; j < thisTetromino->size(); j++) {
            if (thisTetromino->check(i, j)) {
                board_[x + i + 1][(y - thisTetromino->size() + j) + 1] = true;
            }
        }
    }

    holdCheck = false;
}

void Game::drawBoard() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if (board_[i][j]) {
                console::draw(i+1, j+1, BLOCK_STRING);
            } else {
                console::draw(i+1, j+1, " ");
            }
        }
    }
}

void Game::drawTromino(int x, int y) {
    thisTetromino->drawAt(
        SHADOW_STRING, 
        x - calculateTromino(), 
        underBlock() - calculateTromino() - 1
    );

    thisTetromino->drawAt(
        BLOCK_STRING, 
        x - calculateTromino(), 
        y - calculateTromino()
    );
}

void Game::drawNextTromino() {
    console::drawBox(BOARD_WIDTH + 3, 0, BOARD_WIDTH + 3 + 5, 5); 
    console::draw(BOARD_WIDTH + 4, 0, "Next");
    nextTetromino->original()->drawAt(BLOCK_STRING, BOARD_WIDTH + 4 + (nextTetromino->original()->size() % 4 / 2), 1 + (nextTetromino->original()->size() % 4 / 2));
}

void Game::drawHoldTromino() {
    console::drawBox(BOARD_WIDTH + 3 + 6, 0, BOARD_WIDTH + 3 + 6 + 5, 5); 
    console::draw(BOARD_WIDTH + 10, 0, "Hold");
    if (holdTetromino) {
        holdTetromino->original()->drawAt(BLOCK_STRING, BOARD_WIDTH+4 + 6 + (holdTetromino->size() % 4 / 2), 1 + (holdTetromino->size() % 4 / 2));
    }
}

void Game::drawTime() {
    time_t endTime = time(NULL);
    console::draw(0, BOARD_HEIGHT + 3, "time: " + std::to_string(endTime - startTime));
}

void Game::drawScore() {
    console::draw(0, BOARD_HEIGHT + 2, std::to_string(LINES - score)+" lines left");
}


// public function

// update game view
void Game::update() {    
    inputController();
    checkBlock();
    console::draw(BOARD_WIDTH+2, BOARD_HEIGHT, "x:"+std::to_string(x) + " y:"+std::to_string(y) + " s:"+std::to_string(thisTetromino->size()));

    if (delay >= DROP_DELAY) {
        y++;
        delay = 0;
        console::log("test");
    } else {
        delay++;
    }
    
}


// 게임 화면을 그린다.
void Game::draw() {
    console::drawBox(0, 0, BOARD_WIDTH+1, BOARD_HEIGHT+1);

    drawBoard();
    drawTromino(x, y);
    drawScore();
    drawTime();
    drawHoldTromino();
    drawNextTromino();
}

// 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit() {
    return exit;
}

  