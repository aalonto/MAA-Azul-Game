#include "GameEngine.h"
#include <iomanip>
#include <string>
#include <limits>
#include <sstream> 

GameEngine::GameEngine(){
    this->centreBoard = new CentreBoard();
    this->player1 = nullptr;
    this->player2 = nullptr;
    this->players= new Player*[MAX_PLAYER];
    for(int i=0; i != MAX_PLAYER; ++i) {
        players[i] = nullptr;
    }
    this->finished = false;
    this->endRound = false;
}

GameEngine::~GameEngine(){
    if(centreBoard != nullptr) {
        delete centreBoard;
    }

    for(int i=0; i != MAX_PLAYER; ++i) {
        if(players[i] != nullptr){
            delete players[i];
        }

    }

    if(player1 != nullptr) {
        delete player1;
    }    

    if(player2 != nullptr) {
        delete player2;
    }
}

void GameEngine::newPlayers() {
    std::string name1 = "";
    std::string name2 = "";

    std::cout << "\nStarting a New Game..." << std::endl;
    std::cout << "\nEnter name for player 1:" << std::endl;
    std::cout << "> ";
    std::cin >> name1;
    player1 = new Player(name1);
    players[0] = player1;

    std::cout << "\nEnter name for player 2:" << std::endl;
    std::cout << "> ";
    std::cin >> name2;
    player2 = new Player(name2);
    players[1] = player2;
    std::cout << "\nLet's Play! \n" << std::endl;
}

void GameEngine::playGame() {
    Player* current = player1;
    Player* other = player2;


    do {
        std::cout << "\nTURN FOR PLAYER: " << current->getPlayerName() << std::endl;
        std::cout << "Factories:" << std::endl;
        centreBoard->printCentralFactory();
        centreBoard->printFactories();
        std::cout << std::endl;

        displayPlayerMosaic(current);

    
        std::cout << "> ";

        std::string choice;
        std::getline(std::cin, choice);
        std::stringstream playerTurn(choice);

        std::string command;
        int factory;
        std::string colour;
        int row;

        playerTurn >> command >> factory >> colour >> row;

//check save
        if(command == "turn") {
            int numTiles = 0;
            char colourToChar = getColourFromInput(colour);

            if (colourToChar != NO_TILE) {

                numTiles = centreBoard->getNumTilesInFactory(colourToChar, factory);
                if(numTiles != 0) {
                    int remaining = current->getMosaic()->placeTiles(row, colourToChar, numTiles);
                    if(remaining != 0) {
                        for(int i=1; i <= remaining; ++i){
                            centreBoard->getBoxLid().push_back(new Tile(colourToChar));
                        }
                    }
                    
                    if(factory !=0){
                        centreBoard->moveTilesToCentralFactory(colourToChar, factory);
                    } else {
                        if(centreBoard->getCentralFactory().front()->getColour() == FIRST_PLAYER) {
                            centreBoard->removeTilesFromCentralFactory(FIRST_PLAYER);
                            current->getMosaic()->placeFirstPlayerTile();
                        }

                        centreBoard->removeTilesFromCentralFactory(colourToChar);
                    }                    
                }
            }

            Player* tmp = current;
            current = other;
            other = tmp;
            
            checkEndRound();

        } 
    } while(!endRound);
}

char GameEngine::getColourFromInput(std::string colour) {
    char toReturn;
    if(colour == "R") {
        toReturn = RED;
    } else if (colour == "Y"){
        toReturn = YELLOW;
    } else if (colour == "B"){
        toReturn = DARK_BLUE;
    } else if (colour == "L"){
        toReturn = LIGHT_BLUE;
    } else if (colour == "U"){
        toReturn = BLACK;
    } else {
        toReturn = NO_TILE;
    }

    return toReturn;
}

void GameEngine::displayPlayerMosaic(Player* current) {
    TilePtr* storageLine = nullptr;
    TilePtr* broken = current->getMosaic()->getBroken();
    TilePtr** board = current->getMosaic()->getBoard();
    std::cout << current->getPlayerName() << "'s Mosaic:" << std::endl;
    int space = 8;

    for(int i=0; i != MAX_MOSAIC_ROWS; ++i) {
        
        std::cout << i+1 << ":";
        storageLine = current->getMosaic()->getLine(i+1);
        for (int j = 0; j != space; ++j){ 
                std::cout << " "; 
            }
        space = space - 2; 
  
        for(int j = i; j >= 0; --j) {
            std::cout << " " << storageLine[j]->getColour();
        }
        std::cout << " ||";

        for(int k = 0; k != MAX_MOSAIC_COLS; ++k) {
            std::cout << " " << board[i][k]->getColour();
        }
        std::cout << std::endl;
    }

    std::cout << "broken: ";

    for(int i=0; i != 7; ++i) {
        if(broken[i] != nullptr) {
            std::cout << broken[i]->getColour() << " ";
        }
    }
    std::cout << std::endl;
}

void GameEngine::checkEndRound() {
    if(centreBoard->checkEmpty()) {
        endRound = true;
    }
}

void GameEngine::calculateRound() {
    for(int i=0; i != MAX_PLAYER; ++i) {
        int pointsEarned = 0;
        Mosaic* playerMosaic = players[i]->getMosaic();
        for(int j = 0; j != MAX_MOSAIC_ROWS; ++j) {
            int index = playerMosaic->moveTile(j);
            if(index != -1) {
                int horizontal = playerMosaic->countHorizontal(j, index);
                int vertical = playerMosaic->countVertical(j, index);
                pointsEarned = pointsEarned + horizontal + vertical;
                if (horizontal == 1 || vertical == 1) {
                    pointsEarned = pointsEarned - 1;
                }

            }
        }
        int pointstoSubtract = playerMosaic->getBrokenPoints();
        if(pointstoSubtract != 0) {
            playerMosaic->clearBrokenTiles();
        }
        int pointsForRound = pointsEarned - pointstoSubtract;
        players[i]->setPointsforRound(pointsForRound);
        players[i]->updatePoints(pointsForRound);
    }
}

void GameEngine::checkFinished() {
    for(int i=0; i != MAX_PLAYER; ++i) {
        for (int j = 0; j != MAX_MOSAIC_ROWS; ++j) {
            if(players[i]->getMosaic()->checkForCompleteLine(j)) {
                finished = true;
            }
        }
    }
}

bool GameEngine::isFinished() {
    return finished;
}

CentreBoard* GameEngine::getCentreBoard() {
    return centreBoard;
}

void GameEngine::printRoundResults() {
    std::cout << "=== ROUND RESULT ===" << std::endl;
    std::cout << std::endl;

    for(int i=0; i != MAX_PLAYER; ++i) {
        std::cout << players[i]->getPlayerName() << " earned " << players[i]->getPointsForRound() << 
        " points for this round." << std::endl;
        std::cout << players[i]->getPlayerName() << "'s total points so far: " 
        << players[i]->getPoints() << "points" << std::endl;
        displayPlayerMosaic(players[i]);
        std::cout << std::endl;

    }
}

void GameEngine::setEndRoundToFalse() {
    endRound = false;
}

void GameEngine::endOfGameScoring() {
    for(int i=0; i != MAX_PLAYER; ++i) {
        Mosaic* playerMosaic = players[i]->getMosaic();
        int pointsEarned = 0;

            for (int j = 0; j != MAX_MOSAIC_ROWS; ++j) {
                if(playerMosaic->checkForCompleteLine(j)) {
                    pointsEarned += 2;
                }
            }

            for (int j = 0; j != MAX_MOSAIC_COLS; ++j) {
                if(playerMosaic->checkForCompleteColumn(j)) {
                    pointsEarned += 7;
                }
            }

            int completeColours = playerMosaic->countCompleteColours();
            pointsEarned += completeColours * 10;
            players[i]->updatePoints(pointsEarned);
    }
}

void GameEngine::displayWinner() {
    Player* winner = players[0];
    for(int i = 1; i != MAX_PLAYER; ++i) {
        if(players[i]->getPoints() >= winner->getPoints()) {
            winner = players[i];
        }

    } 

    std::cout << "Player " << winner->getPlayerName() << " wins!" << std::endl;
}

void GameEngine::moveDiscardedTilesToBoxLid() {

    for(int i=0; i != MAX_PLAYER; ++i) {
        std::vector<char> discarded = players[i]->getMosaic()->getDiscardedTiles();
        std::vector<TilePtr> boxLid = centreBoard->getBoxLid();
        
        while(!discarded.empty()) {
            boxLid.push_back(new Tile(discarded.back()));
            discarded.pop_back();
        }
    }
}

