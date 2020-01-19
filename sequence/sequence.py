#!/usr/bin/env python

import numpy as np
import sys
from board import Board, Deck

class Player(object):
    def __init__(self, cards, marker):
        self.cards = cards
        self.marker = marker
        self.lines = []

    def reset(self):
        self.cards = []
        self.marker = None
        self.lines = []
    
    def show_cards(self):
        for idx, card in enumerate(self.cards):
            print('{}: {}'.format(idx, str(card)))

    def show_moves(self, move):
        for idx, mv in enumerate(move):
            print("Move {}: {}".format(idx, mv))

    def add_card(self, card, idx = None):
        if not idx:
            self.cards.append(card)
        else:
            self.cards.insert(idx, card)

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
                print()
                print(self.board.board)
                print()

                curr_player.show_cards()
                move_choice = input("Player {}, what's your move?".format(turn+1))
                while not move_choice.isdigit() or int(move_choice) < 0 or int(move_choice) > 6:
                    move_choice = input("Invalid move, choose number 0 - {}".format(
                        len(curr_player.cards)))
                
                move_choice = int(move_choice)
                card = curr_player.get_card(move_choice)

                isOneEyed, moves = self.board.get_moves(card, curr_player.marker)
                if len(moves) == 0:
                    print(" No moves available, try another")
                    curr_player.add_card(card, idx = move_choice)
                    continue

                curr_player.show_moves(moves)
                choice = input("Player {}, which move? Enter 0 through {}, or type 'b' for back".format(turn + 1, len(moves)))

                while not (choice.isdigit() and int(choice) >= 0 and  int(choice) < len(moves)) and choice != 'b':
                    choice = input("Choose a number 0 through {}, or type 'b' for back".format(len(moves)-1))

                if not choice.isdigit() and choice == 'b':
                    curr_player.add_card(card, idx = move_choice)
                    continue

                self.board.make_move(moves[int(choice)], curr_player.marker, isOneEyed)
                have_winner = self.board.update_score(curr_player.marker, curr_player.lines)
                if have_winner:
                    print("Player {} wins!".format(turn))
                    winner = True

                curr_player.add_card(self.deck.draw())
                
                turn = (turn + 1) % 2
                curr_player = players[turn]

                accepted = True

if __name__ == '__main__':
    sequence = Sequence()
    sequence.play()
