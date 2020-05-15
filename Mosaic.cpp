#include "Mosaic.h"

Mosaic::Mosaic() {
    board = new TilePtr*[MAX_MOSAIC_ROWS];
    for(int i = 0; i != MAX_MOSAIC_ROWS; ++i) {
        board[i]= new TilePtr[MAX_MOSAIC_COLS];

        for(int j=0; j != MAX_MOSAIC_COLS; ++j) {
            board[i][j] = new Tile(NO_TILE);
        }
    }

    line1 = new TilePtr[1];
    for(int i=0; i != 1; ++i) {
        line1[i] = new Tile(NO_TILE);
    }    

    line2 = new TilePtr[2];
    for(int i=0; i != 2; ++i) {
        line2[i] = new Tile(NO_TILE);
    }  

    line3 = new TilePtr[3];
    for(int i=0; i < 3; ++i) {
        line3[i] = new Tile(NO_TILE);
    }

    line4 = new TilePtr[4];
    for(int i=0; i < 4; ++i) {
        line4[i] = new Tile(NO_TILE);
    } 

    line5 = new TilePtr[5];
    for(int i=0; i < 5; ++i) {
        line5[i] = new Tile(NO_TILE);
    }

    broken = new TilePtr[7];;
    for(int i=0; i < 7; ++i) {
        broken[i] = nullptr;
    } 
}

Mosaic::~Mosaic() {
    for(int i = 0; i != MAX_MOSAIC_ROWS; ++i) {
        for(int j = 0; j != MAX_MOSAIC_COLS; ++j) {
            if(board != nullptr) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }

    if(line1[0] != nullptr) {
        delete line1[0];
        line1[0] = nullptr;
    }

    for(int i = 0; i != 2; ++i) {
        if(line2[i] != nullptr) {
            delete line2[i];
            line2[i] = nullptr;
        }
    }

    for(int i = 0; i != 3; ++i) {
        if(line3[i] != nullptr) {
            delete line3[i];
            line3[i] = nullptr;
        }
    }
    
    for(int i = 0; i != 4; ++i) {
        if(line4[i] != nullptr) {
            delete line4[i];
            line4[i] = nullptr;
        }
    }
    
    for(int i = 0; i != 5; ++i) {
        if(line5[i] != nullptr) {
            delete line5[i];
            line5[i] = nullptr;
        }
    }
    
    for(int i = 0; i != 7; ++i) {
        if(broken[i] != nullptr) {
            delete broken[i];
            broken[i] = nullptr;
        }
    }

    delete board;
    delete line1;
    delete line2;
    delete line3;
    delete line4;
    delete line5;
    delete broken;  
}

TilePtr* Mosaic::getLine(int pos) {
    TilePtr* toReturn = new TilePtr(nullptr);
    if (pos == 1){
        toReturn = line1;
    } else if (pos == 2){
        toReturn = line2;
    } else if (pos == 3){
        toReturn = line3;
    } else if (pos == 4){
        toReturn = line4;
    }else if (pos == 5){
        toReturn = line5;
    }
    return toReturn;
}

TilePtr* Mosaic::getBroken() {
    return broken;
}

TilePtr** Mosaic::getBoard() {
    return board;
}
    
void Mosaic::placeTiles(int storageRow, char colour, int numTiles) {
    int counter = numTiles;
    TilePtr* line = getLine(storageRow);

    while (counter != 0) {
        for(int i = 0; i < storageRow; ++i) {
            if (line[i]->getColour() == NO_TILE) {
                line[i] = new Tile(colour);
                --counter;
            }
        }

        for(int i=0; i < 7; ++i) {
            if(broken[i]->getColour() == NO_TILE) {
                broken[i] = new Tile(colour);
            }
            --counter;
        }
    }
}

void Mosaic::moveTile() {
    //TODO  moves tiles from storage row to completed tiles

    for(int i=0; i != MAX_MOSAIC_ROWS; ++i) {
            if(isStorageComplete(i+1)) {
                char colour = getTileToMove(i+1);
                int index = indexToMove(colour, i+1);
                board[i][index]->setColour(colour);
                clearStorageRow(i+1);
                //check for adjacent tiles     
            }

    }
}

void Mosaic::clearStorageRow(int row) {
    TilePtr* storageLine = getLine(row);

    for(int i = 0; i != row; ++i) {
        if(storageLine[i]->getColour() != NO_TILE) {
            storageLine[i]->setColour(NO_TILE);
        }
    }
    delete storageLine;
}

bool Mosaic::isStorageComplete(int line) {
    bool complete = false;
    TilePtr* storageLine = getLine(line);
    for(int i=0; i != line; ++i) {
        if(i == line-1) {
            if(storageLine[i]->getColour() != NO_TILE) {
                complete = true;
            }
        }
    }
    delete storageLine;

    return complete;
}

int Mosaic::indexToMove(char colour, int row) {
    int index = 0;
    for(int i=0; i != row; ++i) {
        if(i == row - 1) {
            if(colour == DARK_BLUE) {
                index = i;
            } else if (colour == YELLOW) {
                index = i+1;
            } else if (colour == RED) {
                index = i + 2;
            } else if (colour == BLACK) {
                index = i + 3;
            } else if (colour == LIGHT_BLUE) {
                index = i + 4;
            }            
        }
    }

    if(index > 4) {
        index = index - 5;
    }   
    return index;    
}

char Mosaic::getTileToMove(int line) {
    return getLine(line)[0]->getColour();
}

bool Mosaic::checkForCompleteLine() {
    bool complete = false;
    for(int i= 0; i != MAX_MOSAIC_ROWS; ++i) {
        for(int j = 0; j != MAX_MOSAIC_COLS; ++j) {
            if((j == MAX_MOSAIC_COLS - 1) && (board[i][j]->getColour() != NO_TILE)) {
                complete = true;
            }
        }
    }

    return complete;
}
//TODO print mosaic