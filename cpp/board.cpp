#include <iostream>
#include <map>
#include <vector>
#include "board.h"
#include <stdexcept>
#include <string>

Board::Board() {
    cache[1] = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>();
    cache[2] = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>();
    cache[3] = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>();
    if (!check_board()) {
        throw (std::invalid_argument("Board was not set up correctly"));
    }
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

    done = false;
    winner = 0;
}

void Board::show() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void Board::show(int arr[height][width]) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << arr[i][j] << "\t";
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

    if (corner(row, col)) {
        throw (std::invalid_argument("Can't update a corner!!!"));
    }
    
    if (remove) {
        board[row][col] = 0;
    } else {
        if (board[row][col] != 0) {
            throw (std::invalid_argument("Already a play at " + std::to_string(row) + "," + std::to_string(col)));
        }

        if (row != -1 && col != -1) {
            board[row][col] = marker;
        }
    }

    update(marker);
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

    return (found_row || found_col || found_right || found_left);
}

void Board::getOpenSlots(std::vector<std::pair<int, int>> &vect) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (board[i][j] == 0) {
                vect.push_back(std::pair<int, int>{i, j});
            }
        }
    }
}

void Board::getTakenSlots(std::vector<std::pair<int, int>> &vect) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (board[i][j] != 255 && board[i][j] != 0) {
                vect.push_back(std::pair<int, int>{i, j});
            }
        }
    }
}

const std::vector<std::pair<int, int>>& Board::getMoves(Card card, std::vector<std::pair<int, int>> &moves) {
    if (card.isOneEyedJack()) {
        getTakenSlots(moves);
    }
    else if (card.isTwoEyedJack()) {
        getOpenSlots(moves);
    }
    else {
        for (auto it = cardMap.at(card).begin(); it != cardMap.at(card).end(); ++it) {
            if (board[it->first][it->second] == 0) {
                moves.push_back({it->first, it->second});
            }
        }
        if (moves.size() == 0) {
            moves.push_back({-1, -1});
        }
    }
    return moves;
}


void Board::update(int marker) {
    if (done)
        return;

    bool found;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            found = check(marker, i, j);
        }
    }

    if (cache[marker].size() >= 2) {
        std::cout << "Done!" << std::endl;
        done = true;
        winner = marker;
    }
}

// Test function
bool Board::check_board() {
    int temp_board[height][width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            temp_board[i][j] = 0;
        }
    }

    temp_board[0][0] = 1;
    temp_board[0][width-1] = 1;
    temp_board[height-1][0] = 1;
    temp_board[height-1][width-1] = 1;

    for (auto it = cardMap.begin(); it != cardMap.end(); ++it) {
        
        for (auto vectit = cardMap.at(it->first).begin(); vectit != cardMap.at(it->first).end(); ++vectit) {
            int i = vectit->first;
            int j = vectit->second;
            if (temp_board[i][j] != 0) {
                std::cout << i << "," << j << "already taken" << std::endl;
                return false;
            }
            temp_board[i][j] = 1;
        }
    }
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (temp_board[i][j] == 0) {
                std::cout << i << "," << j << " not set" << std::endl;
                return false;
            }
        }
    }
    
    return true;
}

bool Board::isDone() {
    return done;
}

int Board::getWinner() {
    return winner;
}


