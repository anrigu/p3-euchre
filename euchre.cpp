// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>
#include <string>
#include "Pack.h"
#include <fstream>

using namespace std;

class PointKeeping {
private:
    string partner1;
    string partner2;
    int numPoints;
public:
    PointKeeping()
    : partner1(""), partner2(""), numPoints(0) {}

    PointKeeping(string partner1_in, string partner2_in)
    : partner1(partner1_in), partner2(partner2_in), numPoints(0) {}

    bool checkPartnership(string name1) {
        return name1 == partner1 || name1 == partner2;
    }
    void addPoints(int numAdd) {
        numPoints += numAdd;
    }
    int getNumPoints() {
        return numPoints;
    }
    string getPartner1() {
        return partner1;
    }
    string getPartner2() {
        return partner2;
    }
};

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
    PointKeeping partner0_2;
    PointKeeping partner1_3;
    int handNum;

public:
    Game(string shuffle_in, int numWinPoints_in, char *argv[], Pack pack_in)
    : pack(pack_in), numWinPoints(numWinPoints_in) {
        players = {Player_factory(argv[4], argv[5]),
            Player_factory(argv[6], argv[7]), Player_factory(argv[8], argv[9]),
            Player_factory(argv[10], argv[11])};
        leadPlayer = 1;
        partner0_2 = PointKeeping(players[0]->get_name(), players[2]->get_name());
        partner1_3 = PointKeeping(players[1]->get_name(), players[3]->get_name());
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
                bool orderedUp = players[iterator]->make_trump(trumpCard, iterator == 0,
                                                               round, trumpSuit);
                if (orderedUp && round == 1) {
                    cout << players[iterator]->get_name()
                    << " orders up " << trumpSuit << endl;
                    players[0]->add_and_discard(trumpCard);
                    cout << endl;
                    orderUpPlayer = iterator;
                    currBidder = 5; //To break the loop
                    round = 3;
                }
                else if (orderedUp) {
                    cout << players[iterator]->get_name()
                    << " orders up " << trumpSuit << endl;
                    cout << endl;
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
            Card playedCard = players[leadPlayer]->play_card(ledCard,
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
        if (maxPlayerInd % 2 == orderUpPlayer % 2) {
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

    void majorityHandsWon(PointKeeping *partnership1, PointKeeping *partnership2) {
        if (trumpPartnershipWins > 2 && trumpPartnershipWins < 5) {
            partnership1->addPoints(1);
            cout << partnership1->getPartner1()
                 << " and " << partnership1->getPartner2()
                 << " win the hand" << endl;
            return;
        }
        else if(trumpPartnershipWins == 5) {
            partnership1->addPoints(2);
            cout << partnership1->getPartner1()
                 << " and " << partnership1->getPartner2()
                 << " win the hand" << endl;
            cout << "march!" << endl;
            return;
        }
        else {
            partnership2->addPoints(2);
            cout << partnership2->getPartner1()
                 << " and " << partnership2->getPartner2()
                 << " win the hand" << endl;
            cout << "euchred!" << endl;
            return;
        }
    }

    void gamePointTrack() {
        //If the original 0_2 partnership were trump
        if (partner0_2.checkPartnership(players[orderUpPlayer]->get_name())) {
            majorityHandsWon(&partner0_2, &partner1_3);
        }
        else {
            majorityHandsWon(&partner1_3, &partner0_2);
        }
        trumpPartnershipWins = 0;
        leadPlayer = 1;
    }

    void scorePrint() {
        cout << partner0_2.getPartner1() << " and "
        << partner0_2.getPartner2() << " have "
        << partner0_2.getNumPoints() << " points" << endl;
        cout << partner1_3.getPartner1() << " and "
        << partner1_3.getPartner2() << " have "
        << partner1_3.getNumPoints() << " points" << endl << endl;
    }

    bool gameOver() {
        if (partner0_2.getNumPoints() >= numWinPoints) {
            cout << partner0_2.getPartner1() << " and "
            << partner0_2.getPartner2() << " win!" << endl;
            delete players[0];
            delete players[1];
            delete players[2];
            delete players[3];
            return true;
        }
        else if (partner1_3.getNumPoints() >= numWinPoints) {
            cout << partner1_3.getPartner1() << " and "
            << partner1_3.getPartner2() << " win!" << endl;
            delete players[0];
            delete players[1];
            delete players[2];
            delete players[3];
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

void printArgs(char* argv[], int argc) {
    for(int i = 0; i < argc; i++) {
            cout << argv[i] << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    if (!checkErrors(argc, argv)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    printArgs(argv, argc);
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
    in.close();
}
