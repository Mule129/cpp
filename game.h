#ifndef GAME_H
#define GAME_H

#include "tetromino.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  bool board_[BOARD_WIDTH][BOARD_HEIGHT] = {false};

  int score;
  time_t startTime;

  bool holdCheck;

  int delay = 0;
  int x, y;

  bool exit;

  Tetromino dump = Tetromino::I;
  Tetromino *thisTetromino = &Tetromino::I;
  Tetromino *nextTetromino = &Tetromino::I;
  Tetromino *holdTetromino = &Tetromino::I;

  // create tromino
  Tetromino *createTetromino(int rand);

  // input controller  
  void inputController();

  // rand int return
  int randInt();

  // return board x value (x + 1)
  int boardX();

  // return board y value (y + 1)
  int boardY();

  // calculate tromino size
  int calculateTromino();

  // check under block y pos for first x and first y
  int underBlock();

  // check full block and delete block
  void clearBlock();

  // make Tromino
  void makeTromino();

  // check block pos
  void checkBlock();

  // add this block for board_[x][y]
  void addBlock();

  // update next block
  void nextBlock();

  // hold block
  void holdBlock();

  // draw
  // draw Board
  void drawBoard();

  // draw time
  void drawTime();

  // draw score(time, line clear)
  void drawScore();

  // draw tromino
  void drawTromino(int x, int y);

  // draw next tromino
  void drawNextTromino();

  // draw hold tromino
  void drawHoldTromino();

public:
  // 게임의 한 프레임을 처리한다.
  void update();

  // 게임 화면을 그린다.
  void draw();

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
  bool shouldExit();

  Game();
};
#endif