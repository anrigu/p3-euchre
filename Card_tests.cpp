// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <sstream>
#include "unit_test_framework.h"
#include "Card.h"

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
    Card c3;
    ASSERT_EQUAL(Card::RANK_TWO, c3.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c3.get_suit());
}

TEST(test_card_get_suit) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_HEARTS), Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);
}

TEST(test_card_is_face) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(jack_spades.is_face());
    ASSERT_FALSE(nine_diamonds.is_face());
}

TEST(test_bower) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(nine_diamonds.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card::RANK_JACK, jack_spades.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, jack_spades.get_suit());
    ASSERT_TRUE(jack_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(jack_spades.is_left_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_spades.is_face());
    ASSERT_FALSE(jack_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_SPADES));
    ASSERT_FALSE(jack_spades.is_trump(Card::SUIT_DIAMONDS));
}

TEST(test_comparison) {
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_FALSE(jack_diamonds < jack_hearts);
    ASSERT_TRUE(jack_diamonds <= jack_diamonds);
    ASSERT_FALSE(jack_diamonds <= jack_hearts);
    ASSERT_FALSE(jack_diamonds < jack_hearts);
    ASSERT_TRUE(jack_diamonds >= jack_hearts);
    ASSERT_TRUE(jack_hearts == jack_hearts);
    ASSERT_TRUE(ace_hearts != ace_spades);
    ASSERT_TRUE(ace_spades >= jack_hearts);
    ASSERT_TRUE(ace_spades > jack_diamonds);
    ASSERT_FALSE(ace_spades < jack_diamonds);
    ASSERT_FALSE(ace_spades <= jack_diamonds);

}

//    Card::SUIT_SPADES,
//    Card::SUIT_HEARTS,
//    Card::SUIT_CLUBS,
//    Card::SUIT_DIAMONDS

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

TEST(test_card_less_with_trump2) {
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(jack_spades, queen_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(king_spades, queen_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_clubs, queen_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_hearts, nine_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(king_hearts, nine_spades, Card::SUIT_HEARTS));
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

TEST(test_operators) {
    Card twoSpades;
    Card kingDiamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card aceSpades(Card::RANK_ACE, Card::SUIT_SPADES);
    ostringstream oss1;
    oss1 << twoSpades;

    ostringstream oss2;
    oss2 << kingDiamonds;

    ostringstream oss3;
    oss3 << aceSpades;

    ASSERT_EQUAL(oss3.str(), "Ace of Spades");

    // Verify that the output is the player's name
    ASSERT_EQUAL(oss1.str(), "Two of Spades");
    ASSERT_EQUAL(oss2.str(), "King of Diamonds");
    ASSERT_TRUE(twoSpades != kingDiamonds)

    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);

}


TEST_MAIN()
