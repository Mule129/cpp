#include "tetromino.h"
#include "console/console.h"

Tetromino::Tetromino(std::string name, int size, std::string shape) {
    name_ = name;
    size_ = size;
    int index = 0;
    bool origin[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (shape[index] == 'X') {
                shape_[i][j] = false;
            } else {
                shape_[i][j] = true;
            }
            
            index++;
        }
    }

    original_ = this;
}


Tetromino Tetromino::rotatedCW() {
    Tetromino rotate(name_, size_, "");
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            rotate.shape_[i][j] = shape_[size_ - j - 1][i];
        }
    }
    rotate.original_ = original_;

    return rotate;
}

Tetromino Tetromino::rotatedCCW() {
    Tetromino rotate(name_, size_, "");
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            rotate.shape_[i][j] = shape_[j][size_ - i - 1];
        }
    }
    rotate.original_ = original_;

    return rotate;
}

void Tetromino::drawAt(std::string s, int x, int y) {
    int index = 0;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (check(i, j)) {
                console::draw(x+i + 1, y+j + 1, s);
            }
            
            index++;
        }
    }
}


Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("O", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");
