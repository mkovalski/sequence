#include <vector>
#include <random>
#include <map>
#include "board.h"
#include "deck.h"
#include <stdexcept>

class Sequence {
    const std::map<int, int> cardsPerPlayer = {{2, 7}, {3, 6}};

    public: 
        Sequence(int);
        void reset();
        void move(int, int, int);
        std::vector<Card> getCards(int);
        std::vector<std::pair<int, int>> getMoves(int, int);
        bool join(int);
        bool done();
        int winner();
        void show();
        void print_move(int, Card, std::pair<int, int>);
    private:
        Board board;
        Deck deck;
        std::map<int, std::vector<Card>> playerCards;
        int nplayers;
};

Sequence::Sequence(int nplayers) {
    if (nplayers > 3 || nplayers < 2) {
        throw (std::invalid_argument("Must be 2 or 3 players"));
    }
    this->nplayers = nplayers;
    
    for (int i = 1; i <= nplayers; ++i) {
        playerCards[i] = std::vector<Card>();
    }

    board.reset();
    deck.reset();
    reset();
}

bool Sequence::join(int player) {
    return true;
}
    

void Sequence::reset() {
    board.reset();
    deck.reset();
    int ncards = cardsPerPlayer.at(nplayers);

    for (const auto& p: playerCards) {
        playerCards[p.first].clear();
        for (int i = 0; i < ncards; ++i) {
            playerCards[p.first].push_back(deck.draw());
        }
    }
}

std::vector<Card> Sequence::getCards(int player) {
    return playerCards[player];
}

std::vector<std::pair<int, int>> Sequence::getMoves(int player, int cardIndex) {
    std::vector<std::pair<int, int>> vect;
    Card currentCard = playerCards[player].at(cardIndex);
    board.getMoves(currentCard, vect);
    return vect;
}

void Sequence::move(int player, int cardIndex, int moveIndex) {
    Card currentCard = playerCards[player][cardIndex];
    const std::vector<std::pair<int, int>>& moves = getMoves(player, cardIndex);

    std::pair<int, int> move = moves.at(moveIndex);
    board.play(player, move.first, move.second, false);

    playerCards[player].erase(playerCards[player].begin() + moveIndex);

    try {
        playerCards[player].push_back(deck.draw());
    } catch ( const std::invalid_argument& e ) {
        std::cout << "No more cards to draw!" << std::endl;
    }

}

void Sequence::show() {
    board.show();
}

bool Sequence::done() {
    return board.isDone();
}

void Sequence::print_move(int player, Card card, std::pair<int, int> move) {
    std::cout << "Player " << player << " playing " << card << " at (" << move.first << "," << move.second << ")" << std::endl;
}
