#include "board.h"
#include <stdlib.h>

int main() {
    Board board;
    bool won = false;
    int row, col, remove;
    int player = 1;

    while (!won) {
        row = rand() % 10;
        col = rand() % 10;
        remove = rand() % 10;

        board.play(player, row, col, remove < 2);
        won = board.won(player);
        player = (player % 2) + 1;
    }
    board.show();
}
