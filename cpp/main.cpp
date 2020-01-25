#include "board.h"
#include <stdlib.h>

int main() {
    Board board;
    bool won = false;
    int row, col;
    while (!won) {
        row = rand() % 10;
        col = rand() % 10;

        board.play(1, row, col);
        won = board.won(1);
    }
    board.show();
}
