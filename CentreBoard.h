#ifndef CENTREBOARD_H
#define CENTREBOARD_H

#include "TileBag.h"
#include <vector>
#include <iostream>
#include "Tile.h"

#define MAX_FACTORY 5
#define MAX_TILES_PER_FACTORY 4

class GameEngine;

class CentreBoard{
public:
    CentreBoard();
    ~CentreBoard();

    int getNumTilesInFactory(char colour, int row);
    void newRound(GameEngine ge);
    TilePtr** getFactories();
    std::vector<TilePtr> getCentralFactory();
    void printCentralFactory();
    void printFactories();
    void emptyFactories();
    bool checkEmpty();
    void shuffleTileBag(int seed);
    bool fillTileBag(int value);
    void populateFactories();
    void moveTilesToCentralFactory(char colour, int row);
private:
    TilePtr** factories;
    std::vector<TilePtr> centralFactory;
    std::vector<TilePtr> boxLid;
    TileBag* tileBag;
    int dbToFill;
    int yToFill;
    int rToFill;
    int bToFill;
    int lbToFill;
};

#endif //CENTREBOARD_H
