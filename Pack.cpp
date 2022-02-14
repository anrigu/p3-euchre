// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include "Card.h"
#include <array>
#include <string>

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

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream & pack_input) {
        string str = " ";
        // is this right? just a lil confused
        for (int i = 0; i < PACK_SIZE; i++) {
            pack_input >> card[i].get_rank() >> str >> card[i].get_suit();
        }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() {
      int index = 0;
    //next index in a temporary variable, increment the index, and return the next card using the index of the temporary variable
       
  }

  // EFFECTS: Resets next index to first card in the Pack
  void reset();

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void shuffle();

  // EFFECTS: returns true if there are no more cards left in the pack
  bool empty() const;

private:
  static const int PACK_SIZE = 24;
  std::array<Card, PACK_SIZE> cards;
  int next; //index of next card to be dealt
};

#endif
