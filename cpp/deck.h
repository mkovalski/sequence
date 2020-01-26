#include <iostream>
#include <map>
#include <vector>
#include <string>

#ifndef DECK
#define DECK

enum class Suite {
    heart,
    diamond,
    club,
    spade,
};

enum class Face {
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
};

const Suite Suites[] = {Suite::heart, Suite::diamond, Suite::club, Suite::spade};
const Face Faces[] = {Face::two, Face::three, Face::four, Face::five,
                      Face::six, Face::seven, Face::eight, Face::nine,
                      Face::ten, Face::jack, Face::queen, Face::king, Face::ace};

const std::map<Suite, std::string> SuiteMap = {{Suite::heart, "hearts"},
                                               {Suite::diamond, "diamonds"},
                                               {Suite::club, "clubs"},
                                               {Suite::spade, "spades"},
                                               };

const std::map<Face, std::string> FaceMap = {{Face::two, "two"},
                                             {Face::three, "three"},
                                             {Face::four, "four"},
                                             {Face::five, "five"},
                                             {Face::six, "six"},
                                             {Face::seven, "seven"},
                                             {Face::eight, "eight"},
                                             {Face::nine, "nine"},
                                             {Face::ten, "ten"},
                                             {Face::jack, "jack"},
                                             {Face::queen, "queen"},
                                             {Face::king, "king"},
                                             {Face::ace, "ace"}};

class Card {
    public:
        Card(Suite cardSuite, Face cardFace);
        bool isOneEyedJack();
        bool isTwoEyedJack();
        bool operator == (const Card &Ref) const {
            return (suite == Ref.suite &&
                face == Ref.face);
        }
        bool operator < (const Card &Ref) const {
            if (Ref.suite == this->suite) {
                return Ref.face < this->face;
            }
            return Ref.suite < this->suite;
        }

    private:
        Suite suite;
        Face face;
        bool oneeyedjack;
        bool twoeyedjack;
        friend std::ostream& operator<<(std::ostream &strm, const Card &card);
};

class Deck {
    public:
        void reset();
        Card draw();
        Deck();

    private:
        std::vector<Card> cards;
};

#endif //DECK
