#include <iostream>
#include <map>
#include <vector>
#include "deck.h"

Card::Card(Suite cardSuite, Face cardFace) {
    suite = cardSuite;
    face = cardFace;

    if (face == Face::jack && (suite == Suite::spade || suite == Suite::heart)) {
        oneeyedjack = true;
    } else {
        oneeyedjack = false;
    }
    
    if (face == Face::jack && (suite == Suite::club || suite == Suite::diamond)) {
        twoeyedjack = true;
    } else {
        twoeyedjack = false;
    }

}

bool Card::isOneEyedJack() {
    return oneeyedjack;
}

bool Card::isTwoEyedJack() {
    return twoeyedjack;
}

Deck::Deck() {
    reset();
}

void Deck::reset() {
    cards.clear();
    for (const auto& suite: Suites) {
        for (const auto& face: Faces) {
            cards.push_back(Card(suite, face));
        }
    }
    std::random_shuffle(cards.begin(), cards.end());
}

Card Deck::draw() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

