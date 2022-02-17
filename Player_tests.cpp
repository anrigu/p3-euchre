// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <sstream>
#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    //MAX 5 Cards
    alice->add_card(jack_clubs);
    alice->add_card(jack_spades);
    alice->add_card(queen_spades);
    alice->add_card(ten_diamonds);
    alice->add_card(nine_spades);
    string trump;
    ASSERT_TRUE(alice->make_trump(king_spades, false, 1, trump));
    ASSERT_FALSE(alice->make_trump(ten_diamonds, false, 1, trump));
    ASSERT_TRUE(alice->make_trump(ten_clubs, true, 1, trump));

    Player * melissa = Player_factory("Mel", "Simple");
    melissa->add_card(king_hearts);
    melissa->add_card(king_diamonds);
    melissa->add_card(queen_spades);
    melissa->add_card(ten_diamonds);
    melissa->add_card(nine_spades);

    ASSERT_FALSE(melissa->make_trump(ten_hearts, true, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    ASSERT_TRUE(melissa->make_trump(ten_hearts, false, 2, trump));
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(melissa->make_trump(nine_spades, true, 2, trump));
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    ASSERT_FALSE(melissa->make_trump(ten_spades, false, 2, trump));

    delete alice;
    delete melissa;
}

TEST(test_player_add_discard) {
    Player * jason = Player_factory("Jason", "Simple");

    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    jason->add_card(nine_diamonds);
    jason->add_card(jack_diamonds);
    jason->add_card(king_diamonds);
    jason->add_card(king_hearts);
    jason->add_card(jack_spades);

    string trump;
    ASSERT_TRUE(jason->make_trump(nine_diamonds, true, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

    jason->add_and_discard(queen_spades);
    jason->add_and_discard(king_spades);

    ASSERT_TRUE(jason->make_trump(nine_spades, true, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    delete jason;
}

TEST(test_player_lead_card) {
    Player * adi = Player_factory("Adi", "Simple");
    Player * james = Player_factory("James", "Simple");

    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);


    adi->add_card(nine_diamonds);
    adi->add_card(jack_diamonds);
    adi->add_card(king_diamonds);
    adi->add_card(king_hearts);
    adi->add_card(jack_spades);

    james->add_card(nine_spades);
    james->add_card(ten_spades);
    james->add_card(jack_spades);
    james->add_card(queen_spades);
    james->add_card(king_spades);


    string trump;
    ASSERT_TRUE(adi->make_trump(ten_diamonds, true, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

    ASSERT_EQUAL(adi->lead_card(trump), king_hearts);

    ASSERT_TRUE(adi->make_trump(ten_diamonds, false, 2, trump));
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    ASSERT_EQUAL(adi->lead_card(trump), king_diamonds);

    ASSERT_TRUE(james->make_trump(ace_spades, false, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    ASSERT_EQUAL(james->lead_card(trump), jack_spades);

    ASSERT_TRUE(james->make_trump(ten_clubs, true, 2, trump));
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    ASSERT_EQUAL(james->lead_card(trump), jack_spades);

    delete adi;
    delete james;
}

TEST(test_player_play_card) {
    Player * kris = Player_factory("Kris", "Simple");
    Player * adi = Player_factory("Adi", "Simple");

    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);

    kris->add_card(nine_spades);
    kris->add_card(ten_spades);
    kris->add_card(jack_spades);
    kris->add_card(queen_spades);
    kris->add_card(king_spades);

    adi->add_card(nine_diamonds);
    adi->add_card(jack_diamonds);
    adi->add_card(king_diamonds);
    adi->add_card(king_hearts);
    adi->add_card(jack_spades);

    string trump;

    ASSERT_TRUE(adi->make_trump(ten_diamonds, false, 2, trump));
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    ASSERT_EQUAL(king_spades, kris->play_card(ace_spades, trump));

    ASSERT_TRUE(kris->make_trump(ace_spades, false, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    kris->add_card(ten_hearts);
    ASSERT_EQUAL(ten_hearts, kris->play_card(ten_diamonds, trump));
    ASSERT_EQUAL(jack_spades, kris->play_card(ace_spades, trump));

    ASSERT_EQUAL(queen_spades, kris->play_card(ace_spades, trump));

    kris->add_card(jack_spades);
    kris->add_card(jack_clubs);

    ASSERT_EQUAL(jack_spades, kris->play_card(ace_spades, trump));
    ASSERT_EQUAL(jack_clubs, kris->play_card(ace_spades, trump));

    delete kris;
    delete adi;
}

TEST_MAIN()
