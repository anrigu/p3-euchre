// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <sstream>
#include "unit_test_framework.h"
#include "Card.cpp"

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
    ASSERT_FALSE(jack_diamonds < jack_hearts);
    ASSERT_TRUE(jack_diamonds <= jack_diamonds);
    ASSERT_FALSE(jack_diamonds <= jack_hearts);
    ASSERT_FALSE(jack_diamonds < jack_hearts);
    ASSERT_TRUE(jack_diamonds >= jack_hearts);
    ASSERT_TRUE(jack_hearts == jack_hearts);
    ASSERT_FALSE(jack_hearts != jack_hearts);
    ASSERT_TRUE(jack_hearts != jack_diamonds);
}

TEST(test_card_less_with_trump) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, SUIT_NAMES_BY_WEIGHT[0]));
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, SUIT_NAMES_BY_WEIGHT[2]));
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(nine_spades, jack_clubs, SUIT_NAMES_BY_WEIGHT[0]));
    ASSERT_FALSE(Card_less(jack_clubs, nine_spades, SUIT_NAMES_BY_WEIGHT[1]));
    ASSERT_TRUE(Card_less(nine_spades, nine_hearts, SUIT_NAMES_BY_WEIGHT[1]));
    ASSERT_TRUE(Card_less(king_hearts, ace_hearts, SUIT_NAMES_BY_WEIGHT[1]));
    ASSERT_TRUE(Card_less(king_hearts, ace_hearts, SUIT_NAMES_BY_WEIGHT[0]));
    ASSERT_TRUE(Card_less(jack_spades, ace_hearts, SUIT_NAMES_BY_WEIGHT[3]));
}

TEST(test_card_less_ledsuit) {
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    // a is led
    ASSERT_FALSE(Card_less(nine_spades, jack_clubs, ten_spades, SUIT_NAMES_BY_WEIGHT[1]));
    ASSERT_TRUE(Card_less(nine_spades, jack_clubs, ten_spades, SUIT_NAMES_BY_WEIGHT[2]));
    ASSERT_TRUE(Card_less(nine_spades, nine_hearts, ten_spades, SUIT_NAMES_BY_WEIGHT[1]));
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, ace_spades, SUIT_NAMES_BY_WEIGHT[2]));
    ASSERT_TRUE(Card_less(jack_spades, jack_hearts, ace_spades, SUIT_NAMES_BY_WEIGHT[1]));
    // b is led
    ASSERT_TRUE(Card_less(nine_spades, jack_clubs, nine_clubs, SUIT_NAMES_BY_WEIGHT[1]));
    ASSERT_TRUE(Card_less(nine_spades, jack_clubs, nine_clubs, SUIT_NAMES_BY_WEIGHT[0]));
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, nine_clubs, SUIT_NAMES_BY_WEIGHT[0]));
    ASSERT_TRUE(Card_less(jack_spades, nine_hearts, ten_hearts, SUIT_NAMES_BY_WEIGHT[3]));
    // both aren't led
    ASSERT_FALSE(Card_less(nine_spades, nine_hearts, nine_clubs, SUIT_NAMES_BY_WEIGHT[0]));
    ASSERT_TRUE(Card_less(nine_spades, nine_hearts, ten_hearts, SUIT_NAMES_BY_WEIGHT[3]));



}



TEST_MAIN()