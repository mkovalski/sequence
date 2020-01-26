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

std::ostream& operator<<(std::ostream &strm, const Card &card) {
    return strm << FaceMap.at(card.face) << " of " << SuiteMap.at(card.suite);
}

Deck::Deck() {
    reset();
}

void Deck::reset() {
    cards.clear();
    for (const auto& suite: Suites) {
        for (const auto& face: Faces) {
            for (int i = 0; i < 2; ++i) {
                cards.push_back(Card(suite, face));
            }
        }
    }
    std::random_shuffle(cards.begin(), cards.end());
}

Card Deck::draw() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

