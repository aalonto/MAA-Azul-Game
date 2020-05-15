#ifndef MOSAIC_H 
#define MOSAIC_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Tile.h"

#define MAX_MOSAIC_ROWS 5
#define MAX_MOSAIC_COLS 5


class Mosaic{
    public:
    Mosaic();
    ~Mosaic();
    TilePtr* getLine(int pos);
    TilePtr* getBroken();
    TilePtr** getBoard();
    void placeTiles(int storageRow, char colour, int numTiles);
    void placeBroken(Tile tile, int numTiles);
    void moveTile();
    void clearStorageRow(int row);
    bool isStorageComplete(int line);
    int indexToMove(char colour, int row);
    char getTileToMove(int line);
    bool checkForCompleteLine();

    //char getLine(int i, line1 Line1, line2 Line2, line3 Line3, line4 Line4, line5 Line5);

private:
    TilePtr** board;
    TilePtr* line1;
    TilePtr* line2;
    TilePtr* line3;
    TilePtr* line4;
    TilePtr* line5;
    TilePtr* broken;
};

#endif //MOSAIC_H