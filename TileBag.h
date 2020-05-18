#ifndef TILEBAG_H
#define TILEBAG_H

#include "Tile.h"
#include <istream>

class Node {
public:
    Node(TilePtr tile, Node* next);
    Node(Node& other);

    TilePtr tile;
    Node* next;
};

class TileBag {
public:
    TileBag();
    ~TileBag();

    unsigned int size();
    void addTile(TilePtr tile);
    void removeTileFront();
    TilePtr getHead();
    void clear();
    void loadTileBag(std::istream& inputStream);
    /* int calculateRandom();
    int getCurrent(); 
    void shuffle(int seed);*/
private:
    Node* head;
    int length;
};

#endif //TILEBAG_H