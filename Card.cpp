// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

Card::Card()
    : rank(Card::RANK_TWO), suit(Card::SUIT_SPADES) {}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string& rank_in, const std::string& suit_in) :
    rank(rank_in), suit(suit_in) {}

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string& trump) const {
    if (is_left_bower(trump) || suit == trump) {
        return trump;
    }
    return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
    if (rank == Card::RANK_JACK || rank == Card::RANK_QUEEN
        || rank == Card::RANK_KING || rank == Card::RANK_ACE) {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string& trump) const {
    if (rank == Card::RANK_JACK && suit == trump) {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string& trump) const {
    if (rank == RANK_JACK) {
        if ((trump == Card::SUIT_SPADES && suit == Card::SUIT_CLUBS) ||
            (trump == Card::SUIT_CLUBS && suit == Card::SUIT_SPADES) ||
            (trump == Card::SUIT_HEARTS && suit == Card::SUIT_DIAMONDS) ||
            (trump == Card::SUIT_DIAMONDS && suit == Card::SUIT_HEARTS)) {
            return true;
        }
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string& trump) const {
    if (suit == trump || is_left_bower(trump)) {
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card& lhs, const Card& rhs) {
    int lhsRank = 0;
    int rhsRank = 0;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            lhsRank = i;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            rhsRank = i;
        }
    }
    if (lhsRank < rhsRank) {
        return true;
    }
    else if (lhsRank == rhsRank) {
        int lhsSuit = 0;
        int rhsSuit = 0;
        for (int j = 0; j < NUM_SUITS; j++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[j]) {
                lhsSuit = j;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[j]) {
                rhsSuit = j;
            }
        }
        if (lhsSuit < rhsSuit) {
            return true;
        }
        else if (rhsSuit == lhsSuit) {
            if (rhsRank > lhsRank) {
                return true;
            }
            return false;
        }
        else {
            //lhsSuit < rhsSuit
            return false;
        }
    }
    else {
        return false;
    }
}


//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card& lhs, const Card& rhs) {
    return lhs < rhs || lhs == rhs;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator > (const Card& lhs, const Card& rhs) {
    return !(lhs < rhs) && lhs != rhs;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card& lhs, const Card& rhs) {
    if (lhs > rhs || lhs == rhs) {
        return true;
    }
    return false;
}
//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card& lhs, const Card& rhs) {
    int lhsRank = 0;
    int rhsRank = 0;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            lhsRank = i;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            rhsRank = i;
        }
    }
    int lhsSuit = 0;
    int rhsSuit = 0;
    for (int j = 0; j < NUM_SUITS; j++) {
        if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[j]) {
            lhsSuit = j;
        }
        if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[j]) {
            rhsSuit = j;
        }
    }
    if (lhsRank == rhsRank && lhsSuit == rhsSuit) {
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card& lhs, const Card& rhs) {
    return !(lhs == rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string& suit) {
    if (suit == SUIT_NAMES_BY_WEIGHT[0]) {
        return SUIT_NAMES_BY_WEIGHT[2];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[1]) {
        return SUIT_NAMES_BY_WEIGHT[3];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[2]) {
        return SUIT_NAMES_BY_WEIGHT[0];
    }
    else {
        return SUIT_NAMES_BY_WEIGHT[1];
    }
}


//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream& operator<<(std::ostream& os, const Card& card) {
    return os << card.get_rank() << " of " << card.get_suit();
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const std::string& trump) {
    if (b.get_suit(trump) == trump && a.get_suit(trump) == trump) {
        //both trump
        if (b.get_rank() == RANK_NAMES_BY_WEIGHT[9]
            && a.get_rank() == RANK_NAMES_BY_WEIGHT[9]) {
            //both jacks
            if (a.is_left_bower(trump)) {
                //a is left bower and b is trump
                return true;
            }
            else {
                //b is left bower
                return false;
            }
        }
        else if (b.get_rank() == RANK_NAMES_BY_WEIGHT[9]) {
            //b is jack and a isn't
            return true;
        }
        else if (a.get_rank() == RANK_NAMES_BY_WEIGHT[9]) {
            //a is jack and b isn't
            return false;
        }
        else {
            //no jacks
            return a < b;
        }
    }
    else if (b.get_suit(trump) == trump) {
        //b is trump and a isn't
        return true;
    }
    else if (a.get_suit(trump) == trump) {
        //a is trump and b isn't
        return false;
    }
    //no trumps
    return a < b;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const Card& led_card,
    const std::string& trump) {
    if (a.get_suit(trump) != trump && b.get_suit(trump) != trump) {
        //if both trump, use the card_less version above
        //Led cards get the next priority in terms of hierachy
        if (a.get_suit() == led_card.get_suit()
            && b.get_suit() != led_card.get_suit()) {
            //a is led card suit and b isn't.
            return false;
        }
        else if (b.get_suit() == led_card.get_suit()
            && a.get_suit() != led_card.get_suit()) {
            //b is led card suit and a isn't
            return true;
        }
        else {
            return a < b;
        }
    }
    return Card_less(a, b, trump);
}
