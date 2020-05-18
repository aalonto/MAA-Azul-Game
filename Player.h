#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Mosaic.h"

class Player {
public:
    Player(std::string playerName);
    Player(Player& other);
    ~Player();

    std::string getPlayerName();
    Mosaic* getMosaic();
    int getPoints();
    void setPoints(int points);
    void updatePoints(int points);
    void setPointsforRound(int points);
    int getPointsForRound();
private:
    std::string playerName;
    Mosaic* mosaic;
    int points;
    int pointsForRound;
};

#endif //PLAYER_H