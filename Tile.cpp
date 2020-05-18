#include "Tile.h"

Tile::Tile(char colour) {
    this->colour = colour;
}


Tile::~Tile() {
}

char Tile::getColour() {
    return this->colour;
}

void Tile::setColour(char colour){
    this->colour = colour;
}

