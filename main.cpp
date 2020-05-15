#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include "GameEngine.h"


using std::string;
using std::cout;
using std::cin;
using std::endl;

class Args {
public:

   std::string deckFile;

   bool haveSeed;
   int seed;
};

void processArgs(int argc, char** argv, Args* args);
void displayMenu();
void showCredits();
void newGame(Args* args);
void loadGame();

int main(int argc, char** argv) {
    Args args;
    processArgs(argc, argv, &args);

    cout << "Welcome to Azul!\n-------------------" << endl;

    int choice = 0;

    
    do {
        displayMenu();
        cin >> choice;

        if((choice < 1 || choice > 4 || !cin.good()) && !cin.eof()) {
            cout << "\nInvalid Input. Try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if(choice == 1) {
                newGame(&args);
            } else if(choice == 2) {
                loadGame();
            } else if(choice == 3) {
                showCredits();
            } else if(choice == 4 || cin.eof()) {
                cout << "Goodbye! \n";
                return EXIT_SUCCESS;
            }
        }
    } while (choice != 4 && !cin.eof() && choice != 1 && choice != 2);
}

void displayMenu() {
    cout << "\nMenu\n----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show student information)" << endl;
    cout << "4. Quit" << endl;
    cout << "> ";
}

void showCredits() {
    string names[] = {"Adrian Vong", "Mark Baptista", "Amna Alfarah Alonto"};
    string studentId[] = {"s3721092", "s3722699", "s3778713"};
    string email = "@student.rmit.edu.au";

    cout << "----------------------------------" << endl;

    for(int i=0; i < 3; ++i) {
        cout << "Name: " << names[i] << endl;
        cout << "Student ID: " << studentId[i] << endl;
        cout << "Email: " << studentId[i] << email << endl;

        if(i != 2) {
            cout << endl;
        }
    }

    cout << "----------------------------------" << endl;
}

void newGame(Args* args){
    GameEngine* ge = new GameEngine();
    ge->newPlayers();
    ge->getCentreBoard()->shuffleTileBag(args->seed);
    ge->getCentreBoard()->populateFactories();

    do {
        cout << "== Start Round ==" << endl;
        ge->playGame(); 
        //ge->calculateRound();
        cout << "== End of Round ==" << endl;
        ge->checkFinished();
    } while(!ge->isFinished());
    
    if(ge->isFinished()) {
        //compare player points to see who won
    }
    //print players' mosaic, points earned for each round, total points for each player

    delete ge;     
}

void loadGame(){
    //TODO
}

void processArgs(int argc, char** argv, Args* args) {

   if (argc >= 3) {
       std::string argv1 = argv[1];
       if(argv1 == "-s") {
            std::string strSeed(argv[2]);
            std::stringstream sstream(strSeed);
            sstream >> args->seed;
            args->haveSeed = true;
       }
   } else {
      args->haveSeed = false;
      args->seed = 0;
   }


   }