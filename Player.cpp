// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"

using namespace std;

class SimplePlayer : public Player {
private:
    string name;
    vector<Card>handCards;
public:
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
            for (int i = 0; i < handCards.size(); i++) {
                if (handCards[i].is_face() && handCards[i].is_trump(upcard.get_suit())) {
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
            for (int i = 0; i < handCards.size(); i++) {
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
        for (int i = 1; i < handCards.size(); i++) {
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
        for (int i = 0; i < handCards.size(); i++) {
            if (handCards[i].get_suit() != trump) {
                Card maxNonTrump;
                for (int j = 0; j < handCards.size(); j++) {
                    if (handCards[j] > maxNonTrump && handCards[j].get_suit() != trump) {
                        maxNonTrump = handCards[j];
                    }
                }
                return maxNonTrump;
            }

        }
        Card maxTrump;
        for (int j = 1; j < handCards.size(); j++) {
            if (handCards[j] > maxTrump) {
                maxTrump = handCards[j];
            }
        }
        return maxTrump;
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) override{
        Card maxLed;
        int countLed = 0;
        for (int i = 0; i < handCards.size(); i++) {
            if (handCards[i].get_suit() == led_card.get_suit()){
                countLed ++;
                if(handCards[i] > maxLed) {
                    maxLed = handCards[i];
                }
            }
        }
        if (countLed != 0) {
            return maxLed;
        }
        Card lowestCard = handCards[0];
        for (int i = 1; i < handCards.size(); i++) {
            if (Card_less(handCards[i], lowestCard, trump)) {
                lowestCard = handCards[i];
            }
        }
        return lowestCard;
    }
};

class HumanPlayer : public Player {
private:
    string name;
    vector<Card>handCards;
public:
    const std::string & get_name() const override{
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override{
        handCards.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const override{
        return true;
        //change later
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override{
        handCards.push_back(upcard);
        handCards.erase(<#const_iterator __position#>);
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override;

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) override;

    // Maximum number of cards in a player's hand
    static const int MAX_HAND_SIZE = 5;
}

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) const {
}

//EFFECTS: Prints player's name to os
ostream & operator<<(std::ostream &os, const Player &p){

}
