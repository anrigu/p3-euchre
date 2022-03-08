// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>
#include <string>
#include "Pack.h"

using namespace std;

class Game {
private:
    vector<Player*> players;
    Pack pack;
    bool shuffleCards;
    int numWinPoints;
    string trumpSuit;
    Player* dealer;

public:
    Game(string shuffle_in, int numWinPoints_in, string name_in_1, string type_in_1,string name_in_2, string type_in_2, string name_in_3, string type_in_3, string name_in_4, string type_in_4)
        : numWinPoints(numWinPoints_in) {
            players = {Player_factory(name_in_1, type_in_1), Player_factory(name_in_2, type_in_2), Player_factory(name_in_3, type_in_3), Player_factory(name_in_4, type_in_4)};
            dealer = players[0];
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

    }

};
