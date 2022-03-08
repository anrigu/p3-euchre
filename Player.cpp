// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>

using namespace std;

class SimplePlayer : public Player {
private:
    string name;
    vector<Card>handCards;
public:
    SimplePlayer(string name_in)
        : name(name_in) {}

    const std::string & get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        handCards.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const override {
        if (round == 1) {
            int countTrumpCards = 0;
            for (int i = 0; i < static_cast<int>(handCards.size()); i++) {
                if (handCards[i].is_face() &&
                    handCards[i].is_trump(upcard.get_suit())) {
                    countTrumpCards ++;
                }
            }
            if (countTrumpCards >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                return false;
            }
        }
        if (round == 2) {
            if (is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            int countAdjCards = 0;
            for (int i = 0; i < static_cast<int>(handCards.size()); i++) {
                if (handCards[i].is_face() && handCards[i].is_trump(Suit_next(upcard.get_suit()))) {
                    countAdjCards ++;
                }
            }
            if (countAdjCards >= 1) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            else {
                return false;
            }
        }
        return false;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override{
        add_card(upcard);
        Card minCard = handCards[0];
        int minInd = 0;
        for (int i = 1; i < static_cast<int>(handCards.size()); i++) {
            if (Card_less(handCards[i], minCard, upcard.get_suit())) {
                minCard = handCards[i];
                minInd = i;
            }
        }
        handCards.erase(handCards.begin() + minInd);
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override{
        for (int i = 0; i < static_cast<int>(handCards.size()); i++) {
            if (handCards[i].get_suit(trump) != trump) {
                Card maxNonTrump;
                int maxNonInd = 0;
                for (int j = 0; j < static_cast<int>(handCards.size()); j++) {
                    if (handCards[j] > maxNonTrump
                        && handCards[j].get_suit(trump) != trump) {
                        maxNonTrump = handCards[j];
                        maxNonInd = j;
                    }
                }
                handCards.erase(handCards.begin() + maxNonInd);
                return maxNonTrump;
            }

        }
        Card maxTrump;
        int maxTrumpInd = 0;
        Card jack_trump = Card(Card::RANK_JACK, trump);
        Card jack_left_bower = Card(Card::RANK_JACK, Suit_next(trump));
        for (int j = 1; j < static_cast<int>(handCards.size()); j++) {
            if (handCards[j] == jack_trump) {
                handCards.erase(handCards.begin() + j);
                return jack_trump;
            }
            if (handCards[j] == jack_left_bower) {
                handCards.erase(handCards.begin() + j);
                return jack_left_bower;
            }
            if (handCards[j] > maxTrump) {
                maxTrump = handCards[j];
                maxTrumpInd = j;
            }
        }
        handCards.erase(handCards.begin() + maxTrumpInd);
        return maxTrump;
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) override{
        Card maxLed;
        int countLed = 0;
        int maxInd = 0;
        Card jack_trump = Card(Card::RANK_JACK, trump);
        Card jack_left_bower = Card(Card::RANK_JACK, Suit_next(trump));

        for (int i = 0; i < static_cast<int>(handCards.size()); i++) {
            if (handCards[i].get_suit(trump) == led_card.get_suit(trump)){
                countLed ++;
                if (handCards[i] == jack_trump) {
                    handCards.erase(handCards.begin() + i);
                    return jack_trump;
                }
                if (handCards[i] == jack_left_bower) {
                    handCards.erase(handCards.begin() + i);
                    return jack_left_bower;
                }
                if(handCards[i] > maxLed) {
                    maxLed = handCards[i];
                    maxInd = i;
                }
            }
        }
        if (countLed != 0) {
            handCards.erase(handCards.begin() + maxInd);
            return maxLed;
        }
        Card lowestCard = handCards[0];
        int minInd = 0;
        for (int i = 1; i < static_cast<int>(handCards.size()); i++) {
            if (Card_less(handCards[i], lowestCard, trump)) {
                lowestCard = handCards[i];
                minInd = i;
            }
        }
        handCards.erase(handCards.begin() + minInd);
        return lowestCard;
    }
};


class HumanPlayer : public Player {
private:
    string name;
    vector<Card>handCards;
public:
    HumanPlayer(string name_in)
        : name(name_in) {}

    const std::string & get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        handCards.push_back(c);
    }

    void print_hand() const {
        sort(handCards.begin(), handCards.end());
        for (int i = 0; i < handCards.size(); i++) {
            cout << "Human player " << name << "'s hand: " << "[" << i << "] "
                 << handCards[i] << endl;
        }
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const override {
        string suit;
        print_hand();
        cout << "Human player " << name << ", please enter a suit, or \"pass\": ";
        cin >> suit;
        if (suit == "pass") {
            cout << name << " passes" << endl;
            return false;
        }
        else {
            cout << name << " orders up " << suit << endl;
            order_up_suit = suit;
            return true;
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override{
        print_hand();
        string discardUpcard;
        int discardCardInd;
        string junk;
        cout << "Discard upcard: " << endl;
        cin >> discardUpcard;
        if (discardUpcard == "[-1]") {
            handCards.erase(handCards.end());
        }
        cout << "Human player" << name
             << " , please select a card to discard:" << endl;
        cin >> junk >> discardCardInd >> junk;
        handCards.erase(handCards.begin() + discardCardInd);
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override{
        int cardPlay;
        print_hand();
        cin >> cardPlay;
        handCards.erase(handCards.begin() + cardPlay);
        return handCards[cardPlay];
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) override{
        return lead_card(trump);
    }
};


//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name,
                        const std::string &strategy) {
  // We need to check the value of strategy and return
  // the corresponding player type.
    if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
    else {
        return new HumanPlayer(name);
    }
//    assert(false);
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    return os << p.get_name();
}
