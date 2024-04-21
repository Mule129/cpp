#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <iomanip>

#include "tetromino.h"
#include "console/console.h"

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
  std::chrono::system_clock::time_point startTime;
  std::chrono::system_clock::time_point endTime;

  bool holdCheck;

  int delay = 0;
  int x, y;

  bool exit;

  Tetromino thisDump = Tetromino::I;
  Tetromino holdDump = Tetromino::I;
  Tetromino *thisTetromino = nullptr;
  Tetromino *nextTetromino = nullptr;
  Tetromino *holdTetromino = nullptr;

  // init tromino pos
  void initTrominoPos();
  
  // create tromino
  Tetromino *createTetromino(int rand);

  // input controller  
  void inputController();

  // return margin from tromino
  // way: left = 1, right = 2, top = 3, bottom = 4
  int marginXY(int way);

  // rand int return
  int randInt();

  // return board x value (x + 1)
  int boardX();

  // return board y value (y + 1)
  int boardY();

  // return tromino real x pos
  int realX();

  // return tromino real y pos
  int realY();

  // check under block y pos for first x and first y
  // check tromino x, y pos
  //
  // if tromino size != tromino real size:
  //    return gap from tromino real size and board block
  //
  // this calculate result is x, y standard pos 
  // (x + tromino real x size, y + tromino real y size)
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

  std::string getTime();

  // draw
  // draw Board
  void drawBoard();

  // draw time
  void drawTime();

  // draw score(time, line clear)
  void drawScore();

  // draw tromino
  void drawTromino(int x, int y);

  // draw next tromino for int x and int y (0, 0)
  void drawNextTromino(int x, int y);

  // draw hold tromino
  void drawHoldTromino(int x, int y);

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