#include "sequence.h"
#include "deck.h"
#include <stdlib.h>

int main() {
    const int nplayers = 2;
    Sequence sequence(nplayers);
    sequence.reset();
    std::cout << "new game!" << std::endl;
    
    int player = 1;
    std::vector<Card> playerCards[nplayers];
    std::vector<std::pair<int, int>> playerMoves[nplayers];

    bool done = false;
    int currPlayer = player;
    int card;
    int move;
    int index;

    while (!done) {
        std::cout << "player " << currPlayer << " move" << std::endl;
        index = currPlayer - 1;

        playerCards[index] = sequence.getCards(currPlayer);
        
        for (auto it = playerCards[index].begin(); it != playerCards[index].end(); ++it) {
            std::cout << *it << std::endl;
        }

        card = rand() % playerCards[index].size();
        playerMoves[index] = sequence.getMoves(currPlayer, card);
        while (playerMoves[index].size() == 0) {
            card = rand() % playerCards[index].size();
            playerMoves[index] = sequence.getMoves(currPlayer, card);
        }

        move = rand() % playerMoves[index].size();

        sequence.print_move(currPlayer, playerCards[index].at(card),
                            playerMoves[index].at(move));

        sequence.move(currPlayer, card, move);

        sequence.show();

        currPlayer = (currPlayer % 2) + 1;
        done = sequence.done();

        std::cout << std::endl;
    }
    
    return 0;
}

