#!/usr/bin/env python

import numpy as np
import sys
from board import Board, Deck

class Player(object):
    def __init__(self, cards, marker):
        self.cards = cards
        self.marker = marker
    
    def show_cards(self):
        for idx, card in enumerate(self.cards):
            print('{}: {}'.format(idx, str(card)))

    def show_moves(self, move):
        for idx, mv in enumerate(move):
            print("Move {}: {}".format(idx, mv))

    def add_card(self, card):
        self.cards.append(card)

    def get_card(self, idx):
        return self.cards.pop(idx)


class Sequence():
    def __init__(self):
        self.board = Board()
        self.deck = Deck()
    
    def reset(self):
        self.board.reset()
        self.deck.reset()

    def play(self):
        winner = False
        
        player1 = Player([self.deck.draw() for _ in range(7)],
                         marker = 1) 
        player2 = Player([self.deck.draw() for _ in range(7)],
                         marker = 2) 
        
        assert(player1.marker != player2.marker)
        players = [player1, player2]
        assert([p.marker != 0 for p in players])


        turn = np.random.randint(low = 0, high = 2)
        curr_player = players[turn]

        while not winner:
            accepted = False

            while not accepted:
                curr_player.show_cards()
                choice = input("Player {}, what's your move?".format(turn))
                while not choice.isdigit() or int(choice) < 0 or int(choice) > 6:
                    choice = input("Invalid move, choose number 0 - {}".format(
                        len(curr_player.cards)))
                
                choice = int(choice)
                card = curr_player.get_card(choice)

                isOneEyed, moves = self.board.get_moves(card, curr_player.marker)
                if len(moves) == 0:
                    print(" No moves available, try another")
                    curr_player.add_card(card)
                    continue
                
                curr_player.show_moves(moves)
                choice = input("Player {}, which move?".format(turn))
                while not choice.isdigit() or int(choice) < 0 or int(choice) >= len(moves):
                    choice = input("Choose a number 0 through {}".format(len(moves)-1))

                self.board.make_move(moves[int(choice)], curr_player.marker, isOneEyed)

                curr_player.add_card(self.deck.draw())
                
                turn = (turn + 1) % 2
                curr_player = players[turn]
                print()
                print(self.board.board)
                print()

                accepted = True

if __name__ == '__main__':
    sequence = Sequence()
    sequence.play()
