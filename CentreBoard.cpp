#include "CentreBoard.h"

#include <random>


CentreBoard::CentreBoard() {  
    if(!centralFactory.empty()) {
        centralFactory.clear();
    }
    centralFactory.push_back(new Tile(FIRST_PLAYER));
    
    factories = new TilePtr*[MAX_FACTORY];
    for(int i = 0; i != MAX_FACTORY; ++i) {
        factories[i]= new TilePtr[MAX_TILES_PER_FACTORY];

        for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
            factories[i][j] = nullptr;
        }
    }
    
    this->tileBag = new TileBag();
    dbToFill = 20;
    yToFill = 20;
    rToFill = 20;
    bToFill = 20;
    lbToFill = 20;
}
    
CentreBoard::~CentreBoard() {
    if(!centralFactory.empty()) {
        centralFactory.clear();
    }

    for(int i=0; i != MAX_FACTORY; ++i) {
        for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
            if(factories[i][j]!= nullptr) {
                delete factories[i][j];
            }
        }
    }
    delete factories;

    if(tileBag != nullptr) {
        delete tileBag;
    }
    boxLid.clear();     
}

int CentreBoard::getNumTilesInFactory(char colour, int row) {
    int counter = 0;
    for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
        if(factories[row-1][j]->getColour() == colour) {
            counter++;
        }
    }    
    return counter;
}

void CentreBoard::moveTilesToBoxLid(char colour, int row) {
    for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
        if(factories[row-1][j]->getColour() != colour) {
            boxLid.push_back(factories[row-1][j]);
        }
        factories[row-1][j] = nullptr;
    }          
}

TilePtr** CentreBoard::getFactories() {
    return factories;
}

std::vector<TilePtr> CentreBoard::getCentralFactory() {
    return centralFactory;
}

void CentreBoard::printCentralFactory() {
    std::cout << "O: ";
    for(TilePtr tile : centralFactory) {
        std::cout << tile->getColour() << " ";
    }    
    std::cout << std::endl;
}

void CentreBoard::printFactories() {
    for(int i=0; i != MAX_FACTORY; ++i) {
        std::cout << i+1 << ": ";
        for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
            if(factories[i][j] != nullptr){
                std::cout << factories[i][j]->getColour() << " ";
            }
        }
        std::cout << std::endl;
    }
}
    
bool CentreBoard::checkEmpty() {
    bool empty = false;

    if(centralFactory.empty()) {
        for(int i = 0; i != MAX_FACTORY; i++) {
            for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
                if (factories[i][j]->getColour() == NO_TILE) {
                    empty = true; 
                }
            } 
        }

    }

    return empty;
}

void CentreBoard::shuffleTileBag(int seed) {
    bool filled = false;
    int min = 1;
    int max = 5;
    while(!filled) {
        if(seed == 0) {
            std::random_device engine;
            std::uniform_int_distribution<int> uniform_dist(min, max);

            int value = -1;
            for (int i = 0; i != 100; ++i) {
                value = uniform_dist(engine);
                filled = fillTileBag(value);
            }
        } else {
            std::default_random_engine engine(seed);
            std::uniform_int_distribution<int> uniform_dist(min, max);

            int value = -1;
            for (int i = 0; i != 100; ++i) {
                value = uniform_dist(engine);
                filled = fillTileBag(value);
            }
        }
    }
}

bool CentreBoard::fillTileBag(int value) {
    bool completed = false;
    if(value == 1 && dbToFill != 0) {
        tileBag->addTile(new Tile(DARK_BLUE));
        dbToFill--;
    } else if(value == 2 && yToFill != 0) {
        tileBag->addTile(new Tile(YELLOW));
        yToFill--;        
    } else if(value == 3 && rToFill != 0) {
        tileBag->addTile(new Tile(RED));
        rToFill--;        
    } else if(value == 4 && bToFill != 0) {
        tileBag->addTile(new Tile(BLACK));
        bToFill--;        
    } else if(value == 5 && lbToFill != 0) {
        tileBag->addTile(new Tile(LIGHT_BLUE));
        lbToFill--;        
    }
    if(dbToFill == 0 && yToFill == 0 && rToFill == 0 && bToFill == 0 && lbToFill == 0) {
        completed = true;
    }

    return completed;

}

void CentreBoard::populateFactories() {
    for(int i=0; i != MAX_FACTORY; ++i) {
        for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
            if(factories[i][j] == nullptr) {
                if(tileBag->size() != 0){
                    factories[i][j] = tileBag->getHead();
                } else{
                    if(!boxLid.empty()) {
                        factories[i][j] = boxLid.back();
                        boxLid.pop_back();
                    }
                    
                }
            }
        }
    }    
}