#include <iostream>
#include <map>
#include <vector>

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
class Card {
    public:
        Card(Suite cardSuite, Face cardFace);
        bool isOneEyedJack();
        bool isTwoEyedJack();
        const Suite getSuite() const {return suite; };
        const Face getFace() const { return face; };
        bool operator == (const Card &Ref) const {
            return (getSuite() == Ref.getSuite() &&
                getFace() == Ref.getFace());
        }
        bool operator < (const Card &Ref) const {
            if (Ref.face < this->face) {
                return true;
            }
            return false;
        }

    private:
        Suite suite;
        Face face;
        bool oneeyedjack;
        bool twoeyedjack;
};

class Deck {
    public:
        void reset();
        Card draw();
        Deck();

    private:
        std::vector<Card> cards;
};
