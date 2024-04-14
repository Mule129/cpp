#include "game.h"
#include "console/console.h"
#include "tetromino.h"


Game::Game() {
    x = BOARD_WIDTH/2;
    y = 0;

    score = 0;
    // TODO: Create Tromino
}

void Game::inputController() {
    if (console::key(console::K_DOWN)) {
        delay *= 2;
    } if (console::key(console::K_LEFT) && x > 0 && board_[x-1][y] == false) {
        x--;
    } if (console::key(console::K_RIGHT) && x < BOARD_WIDTH-1) {
        x++;
    } if (console::key(console::K_UP)) {
        y = BOARD_HEIGHT;
        // TODO: goto Tromino result position.
    }
}

void Game::nextBlock() {
    x = BOARD_WIDTH/2;
    y = 0;

    // TODO: Tromino Create and Delete
}

void Game::clearBlock() {
    bool linCheck = true;
    for (int i = BOARD_HEIGHT-1; i >= 0; i--) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (!board_[j][i]) {
                linCheck = false;
                break;
            }
        }
        if (linCheck == true) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                for (int h = i; h > 0; h--) {
                    board_[j][h] = board_[j][h-1];  // TODO: check many line
                }
            }
            score++;
            i--;
        }

        linCheck = true;
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
    clearBlock();
}

void Game::addBlock() {
    board_[x][y-1] = true;
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
    console::draw(x+1, y+1, BLOCK_STRING);

    // TODO: use Tromino::drawAt(string, x, y)
}

void Game::drawScore() {
    console::draw(0, BOARD_HEIGHT + 2, std::to_string(LINES - score)+" lines left");
    console::draw(0, BOARD_HEIGHT + 3, std::to_string(11)+":"+std::to_string(48)+"."+std::to_string(10));
}


// public function

// update game view
void Game::update() {    
    inputController();
    checkBlock();
    if (delay >= DROP_DELAY) {
        y++;
        delay = 0;
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
}

// 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit() {
    return false;
}

  