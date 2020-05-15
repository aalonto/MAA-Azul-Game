#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include <iostream>
#include "Player.h"
#include "CentreBoard.h"

#define MAX_PLAYER 2

class GameEngine{
public:
    GameEngine();
    ~GameEngine();

    void newPlayers();
    void playGame();
    char getColourFromInput(std::string colour);
    void displayPlayerMosaic(Player* current);
    void playerTurn(int playerTurn, CentreBoard board);
    void finalResults(Player playerlist[]);
    void checkEndRound();
    void checkFinished();
    void calculateRound();

    Player* getPlayer(int i);
    CentreBoard* getCentreBoard();
    bool isFinished();
    TileBag getTileBag();
    std::vector<Tile> getBoxLid();

private:
    Player* player1;
    Player* player2;
    Player** players;
    CentreBoard* centreBoard;
    bool finished;
    bool endRound;
};

#endif //GAME_ENGINE_H