#!/usr/bin/env python

import numpy as np
from enum import Enum
import itertools

class Board(object):
    CORNERS = [(0, 0), (0, -1), (-1, 0), (-1, -1)]

    def __init__(self):
        self.board = np.zeros((10, 10), dtype = np.int)
        self.player1_streaks = []
        self.player2_streaks = []
        self.moves = self.build()
        self.one_eyed_jacks, self.two_eye_jacks = self.create_jacks()
        self.check_board()
        self.reset()

    def build(self):
        # This logic is a bit wild but I kind of need to hard code this in
        moves = {}

        # Row 0
        moves[Card(Rank.SIX, Suite.DIAMONDS)] = [(0, 1), (7, 3)]
        moves[Card(Rank.SEVEN, Suite.DIAMONDS)] = [(0, 2), (7, 2)]
        moves[Card(Rank.EIGHT, Suite.DIAMONDS)] = [(0, 3), (6, 2)]
        moves[Card(Rank.NINE, Suite.DIAMONDS)] = [(0, 4), (5, 2)]
        moves[Card(Rank.TEN, Suite.DIAMONDS)] = [(0, 5), (4, 2)]
        moves[Card(Rank.QUEEN, Suite.DIAMONDS)] = [(0, 6), (3, 2)]
        moves[Card(Rank.KING, Suite.DIAMONDS)] = [(0, 7), (2, 2)]
        moves[Card(Rank.ACE, Suite.DIAMONDS)] = [(0, 8), (2, 3)]

        # Row 1
        moves[Card(Rank.FIVE, Suite.DIAMONDS)] = [(1, 0), (7, 4)]
        moves[Card(Rank.THREE, Suite.HEARTS)] = [(1, 1), (4, 4)]
        moves[Card(Rank.TWO, Suite.HEARTS)] = [(1, 2), (4, 5)]
        moves[Card(Rank.TWO, Suite.SPADES)] = [(1, 3), (9, 8)]
        moves[Card(Rank.THREE, Suite.SPADES)] = [(1, 4), (9, 7)]
        moves[Card(Rank.FOUR, Suite.SPADES)] = [(1, 5), (9, 6)]
        moves[Card(Rank.FIVE, Suite.SPADES)] = [(1, 6), (9, 5)]
        moves[Card(Rank.SIX, Suite.SPADES)] = [(1, 7), (9, 4)]
        moves[Card(Rank.SEVEN, Suite.SPADES)] = [(1, 8), (9, 3)]
        moves[Card(Rank.ACE, Suite.CLUBS)] = [(1, 9), (2, 4)]

        # Row 2
        moves[Card(Rank.FOUR, Suite.DIAMONDS)] = [(2, 0), (7, 5)]
        moves[Card(Rank.FOUR, Suite.HEARTS)] = [(2, 1), (5, 4)]
        moves[Card(Rank.KING, Suite.CLUBS)] = [(2, 5), (2, 9)]
        moves[Card(Rank.QUEEN, Suite.CLUBS)] = [(2, 6), (3, 9)]
        moves[Card(Rank.TEN, Suite.CLUBS)] = [(2, 7), (4, 9)]
        moves[Card(Rank.EIGHT, Suite.SPADES)] = [(2, 8), (9, 2)]
    
        # Row 3
        moves[Card(Rank.THREE, Suite.DIAMONDS)] = [(3, 0), (7, 6)]
        moves[Card(Rank.FIVE, Suite.HEARTS)] = [(3, 1), (5, 5)]
        moves[Card(Rank.QUEEN, Suite.HEARTS)] = [(3, 3), (8, 2)]
        moves[Card(Rank.TEN, Suite.HEARTS)] = [(3, 4), (8, 1)]
        moves[Card(Rank.NINE, Suite.HEARTS)] = [(3, 5), (7, 1)]
        moves[Card(Rank.EIGHT, Suite.HEARTS)] = [(3, 6), (6, 1)]
        moves[Card(Rank.NINE, Suite.CLUBS)] = [(3, 7), (5, 9)]
        moves[Card(Rank.NINE, Suite.SPADES)] = [(3, 8), (9, 1)]

        # Row 4
        moves[Card(Rank.TWO, Suite.DIAMONDS)] = [(4, 0), (7, 7)]
        moves[Card(Rank.SIX, Suite.HEARTS)] = [(4, 1), (5, 6)]
        moves[Card(Rank.KING, Suite.HEARTS)] = [(4, 3), (8, 3)]
        moves[Card(Rank.SEVEN, Suite.HEARTS)] = [(4, 6), (5, 1)]
        moves[Card(Rank.EIGHT, Suite.CLUBS)] = [(4, 7), (6, 9)]
        moves[Card(Rank.TEN, Suite.SPADES)] = [(4, 8), (8, 0)]

        # Row 5
        moves[Card(Rank.ACE, Suite.SPADES)] = [(5, 0), (7, 8)]
        moves[Card(Rank.ACE, Suite.HEARTS)] = [(5, 3), (8, 4)]
        moves[Card(Rank.SEVEN, Suite.CLUBS)] = [(5, 7), (7, 9)]
        moves[Card(Rank.QUEEN, Suite.SPADES)] = [(5, 8), (7, 0)]

        # Row 6
        moves[Card(Rank.KING, Suite.SPADES)] = [(6, 0), (6, 8)]
        moves[Card(Rank.TWO, Suite.CLUBS)] = [(6, 3), (8, 5)]
        moves[Card(Rank.THREE, Suite.CLUBS)] = [(6, 4), (8, 6)]
        moves[Card(Rank.FOUR, Suite.CLUBS)] = [(6, 5), (8, 7)]
        moves[Card(Rank.FIVE, Suite.CLUBS)] = [(6, 6), (8, 8)]
        moves[Card(Rank.SIX, Suite.CLUBS)] = [(6, 7), (8, 9)]
    
        return moves
    
    def create_jacks(self):
        one_eyed_jacks = [Card(Rank.JACK, Suite.DIAMONDS),
                           Card(Rank.JACK, Suite.HEARTS)]

        two_eyed_jacks = [Card(Rank.JACK, Suite.SPADES),
                          Card(Rank.JACK, Suite.CLUBS)]

        return one_eyed_jacks, two_eyed_jacks


    def reset(self):
        self.board[:] = Player.NONE.value
        self.board[0, 0] = Player.EITHER.value
        self.board[0, -1] = Player.EITHER.value
        self.board[-1, 0] = Player.EITHER.value
        self.board[-1, -1] = Player.EITHER.value
    
    def check_board(self):
        empty_board = np.zeros((10, 10))
        # TODO: corn
        for corn in self.CORNERS:
            empty_board[corn] = 1

        for key, values in self.moves.items():
            for position in values:
                assert(empty_board[position] == 0), \
                    'Tried to set {} at {}, but already set'.format(str(key), position)
                empty_board[position] = 1
        
        uniq = np.unique(empty_board)
        if len(uniq) != 1:
            indices = np.where(empty_board != 1)
            raise ValueError("Indices {} were not set".format(indices))
    

    def get_moves(self, card, marker):
        
        # Check for jokers: TODO
        isOneEyed, isjack = card.isjack()

        if isjack:
            if isOneEyed:
                indices = np.where((self.board != Player.NONE.value) & (self.board != Player.EITHER.value))
            else:
                indices = np.where(self.board == Player.NONE.value)
            return isOneEyed, list(zip(indices[0], indices[1]))

        else:
        
            positions = self.moves[card]
            moves = []
            for pos in positions:
                if self.board[pos] == 0:
                    moves.append(pos)

        return isOneEyed, moves

    def make_move(self, move, marker, oneEyed):
        if oneEyed:
            self.board[move] = 0
        else:
            assert(self.board[move] == 0)
            self.board[move] = marker

class Player(Enum):
    NONE = 0
    EITHER = -1

class Rank(Enum):
    TWO = 2
    THREE = 3
    FOUR = 4
    FIVE = 5
    SIX = 6
    SEVEN = 7
    EIGHT = 8
    NINE = 9
    TEN = 10
    JACK = 11
    QUEEN = 12
    KING = 13
    ACE = 14

class Suite(Enum):
    DIAMONDS = 1
    HEARTS = 2
    SPADES = 3
    CLUBS = 4

class Deck(object):
    def __init__(self):
        self.reset()

    def reset(self):
        self.cards = []
        for item in itertools.product([x for x in Rank], [x for x in Suite]):
            self.cards.append(Card(item[0], item[1]))

        np.random.shuffle(self.cards)
    
    def draw(self):
        if len(self.cards) > 0:
            return self.cards.pop()
        return None

class Card(object):
    def __init__(self, rank: Rank, suite: Suite):
        self.rank = rank
        self.suite = suite
    
    def isjack(self):
        if self.rank == Rank.JACK:
            if self.suite == Suite.DIAMONDS or self.suite == Suite.HEARTS:
                return True, True
            return False, True
        
        return False, False

    def __hash__(self):
        return hash(str(self.rank) + str(self.suite))

    def __str__(self):
        return str(self.rank.name) + ' of ' + str(self.suite.name)

    def __eq__(self, other):
        return self.rank == other.rank and self.suite == other.suite

if __name__ == '__main__':
    board = Board() 
