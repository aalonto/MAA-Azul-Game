#include "GameEngine.h"
#include <string>
#include <limits>
#include <sstream> 

GameEngine::GameEngine(){
    this->centreBoard = new CentreBoard();
    this->player1 = nullptr;
    this->player2 = nullptr;
    this->players= new Player*[MAX_PLAYER];
    players[0] = player1;
    players[1] = player2;  
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

    std::cout << "Starting a New Game" << std::endl;
    std::cout << "Enter name for player 1:" << std::endl;
    std::cout << "> ";
    std::cin >> name1;
    player1 = new Player(name1);

    std::cout << "Enter name for player 2:" << std::endl;
    std::cout << "> ";
    std::cin >> name2;
    player2 = new Player(name2);
    std::cout << "Let's Play!" << std::endl;
}

void GameEngine::playGame() {
    Player* current = player1;
    Player* other = player2;


    do {
        std::cout << "TURN FOR PLAYER: " << current->getPlayerName() << std::endl;
        std::cout << "Factories:" << std::endl;
        centreBoard->printCentralFactory();
        centreBoard->printFactories();

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
                    centreBoard->moveTilesToCentralFactory(colourToChar, factory);
                    current->getMosaic()->placeTiles(row, colourToChar, numTiles);
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
    std::cout << "Mosaic for " << current->getPlayerName() << ":" << std::endl;
    for(int i=0; i != MAX_MOSAIC_ROWS; ++i) {
        std::cout << i+1 << ":";
        storageLine = current->getMosaic()->getLine(i+1);
    //format mosaic display for spaces
        for(int j = 0; j != i+1; ++j) {

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
        Mosaic* playerMosaic = players[i]->getMosaic();
        playerMosaic->moveTile();
        //check for adjacent tiles
        //update player points
    }
}
void GameEngine::checkFinished() {
    for(int i=0; i != MAX_PLAYER; ++i) {
        if(players[i]->getMosaic()->checkForCompleteLine()) {
            finished = true;
        }
    }
}

bool GameEngine::isFinished() {
    return finished;
}
    // void finalResults();
    // void calculateRound(Player p);

    // Player* getPlayer(int i);

CentreBoard* GameEngine::getCentreBoard() {
    return centreBoard;
}

