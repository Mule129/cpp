#include "tetromino.h"

Tetromino::Tetromino(std::string name, int size, std::string shape) {
    name_ = name;
    size_ = size;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            shape_[i][j] = shape[i*4+j];
        }
    }
}

// Tetromino Tetromino::rotatedCW() {
    
// }
