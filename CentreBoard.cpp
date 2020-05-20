#include "CentreBoard.h"

#include <random>
#include <algorithm>


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
    if(row !=0) {
        for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
            if(factories[row-1][j]->getColour() == colour) {
                counter++;
            }
        }  
    } else {
        for(int i=0; i != centralFactory.size(); ++i) {
            if (centralFactory[i]->getColour() == colour) {
                counter++;
            }
        }
    } 
    return counter;
}

void CentreBoard::moveTilesToCentralFactory(char colour, int row) {
    for(int j=0; j != MAX_TILES_PER_FACTORY; ++j) {
        if(factories[row-1][j]->getColour() != colour) {
            centralFactory.push_back(factories[row-1][j]);
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

std::vector<TilePtr> CentreBoard::getBoxLid(){
    return boxLid;
}

void CentreBoard::printCentralFactory() {
    std::cout << "O:";

    int countF = 0;
    int countR = 0;
    int countY = 0;
    int countB = 0;
    int countL = 0;
    int countU = 0;

    for (int i = 0; i != centralFactory.size(); ++i) {
        if (centralFactory.at(i)->getColour() == FIRST_PLAYER) {
            countF++;
        } else if(centralFactory.at(i)->getColour() == RED) {
            countR++;
        } else if(centralFactory.at(i)->getColour() == YELLOW) {
            countY++;
        } else if(centralFactory.at(i)->getColour() == DARK_BLUE) {
            countB++;
        } else if(centralFactory.at(i)->getColour() == LIGHT_BLUE) {
            countL++;
        } else if(centralFactory.at(i)->getColour() == BLACK) {
            countU++;
        }
    }

    for(int i = 0; i != countF; ++i) {
        std::cout << " " << FIRST_PLAYER; 
    }

    for(int i = 0; i != countR; ++i) {
        std::cout << " " << RED; 
    }

    for(int i = 0; i != countY; ++i) {
        std::cout << " " << YELLOW; 
    }

    for(int i = 0; i != countB; ++i) {
        std::cout << " " << DARK_BLUE; 
    }

    for(int i = 0; i != countL; ++i) {
        std::cout << " " << LIGHT_BLUE; 
    }

    for(int i = 0; i != countU; ++i) {
        std::cout << " " << BLACK; 
    }

    std::cout << std::endl;
}

void CentreBoard::printFactories() {
    for(int i=0; i != MAX_FACTORY; ++i) {
        std::cout << i+1 << ":";
        printFactoriesByOrder(i);
    }
}
    
bool CentreBoard::checkEmpty() {
    bool empty = false;

    if(centralFactory.empty()) {
        for(int i = 0; i != MAX_FACTORY; ++i) {
            for(int j = 0; j != MAX_TILES_PER_FACTORY; ++j) {
                if (factories[i][j] == nullptr) {
                    empty = true;
                } else {
                    empty = false;
                    break;
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
                if( tileBag->size() == 0) {
                    factories[i][j] = boxLid.back();
                    boxLid.pop_back();
                } else {
                    factories[i][j] = tileBag->getHead();
                }  
                          
            }
        }
    }

    if(centralFactory.empty()) {
        centralFactory.push_back(new Tile(FIRST_PLAYER));
    }    
}

void CentreBoard::removeTilesFromCentralFactory(char colour) {

    for(auto& tilePtr : centralFactory)
    {
        if (tilePtr->getColour() == colour)
        {
            delete tilePtr;
            tilePtr = nullptr;
        }
    }
    centralFactory.erase(std::remove(centralFactory.begin(), centralFactory.end(), nullptr), centralFactory.end());
}

bool CentreBoard::isFactoryEmpty(int factory) {
    bool empty = false;
    if(factory == 0) {
        if(centralFactory.empty() || centralFactory.back()->getColour() == FIRST_PLAYER) {
            empty = true;
        } else {
            empty = false;
        }
    } else {
        if(factories[factory-1][0] == nullptr) {
            empty = true;
        } else {
            empty = false;
        }
    }

    return empty;
}

void CentreBoard::printFactoriesByOrder(int row) {
    int countR = 0;
    int countY = 0;
    int countB = 0;
    int countL = 0;
    int countU = 0;

    for (int i = 0; i != MAX_TILES_PER_FACTORY; ++i) {
        if(factories[row][i] != nullptr) {
            if (factories[row][i]->getColour() == RED) {
                countR++;
            } else if(factories[row][i]->getColour() == YELLOW) {
                countY++;
            }  else if(factories[row][i]->getColour() == DARK_BLUE) {
                countB++;
            } else if(factories[row][i]->getColour() == LIGHT_BLUE) {
                countL++;
            } else if(factories[row][i]->getColour() == BLACK) {
                countU++;
            }
        }
    }
    
    for(int i = 0; i != countR; ++i) {
        std::cout << " " << RED; 
    }

    for(int i = 0; i != countY; ++i) {
        std::cout << " " << YELLOW; 
    }

    for(int i = 0; i != countB; ++i) {
        std::cout << " " << DARK_BLUE; 
    }

    for(int i = 0; i != countL; ++i) {
        std::cout << " " << LIGHT_BLUE; 
    }

    for(int i = 0; i != countU; ++i) {
        std::cout << " " << BLACK; 
    }

    std::cout << std::endl;
}