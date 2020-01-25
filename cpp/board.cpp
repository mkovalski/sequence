#include <iostream>
#include <map>
#include <vector>
#include "board.h"

Board::Board() {
    cache[1] = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>();
    cache[2] = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>();
    cache[3] = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>();
    reset();
};

void Board::reset() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            board[i][j] = 0;
        }
    }

    board[0][0] = 255;
    board[width-1][0] = 255;
    board[0][height-1] = 255;
    board[width-1][height-1] = 255;
    
    for (auto const& element : cache) {
        cache[element.first].clear();
    }

}

void Board::show() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

bool Board::corner(int row, int col) {
    if ((row == 0 && col == 0) ||
        (row == 0 && col == width - 1) ||
        (row == height -1  && col == 0) ||
        (row == height - 1 && col == height - 1)) 
        return true;
    return false;
}

void Board::play(int marker, int row, int col, bool remove) {
    if (cache.count(marker) == 0) {
        std::cout << "No such marker!" << std::endl;
    }
    
    if (remove && !corner(row, col)) {
        board[row][col] = 0;
    } else {
        if (board[row][col] == 0) {
            board[row][col] = marker;
        }
    }
}

bool Board::check_row(int marker, int row, int col) {
    if (col > (width / 2))
        return false;
    
    std::pair<std::pair<int, int>, std::pair<int, int>> search{{row, col}, {row, col+4}};

    if (std::find(cache[marker].begin(), cache[marker].end(), search) != cache[marker].end())
        return false;

    bool found = true;
    for (int i = col; i < col + 5; ++i) {
        if (board[row][i] != marker && board[row][i] != 255) {
            found = false;
            break;
        }
    }

    if (found) {
        cache[marker].push_back(search);
    }
    return found;
}

bool Board::check_col(int marker, int row, int col) {
    if (row > (height / 2))
        return false;
    
    std::pair<std::pair<int, int>, std::pair<int, int>> search{{row, col}, {row+4, col}};

    if (std::find(cache[marker].begin(), cache[marker].end(), search) != cache[marker].end())
        return false;

    bool found = true;
    for (int i = row; i < row + 5; ++i) {
        if (board[i][col] != marker && board[i][col] != 255) {
            found = false;
            break;
        }
    }
    
    if (found) {
        cache[marker].push_back(search);
    }

    return found;
}

bool Board::check_diag_right(int marker, int row, int col) {
    if (row > (height / 2) || col > (width / 2))
        return false;
    
    std::pair<std::pair<int, int>, std::pair<int, int>> search{{row, col}, {row+4, col+4}};

    if (std::find(cache[marker].begin(), cache[marker].end(), search) != cache[marker].end())
        return false;

    bool found = true;
    for (int i = 0; i < 5; ++i) {
        if (board[row + i][col + i] != marker && board[row + i][col + i] != 255) {
            found = false;
            break;
        }
    }
   

    if (found) {
        cache[marker].push_back(search);
    }

    return found;
}

bool Board::check_diag_left(int marker, int row, int col) {
    if (row > (height / 2) || col < ((width / 2) - 1))
        return false;
    
    std::pair<std::pair<int, int>, std::pair<int, int>> search{{row, col}, {row+4, col-4}};

    if (std::find(cache[marker].begin(), cache[marker].end(), search) != cache[marker].end())
        return false;

    bool found = true;
    for (int i = 0; i < 5; ++i) {
        if (board[row + i][col - i] != marker && board[row + i][col - i] != 255) {
            found = false;
            break;
        }
    }
    
    if (found) {
        cache[marker].push_back(search);
    }

    return found;
}

bool Board::check(int marker, int row, int col) {
    bool found_row = check_row(marker, row, col);
    bool found_col = check_col(marker, row, col);
    bool found_right = check_diag_right(marker, row, col);
    bool found_left = check_diag_left(marker, row, col);

    return true;
}

bool Board::won(int marker) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            bool won = check(marker, i, j);
        }
    }

    if (cache[marker].size() >= 2)
        return true;

    return false;
}


