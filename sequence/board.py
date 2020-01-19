#!/usr/bin/env python

import numpy as np
from enum import Enum
import itertools

class Board(object):
    def __init__(self):
        self.board = np.zeros((10, 10), dtype = PLAYER)
        self.player1_streaks = []
        self.player2_streaks = []
        self.moves = self.build()
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
        moves[Card(Rank.FOUR, Suite.DIAMONDS)] = [(2, 2), (7, 5)]
        moves[Card(Rank.FOUR, Suite.HEARTS)] = [(2, 1), (5, 4)]
        moves[Card(Rank.KING, Suite.CLUBS)] = [(2, 5), (2, 9)]
        moves[Card(Rank.QUEEN, Suite.CLUBS)] = [(2, 6), (3, 9)]
        moves[Card(Rank.TEN, Suite.CLUBS)] = [(2, 7), (3, 9)]
        moves[Card(Rank.EIGHT, Suite.SPADES)] = [(2, 8), (9, 2)]




        




    
    def reset(self)
        self.board[:] = PLAYER.NONE
        self.board[0, 0] = PLAYER.EITHER
        self.board[0, -1] = PLAYER.EITHER
        self.board[-1, 0] = PLAYER.EITHER
        self.board[-1, -1] = PLAYER.EITHER

class Player(Enum):
    NONE = 0
    PLAYER1 = 1
    PLAYER2 = 2
    EITHER = 3

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


class Card(object):
    def __init__(self, rank: Rank, suite: Suite):
        self.rank = rank
        self.suite = suite

    def __hash__(self):
        return hash(str(self.rank) + str(self.suite))
