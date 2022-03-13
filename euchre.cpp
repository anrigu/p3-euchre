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
    string trumpSuit;
    int leadPlayer;
    int orderUpPlayer;
    int partner0and2;
    int partner1and3;
    int handNum;

public:
    Game(string shuffle_in, int numWinPoints_in, char *argv[], Pack pack_in)
    : numWinPoints(numWinPoints_in), pack(pack_in) {
        players = {Player_factory(argv[4], argv[5]),
            Player_factory(argv[6], argv[7]), Player_factory(argv[8], argv[9]),
            Player_factory(argv[10], argv[11])};
        leadPlayer = 1;
        partner0and2 = 0;
        partner1and3 = 0;
        handNum = 0;
        trumpPartnershipWins = 0;
        trumpCard = Card();
        trumpSuit = trumpCard.get_suit();
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
        Player *temp = players[0];
        for (int i = 1; i < static_cast<int>(players.size()); i++) {
            players[i - 1] = players[i];
        }
        players[static_cast<int>(players.size() - 1)] = temp;
    }

    void dealCards() {
        players[1]->add_card(pack.deal_one());
        players[1]->add_card(pack.deal_one());
        players[1]->add_card(pack.deal_one());
        players[2]->add_card(pack.deal_one());
        players[2]->add_card(pack.deal_one());
        players[3]->add_card(pack.deal_one());
        players[3]->add_card(pack.deal_one());
        players[3]->add_card(pack.deal_one());
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
        players[0]->add_card(pack.deal_one());
    }

    void decideTrump() {
        int currBidder = 1;
        int iterator = currBidder;
        trumpCard = pack.deal_one();
        trumpSuit = trumpCard.get_suit();
        cout << "Hand " << handNum << endl;
        cout << players[0]->get_name() << " deals" << endl;
        cout << trumpCard.get_rank() << " of " << trumpCard.get_suit()
        << " turned up" << endl;
        for (int round = 1; round <= 2; round ++) {
            while (currBidder <= 4) {
                iterator = currBidder;
                if (currBidder == 4) {
                    iterator = 0;
                }
                if (players[iterator]->make_trump(trumpCard, iterator == 0,
                                                    round, trumpSuit)) {
                    cout << players[iterator]->get_name()
                         << " orders up " << trumpSuit << endl << endl;
                    if (round == 1) {
                        players[0]->add_and_discard(trumpCard);
                    }
                    orderUpPlayer = iterator;
                    currBidder = 5; //To break the loop
                    round = 3;
                }
                else {
                    cout << players[iterator]->get_name() << " passes" << endl;
                }
                currBidder ++;
            }
            currBidder = 1;

        }
        handNum ++;
    }

    void playedCards() {
        int maxPlayerInd = leadPlayer;
        Card maxCard = players[leadPlayer]->lead_card(trumpSuit);
        Card ledCard = maxCard;
        cout << maxCard.get_rank() << " of " << maxCard.get_suit()
             << " led by " << players[leadPlayer]->get_name() << endl;
        leadPlayer ++;
        int play = 1;
        while (play != 4) {
            if (leadPlayer > 3) {
                leadPlayer %= 4;
            }
            Card playedCard = players[leadPlayer]->play_card(maxCard,
                                                             trumpSuit);
            cout << playedCard.get_rank() << " of " << playedCard.get_suit()
                 << " played by " << players[leadPlayer]->get_name() << endl;
            if (!Card_less(playedCard, maxCard, ledCard, trumpSuit)) {
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
                cout << players[1]->get_name() << " and " << players[3]->get_name()
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
        leadPlayer = 1;

    }

    void scorePrint() {
        cout << players[0]->get_name() << " and "
             << players[2]->get_name() << " have " << partner0and2 << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name()
             << " have " << partner1and3 << " points" << endl << endl;
    }

    bool gameOver() {
        if (partner0and2 >= numWinPoints) {
            cout << players[0]->get_name() << " and "
            << players[2]->get_name() << " wins!" << endl;
            return true;
        }
        else if (partner1and3 >= numWinPoints) {
            cout << players[1]->get_name() << " and "
            << players[3]->get_name() << " wins!" << endl;
            return true;
        }
        rearrangeDealer();
        pack.reset();
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
    string shuffleParam = argv[2];
    if (shuffleParam != "shuffle" && shuffleParam != "noshuffle") {
        return false;
    }
    string playerType[4] = {argv[5], argv[7], argv[9], argv[11]};
    for (int i = 0; i < 4; i ++) {
        if (playerType[i] != "Simple" && playerType[i] != "Human") {
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
    Pack pack(in);
    Game game(shuffle, numPointsWin, argv, pack);
    bool gameIsOver = false;
    while (!gameIsOver) {
        game.shuffle();
        game.dealCards();
        game.decideTrump();
        game.roundPlay();
        game.gamePointTrack();
        game.scorePrint();
        if (game.gameOver()) {
            gameIsOver = true;
        }
    }
}
