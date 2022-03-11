// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>
#include <string>
#include "Pack.h"

using namespace std;

class Game {
private:
    vector<Player*> players;
    //dealer will always be at index 0
    Pack pack;
    bool shuffleCards;
    int numWinPoints;
    int trumpPartnershipWins;
    string trumpSuit;
    int leadPlayer;
    int orderUpPlayer;

public:
    Game(string shuffle_in, int numWinPoints_in, string name_in_1, string type_in_1,string name_in_2, string type_in_2, string name_in_3, string type_in_3, string name_in_4, string type_in_4)
        : numWinPoints(numWinPoints_in) {
            players = {Player_factory(name_in_1, type_in_1), Player_factory(name_in_2, type_in_2), Player_factory(name_in_3, type_in_3), Player_factory(name_in_4, type_in_4)};
            leadPlayer = 1;
            trumpPartnershipWins = 0;
            orderUpPlayer = 0;
            if (shuffle_in == "shuffle") {
                shuffleCards = true;
            }
            else {
                shuffleCards = false;
            }
        }

    void shuffle() {
        if (shuffleCards) {
            pack.shuffle();
        }
    }

    void dealCards() {
        int increment = 0;
        while(!pack.empty()) {
            Card currCard = pack.deal_one();
            players[increment % 4]->add_card(currCard);
            increment ++;
        }
    }

    void decideTrump() {
        const Card upcard = pack.deal_one();
        int currBidder = 0;
        trumpSuit = upcard.get_suit();
        for (int round = 1; round <= 2; round ++) {
            if (currBidder > 3) {
                currBidder %= 3;
            }
            if (players[currBidder]->make_trump(upcard, currBidder == 0,
                                                round, trumpSuit)) {
                if (round == 1) {
                    players[currBidder]->add_and_discard(upcard);
                }
                orderUpPlayer = currBidder;
                break;
            }
            currBidder ++;
        }
    }

    void playedCards() {
        int maxPlayerInd = leadPlayer;
        Card maxCard = players[leadPlayer]->lead_card(trumpSuit);
        leadPlayer ++;
        int play = 1;
        while (play != 4) {
            if (leadPlayer > 3) {
                leadPlayer %= 3;
            }
            Card playedCard = players[leadPlayer]->play_card(maxCard, trumpSuit);
            if (!Card_less(playedCard, maxCard, trumpSuit)) {
                maxCard = playedCard;
                maxPlayerInd = leadPlayer;
            }
            play ++;
            leadPlayer ++;
        }
        if (maxPlayerInd == orderUpPlayer || maxPlayerInd == orderUpPlayer + 2) {
            trumpPartnershipWins ++;
        }
        leadPlayer = maxPlayerInd;
    }


};
