#include <iostream>
#include <map>
#include <vector>
#include "deck.h"

#ifndef BOARD
#define BOARD

class Board {
    static const int width = 10;
    static const int height = 10;
    const std::map<Card, std::vector<std::pair<int, int>>> cardMap = {
        {Card(Suite::heart, Face::two), {{1, 2}, {4, 5}}}, 
        {Card(Suite::heart, Face::three), {{1, 1}, {4, 4}}},
        {Card(Suite::heart, Face::four), {{2, 1}, {5, 4}}},
        {Card(Suite::heart, Face::five), {{3, 1}, {5, 5}}},
        {Card(Suite::heart, Face::six), {{4, 1}, {5, 6}}},
        {Card(Suite::heart, Face::seven), {{4, 6}, {5, 1}}},
        {Card(Suite::heart, Face::eight), {{3, 6}, {6, 1}}},
        {Card(Suite::heart, Face::nine), {{3, 5}, {7, 1}}},
        {Card(Suite::heart, Face::ten), {{3, 4}, {8, 1}}},
        {Card(Suite::heart, Face::queen), {{3, 3}, {8, 2}}},
        {Card(Suite::heart, Face::king), {{4, 3}, {8, 3}}},
        {Card(Suite::heart, Face::ace), {{5, 3}, {8, 4}}},
        {Card(Suite::diamond, Face::two), {{4, 0}, {7, 7}}},
        {Card(Suite::diamond, Face::three), {{3, 0}, {7, 6}}},
        {Card(Suite::diamond, Face::four), {{2, 0}, {7, 5}}},
        {Card(Suite::diamond, Face::five), {{1, 0}, {7, 4}}},
        {Card(Suite::diamond, Face::six), {{0, 1}, {7, 3}}},
        {Card(Suite::diamond, Face::seven), {{0, 2}, {7, 2}}},
        {Card(Suite::diamond, Face::eight), {{0, 3}, {6, 2}}},
        {Card(Suite::diamond, Face::nine), {{0, 4}, {5, 2}}},
        {Card(Suite::diamond, Face::ten), {{0, 5}, {4, 2}}},
        {Card(Suite::diamond, Face::queen), {{0, 6}, {3, 2}}},
        {Card(Suite::diamond, Face::king), {{0, 7}, {2, 2}}},
        {Card(Suite::diamond, Face::ace), {{0, 8}, {2, 3}}},
        {Card(Suite::club, Face::two), {{6, 3}, {8, 5}}},
        {Card(Suite::club, Face::three), {{6, 4}, {8, 6}}},
        {Card(Suite::club, Face::four), {{6, 5}, {8, 7}}},
        {Card(Suite::club, Face::five), {{6, 6}, {8, 8}}},
        {Card(Suite::club, Face::six), {{6, 7}, {8, 9}}},
        {Card(Suite::club, Face::seven), {{5, 7}, {7, 9}}},
        {Card(Suite::club, Face::eight), {{4, 7}, {6, 9}}},
        {Card(Suite::club, Face::nine), {{3, 7}, {5, 9}}},
        {Card(Suite::club, Face::ten), {{2, 7}, {4, 9}}},
        {Card(Suite::club, Face::queen), {{2, 6}, {3, 9}}},
        {Card(Suite::club, Face::king), {{2, 5}, {2, 9}}},
        {Card(Suite::club, Face::ace), {{1, 9}, {2, 4}}},
        {Card(Suite::spade, Face::two), {{1, 3}, {9, 8}}},
        {Card(Suite::spade, Face::three), {{1, 4}, {9, 7}}},
        {Card(Suite::spade, Face::four), {{1, 5}, {9, 6}}},
        {Card(Suite::spade, Face::five), {{1, 6}, {9, 5}}},
        {Card(Suite::spade, Face::six), {{1, 7}, {9, 4}}},
        {Card(Suite::spade, Face::seven), {{1, 8}, {9, 3}}},
        {Card(Suite::spade, Face::eight), {{2, 8}, {9, 2}}},
        {Card(Suite::spade, Face::nine), {{3, 8}, {9, 1}}},
        {Card(Suite::spade, Face::ten), {{4, 8}, {8, 0}}},
        {Card(Suite::spade, Face::queen), {{5, 8}, {7, 0}}},
        {Card(Suite::spade, Face::king), {{6, 0}, {6, 8}}},
        {Card(Suite::spade, Face::ace), {{5, 0}, {7, 8}}}
    };

    public:
        Board();
        void reset();
        void show();
        void show(int[height][width]);
        void play(int, int, int, bool);
        void getOpenSlots(std::vector<std::pair<int, int>> &vect);
        void getTakenSlots(std::vector<std::pair<int, int>> &vect);
        const std::vector<std::pair<int, int>>& getMoves(Card, std::vector<std::pair<int, int>> &vect);
        bool isDone();
        int getWinner();

    private:
        int board[width][height];
        int winner;
        bool done;

        std::map<int, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> cache;
        bool check(int, int, int);
        bool check_row(int, int, int);
        bool check_col(int, int, int);
        bool check_diag_right(int, int, int);
        bool check_diag_left(int, int, int);
        bool corner(int, int);
        bool check_board();
        void update(int);
};

#endif //BOARD
