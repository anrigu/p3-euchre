// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>
#include <string>
#include "Pack.h"
#include <fstream>

using namespace std;

class Game {
private:
    vector<Player*> players;
    //dealer will always be at index 0
    Pack pack;
    bool shuffleCards;
    int numWinPoints;
    int trumpPartnershipWins;
    Card trumpCard;
    int leadPlayer;
    int orderUpPlayer;
    int partner0and2;
    int partner1and3;

public:
    Game(string shuffle_in, int numWinPoints_in, string name_in_1, string type_in_1,string name_in_2, string type_in_2, string name_in_3, string type_in_3, string name_in_4, string type_in_4)
    : numWinPoints(numWinPoints_in) {
        players = {Player_factory(name_in_1, type_in_1), Player_factory(name_in_2, type_in_2), Player_factory(name_in_3, type_in_3), Player_factory(name_in_4, type_in_4)};
        leadPlayer = 1;
        partner0and2 = 0;
        partner1and3 = 0;
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

    void rearrangeDealer() {
        Player *temp = players[players.size() - 1];
        Player *temp2;
        for (int i = 1; i < players.size(); i++) {
            temp2 = players[0];
            players[0] = players[i];
            players[i] = temp2;
        }
        players[0] = temp;
    }

    void dealCards() {
        players[0]->add_card(pack.deal_one());
        players[0]->add_card(pack.deal_one());
        players[0]->add_card(pack.deal_one());
        players[1]->add_card(pack.deal_one());
        players[1]->add_card(pack.deal_one());
        players[2]->add_card(pack.deal_one());
        players[2]->add_card(pack.deal_one());
        players[2]->add_card(pack.deal_one());
        players[3]->add_card(pack.deal_one());
        players[3]->add_card(pack.deal_one());
        players[0]->add_card(pack.deal_one());
        players[0]->add_card(pack.deal_one());
        players[1]->add_card(pack.deal_one());
        players[1]->add_card(pack.deal_one());
        players[1]->add_card(pack.deal_one());
        players[2]->add_card(pack.deal_one());
        players[2]->add_card(pack.deal_one());
        players[3]->add_card(pack.deal_one());
        players[3]->add_card(pack.deal_one());
        players[3]->add_card(pack.deal_one());
    }

    void decideTrump() {
        int currBidder = 0;
        trumpCard = pack.deal_one();
        string trumpSuit = trumpCard.get_suit();
        for (int round = 1; round <= 2; round ++) {
            while (currBidder <= 3) {
                if (players[currBidder]->make_trump(trumpCard, currBidder == 0,
                                                    round, trumpSuit)) {
                    if (round == 1) {
                        players[currBidder]->add_and_discard(trumpCard);
                    }
                    orderUpPlayer = currBidder;
                    cout << players[currBidder]->get_name() << " orders up "
                    << trumpSuit << endl << endl;
                    break;
                }
                else {
                    cout << players[currBidder]->get_name() << " passes" << endl;
                }
                currBidder ++;
            }
            currBidder = 0;
        }
    }

    void playedCards() {
        int maxPlayerInd = leadPlayer;
        Card maxCard = players[leadPlayer]->lead_card(trumpCard.get_suit());
        leadPlayer ++;
        int play = 1;
        while (play != 4) {
            if (leadPlayer > 3) {
                leadPlayer %= 4;
            }
            Card playedCard = players[leadPlayer]->play_card(maxCard, trumpCard.get_suit());
            cout << playedCard.get_rank() << " of " << playedCard.get_suit() << " led by "
            << players[leadPlayer]->get_name() << endl;
            if (!Card_less(playedCard, maxCard, trumpCard.get_suit())) {
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
        cout << players[leadPlayer]->get_name() << " takes the trick" << endl << endl;
    }

    void roundPlay() {
        for (int i = 0; i < 5; i++) {
            cout << "Hand " << i << endl;
            cout << players[0]->get_name() << " deals" << endl;
            cout << trumpCard.get_rank() << " of " << trumpCard.get_suit()
            << " turned up" << endl << endl;
            playedCards();
        }
    }

    void gamePointTrack() {
        if(orderUpPlayer == 0 || orderUpPlayer == 2 ) {
            if(trumpPartnershipWins > 2 && trumpPartnershipWins < 5) {
                partner0and2++;
                cout << players[0]->get_name() << " and " << players[2]->get_name()
                << " win the hand" << endl;
            }
            else if(trumpPartnershipWins == 5){
                partner0and2 += 2;
                cout << players[0]->get_name() << " and " << players[2]->get_name()
                << " win the hand" << endl;
                cout << "march!" << endl;
            }
            else {
                partner1and3 +=2;
                cout << players[0]->get_name() << " and " << players[2]->get_name()
                << " win the hand" << endl;
                cout << "euchred!" << endl;
            }
        }
        else if(orderUpPlayer == 1 || orderUpPlayer == 3 ) {
            if(trumpPartnershipWins > 2 && trumpPartnershipWins < 5) {
                partner1and3++;
                cout << players[1]->get_name() << " and " << players[3]->get_name()
                << " win the hand" << endl;
            }
            else if(trumpPartnershipWins == 5){
                partner1and3 += 2;
                cout << players[1]->get_name() << " and " << players[3]->get_name()
                << " win the hand" << endl;
                cout << "march!" << endl;
            }
            else {
                partner0and2 +=2;
                cout << players[0]->get_name() << " and " << players[2]->get_name()
                << " win the hand" << endl;
                cout << "euchred!" << endl;
            }
        }
        trumpPartnershipWins = 0;
        rearrangeDealer();
        leadPlayer = 1;

    }

    void scorePrint() {
        cout << players[0]->get_name() << " and "
             << players[2]->get_name() << " have " << partner0and2 << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name()
             << " have " << partner1and3 << " points" << endl << endl;
    }


    bool gameOver() {
        if (partner0and2 == numWinPoints) {
            cout << players[0]->get_name() << " and "
            << players[2]->get_name() << " wins!" << endl;
            return true;
        }
        else if (partner1and3 == numWinPoints) {
            cout << players[1]->get_name() << " and "
            << players[3]->get_name() << " wins!" << endl;
            return true;
        }
        return false;
    }

};

bool checkErrors(int argc, char* argv[]) {
    if (argc != 12) {
        return false;
    }
    int numPoints = atoi(argv[3]);
    if (numPoints < 1 || numPoints > 100) {
        return false;
    }
    string shuffleParam = argv[4];
    if (shuffleParam != "shuffle" || shuffleParam != "noshuffle") {
        return false;
    }
    string playerType[4] = {argv[5], argv[7], argv[9], argv[11]};
    for (int i = 0; i < 4; i ++) {
        if (playerType[i] != "Simple" || playerType[i] != "Human") {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (!checkErrors(argc, argv)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    ifstream in;
    string pack_filename = argv[1];
    in.open(pack_filename);
    if (!in.is_open()) {
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }
    string shuffle = argv[2];
    int numPointsWin = atoi(argv[3]);
    string play1 = argv[4];
    string type1 = argv[5];
    string play2 = argv[6];
    string type2 = argv[7];
    string play3 = argv[8];
    string type3 = argv[9];
    string play4 = argv[10];
    string type4 = argv[11];

    Game game(shuffle, numPointsWin, play1, type1, play2,
              type2, play3, type3, play4, type4);

    while (!game.gameOver()) {
        game.shuffle();
        game.dealCards();
        game.decideTrump();
        game.roundPlay();
        game.gamePointTrack();
        game.scorePrint();
    }
}
