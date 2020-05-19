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
    line1[0] = new Tile(NO_TILE);   

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
    discardedTiles.clear();
}

Mosaic::~Mosaic() {
    clearLines();
    delete board;
    delete line1;
    delete line2;
    delete line3;
    delete line4;
    delete line5;
    delete broken;  
    discardedTiles.clear();
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
    
int Mosaic::placeTiles(int storageRow, char colour, int numTiles) {
    int remaining = numTiles;
    TilePtr* line = getLine(storageRow);
    

    for(int i = 0; i != storageRow; ++i) {
        if (line[i]->getColour() == NO_TILE && remaining != 0) {
            line[i]->setColour(colour);
            --remaining;
        }
    }    

    for(int i=0; i != 7; ++i) {
        if(broken[i] == nullptr && remaining != 0) {
            broken[i] = new Tile(colour);
            --remaining;
        }
    }

    return remaining;
}

int Mosaic::moveTile(int row) {
    int index = -1;
    if(isStorageComplete(row+1)) {
        char colour = getTileToMove(row+1);
        index = indexToMove(colour, row+1);
        board[row][index]->setColour(colour);
        clearStorageRow(row+1);   
    }
    return index;
}

int Mosaic::countHorizontal(int row, int col) {
    int counter = 0;

    int i=col;
    while (i < MAX_MOSAIC_COLS && board[row][i]->getColour() != NO_TILE) {
        counter++;
        i++;
    } 

    if(col != 0) {
        int j = col - 1;
        while(j >= 0 && board[row][j]->getColour() != NO_TILE) {
            counter++;
            j--;
        } 
    }

    return counter;

}

int Mosaic::countVertical(int row, int col) {
    int counter = 0;

    int i=row;
    while (i < MAX_MOSAIC_ROWS && board[i][col]->getColour() != NO_TILE) {
        counter++;
        i++;
    } 

    if(row != 0) {
        int j = row - 1;
        while(j >= 0 && board[j][col]->getColour() != NO_TILE) {
            counter++;
            j--;
        } 
    }

    return counter;
}

void Mosaic::clearStorageRow(int row) {
    TilePtr* storageLine = getLine(row);

    for(int i = 0; i != row; ++i) {
        if(storageLine[i]->getColour() != NO_TILE) {
            discardedTiles.push_back(storageLine[i]->getColour());
            storageLine[i]->setColour(NO_TILE);
        }
    }
    discardedTiles.pop_back();
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

bool Mosaic::checkForCompleteLine(int row) {
    bool complete = false;
    int count = 0;
    for(int j = 0; j != MAX_MOSAIC_COLS; ++j) {
        if(board[row][j]->getColour() != NO_TILE) {
            count++;
        }
    }
    if(count == 5) {
        complete = true;
    }

    return complete;
}

void Mosaic::placeFirstPlayerTile() {
    for(int i=0; i != 7; ++i) {
        if(broken[i] == nullptr) {
            broken[i] = new Tile(FIRST_PLAYER);
            break;
        }
    }    
}

int Mosaic::getBrokenPoints(){
    int count = 0;
    int points = 0;
    for(int i=0; i != 7; ++i) {
        if(broken[i] != nullptr) {
            count++;
        }
    }

    if(count == 1 || count == 2) {
        points = count;
    } else if(count == 3 || count == 4 || count == 5) {
        points =  2 * (count-1);
    } else if( count == 6) {
        points = 11;
    } else if(count == 7) {
        points = 14;
    }

    return points;

}

void Mosaic::clearBrokenTiles() {
    for(int i=0; i != 7; ++i) {
        if(broken[i] != nullptr) {
            if(broken[i]->getColour() != FIRST_PLAYER) {
                discardedTiles.push_back(broken[i]->getColour());
            } 
            delete broken[i];
            broken[i] = nullptr;
        }
    }
}

bool Mosaic::checkForCompleteColumn(int col) {
    bool complete = false;
    int count = 0;
    for(int i = 0; i != MAX_MOSAIC_ROWS; ++i) {
        if(board[i][col]->getColour() != NO_TILE) {
            count++;
        }
    }
    if(count == 5) {
        complete = true;
    }

    return complete;    
}

int Mosaic::countCompleteColours() {
    int complete = 0;
    char colours[] = {RED, YELLOW, DARK_BLUE, LIGHT_BLUE, BLACK};
    
    for(int i=0; i != NUMBER_OF_COLOURS; ++i) {
        int count = 0;
        for(int j = 0; j != MAX_MOSAIC_ROWS; ++j) {
            for(int k = 0; k != MAX_MOSAIC_COLS; ++k) {
                if(board[j][k]->getColour() == colours[i]) {
                    count++;
                }
            }

            if(count == 5) {
                complete++;
            }
        }
    }
    return complete;
}

void Mosaic::clearLines() {
    for(int i = 0; i != MAX_MOSAIC_ROWS; ++i) {
        for(int j = 0; j != MAX_MOSAIC_COLS; ++j) {
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }
    
    delete line1[0];
    line1[0] = nullptr;

    for(int i = 0; i != 2; ++i) {
        delete line2[i];
        line2[i] = nullptr;
    }

    for(int i = 0; i != 3; ++i) {
        delete line3[i];
        line3[i] = nullptr;
    }
    
    for(int i = 0; i != 4; ++i) {
        delete line4[i];
        line4[i] = nullptr;
    }
    
    for(int i = 0; i != 5; ++i) {
        delete line5[i];
        line5[i] = nullptr;
    }
}

std::vector<char> Mosaic::getDiscardedTiles() {
    return discardedTiles;
}