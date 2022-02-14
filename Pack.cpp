// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include <array>
#include <string>

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    int cards_ind = 0;
    for (int i = 0; i < NUM_SUITS; i++) {
        for (int j = 7; j < NUM_RANKS; j++) {
            cards[cards_ind] = Card(SUIT_NAMES_BY_WEIGHT[i], RANK_NAMES_BY_WEIGHT[j]);
        }
    }
    //See what to do w/ this later
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    string rank;
    string buffer;
    string suit;
    int i = 0;
    while (pack_input >> rank >> buffer >> suit) {
        cards[i] = Card(rank,suit);
        i++;
    }
    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    return cards[next++];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    array<Card, PACK_SIZE/2>cards_top;
    array<Card, PACK_SIZE/2>cards_bottom;
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < PACK_SIZE; i++) {
            if (i < PACK_SIZE / 2) {
                cards_bottom[i] = cards[i];
            }
            else {
                cards_top[i - PACK_SIZE/2] = cards[i];
            }
        }

        array<Card, PACK_SIZE>newCards;
        int counter = 0;
        for (int m = 0; m < PACK_SIZE/2; m++) {
            newCards[counter++] = cards_top[m];
            newCards[counter++] = cards_bottom[m];
        }
        cards = newCards;
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {

}
