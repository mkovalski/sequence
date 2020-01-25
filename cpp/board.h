#include <iostream>
#include <map>
#include <vector>

class Board {
    static const int width = 10;
    static const int height = 10;

    public:
        Board();
        void reset();
        void show();
        void play(int, int, int);
        bool won(int);

    private:
        int board[width][height];
        std::map<int, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> cache;
        bool check(int, int, int);
        bool check_row(int, int, int);
        bool check_col(int, int, int);
        bool check_diag_right(int, int, int);
        bool check_diag_left(int, int, int);
};


