// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::RANK_JACK, c1.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c1.get_suit());
    Card c2(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::RANK_TWO, c2.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c2.get_suit());
}
TEST(test_bower) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::RANK_JACK, jack_spades.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, jack_spades.get_suit());
    ASSERT_TRUE(jack_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_face());
    ASSERT_FALSE(jack_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_SPADES));
    ASSERT_FALSE(jack_spades.is_trump(Card::SUIT_DIAMONDS));
}

TEST(test_comparison) {
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    if (get_suit(trump) == SUIT_DIAMONDS) { // is this how you write this?
        ASSERT_TRUE(jack_diamonds > jack_hearts)
    }
    ASSERT_TRUE(jack_hearts != jack_diamonds);
}


TEST_MAIN()
