#ifndef TILE_H
#define TILE_H

#define RED          'R'
#define YELLOW       'Y'
#define DARK_BLUE    'B'
#define LIGHT_BLUE   'L'
#define BLACK        'U'
#define FIRST_PLAYER 'F'
#define NO_TILE      '.'


class Tile {
public:
    Tile(char colour);
    ~Tile();
    char getColour();
    void setColour(char colour);
    

private:
    char colour;
};

typedef Tile* TilePtr;

#endif //TILE_H