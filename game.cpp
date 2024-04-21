#include "game.h"


Game::Game() {
    score = 0;
    startTime = std::chrono::system_clock::now();

    exit = false;
    
    thisTetromino = createTetromino(randInt());
    nextTetromino = createTetromino(randInt());
    holdTetromino = nullptr;

    initTrominoPos();
}

void Game::initTrominoPos() {
    x = BOARD_WIDTH/2 - thisTetromino->size()/2;
    y = 2 + thisTetromino->size()/2;
}

Tetromino *Game::createTetromino(int rand) {
    switch (rand)
    {
    case 0:
        return &Tetromino::I;
    case 1:
        return &Tetromino::O;
    case 2:
        return &Tetromino::T;
    case 3:
        return &Tetromino::S;
    case 4:
        return &Tetromino::Z;
    case 5:
        return &Tetromino::J;
    case 6:
        return &Tetromino::O;
    };
    return nullptr;
}

void Game::inputController() {
    if (console::key(console::K_ESC)) {
        exit = true;
    }

    if (console::key(console::K_DOWN)) {
        delay *= 2;  // delay limit delete
    } if (console::key(console::K_LEFT) && x > 0) {
        x--;
    } if (console::key(console::K_RIGHT) && x < BOARD_WIDTH - realX()) {
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


int Game::realX() {
    int x = 0;
    for (int i = 0; i < thisTetromino->size(); i++) {
        for (int j = 0; j < thisTetromino->size(); j++) {
            if (thisTetromino->check(i, j) && x < i) {
                x = i;
            } 
        }
    }
    
    return x;
}

int Game::realY() {
    int y = 0;
    for (int i = 0; i < thisTetromino->size(); i++) {
        for (int j = 0; j < thisTetromino->size(); j++) {
            if (thisTetromino->check(i, j) && y < j) {
                y = j;
            } 
        }
    }

    return y;
}

int Game::randInt() {
    return rand() % 7;
}

int Game::underBlock() {
    int underY = BOARD_HEIGHT;
    bool status = false;

    for (int localY = y; localY < BOARD_HEIGHT; localY++) {
        for (int localX = x; localX < thisTetromino->size(); localX++) {
            
        }

        if (!status) {
            break;
        }
    }
    
    return underY;
}

void Game::nextBlock() {
    initTrominoPos();

    *thisTetromino = *nextTetromino;
    nextTetromino = createTetromino(randInt());
}

void Game::holdBlock() {
    Tetromino hold = Tetromino::I;
    if (holdTetromino == nullptr) {
        holdTetromino = thisTetromino;
        thisTetromino = createTetromino(randInt());
    } else if (holdCheck == false) {
        hold = *thisTetromino;
        thisTetromino = holdTetromino;
        holdTetromino = &hold;
        holdCheck = true;
    } else {
        return;
    }
    
    initTrominoPos();
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
    if (board_[x][y]) {  // TODO: use Tetromino::check
        addBlock();
        nextBlock();
    }
    if (y >= BOARD_HEIGHT) {
        addBlock();
        nextBlock();
    }
    if (underBlock() == 0) {
        exit = true;
    }
    clearBlock();
}

void Game::addBlock() {
    for (int i = 0; i < thisTetromino->size(); i++) {
        for (int j = 0; j < thisTetromino->size(); j++) {
            if (thisTetromino->check(i, j)) {
                board_[x - realX() + i + 1][(y - realY() + j - 1)] = true;
            }
        }
    }

    holdCheck = false;
}

void Game::drawBoard() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if (board_[i][j]) {
                console::draw(i + 1, j + 1, BLOCK_STRING);
            } else {
                console::draw(i + 1, j + 1, " ");
            }
        }
    }
}

void Game::drawTromino(int x, int y) {
    thisTetromino->drawAt(
        SHADOW_STRING, 
        x, 
        underBlock() - thisTetromino->size()
    );

    thisTetromino->drawAt(
        BLOCK_STRING, 
        x, 
        y - thisTetromino->size()
    );
}

void Game::drawNextTromino(int x, int y) {
    console::drawBox(BOARD_WIDTH + 3, 0, BOARD_WIDTH + 3 + 5, 5); 
    console::draw(BOARD_WIDTH + 4, 0, "Next");
    nextTetromino->original()->drawAt(BLOCK_STRING, BOARD_WIDTH + 3 + (nextTetromino->original()->size() % 4 / 2), (nextTetromino->original()->size() % 4 / 2));
}

void Game::drawHoldTromino(int x, int y) {
    console::drawBox(BOARD_WIDTH + 3 + 6, 0, BOARD_WIDTH + 3 + 6 + 5, 5); 
    console::draw(BOARD_WIDTH + 10, 0, "Hold");
    if (holdTetromino) {
        holdTetromino->original()->drawAt(BLOCK_STRING, BOARD_WIDTH + 3 + 6 + (holdTetromino->size() % 4 / 2), (holdTetromino->size() % 4 / 2));
    }
}

std::string Game::getTime() {
    endTime = std::chrono::system_clock::now();
    auto duration = endTime - startTime;
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    
    auto minutes = millis / (60 * 1000);
    millis %= 60 * 1000;
    auto seconds = millis / 1000;
    millis %= 1000;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds << "." << std::setw(2) << millis/10;
    return oss.str();
}

void Game::drawTime() {
    console::draw(0, BOARD_HEIGHT + 3, "time: "+getTime());
}

void Game::drawScore() {
    console::draw(0, BOARD_HEIGHT + 2, std::to_string(LINES - score)+" lines left");
}


// public function

// update game view
void Game::update() {    
    inputController();
    checkBlock();
    console::draw(BOARD_WIDTH+2, BOARD_HEIGHT, "x:"+std::to_string(x) + " y:"+std::to_string(y) + " s:"+std::to_string(underBlock()));

    if (delay >= DROP_DELAY) {
        y++;
        delay = 0;
        console::log(std::to_string(underBlock()) + std::to_string(x));
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
    drawHoldTromino(BOARD_WIDTH, 1);
    drawNextTromino(BOARD_WIDTH, 1);
}

// 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit() {
    if (score >= 40) {
        console::draw(4, BOARD_HEIGHT/2, "You Win");
        console::draw(2, BOARD_HEIGHT/2+1, getTime());
        exit = true;
    }
    return exit;
}

  