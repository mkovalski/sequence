#include <deck.h>
#include <board.h>
#include <vector>
#include <random>

class Sequence {
    const std::map<int, int> cardsPerPlayer { {2, 7}, {3, 6} };

    public: 
        Sequence(int);
        void reset();
    private:
        Board board;
        Deck deck;
        std::map<int, std:vector<Card>> playerCards;
        int nplayers;

    Sequence(int nplayers) {
        if (nplayers > 3 || nplayers < 2) {
            throw std::invalid_argument;
        }
        this->nplayers = nplayers;
        
        for (int i = 1, i <= nplayers; ++i) {
            playerCards[i] = std::vector<Card>();
        }

        board.reset();
        deck.reset();
        reset();
    }

    void reset() {
        board.reset();
        deck.reset();
        for (const auto& p: playerCards) {
            playerCards[p.first].clear();
            for (int i = 0; i < cardsPerPlayer[p.first]; ++i) {
                playerCards[p.first].push_back(deck.draw());
            }
        }
    }

    void move(Card card) {
        
    }

}
