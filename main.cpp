#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include "GameEngine.h"

#define READ_FACTORY_NUM 7
#define READ_PLAYER_NUM 13

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
void readfactory(std::ifstream& readfile,GameEngine* ge);
char* getchar(string line);
void addcentrefactory(char * array, int index, GameEngine* ge);
void readplayer(Player* player,std::ifstream& readfile);
string getstring(char* array);
void addstoragerow(char* array, int index,Player* p);
void addbroken(char* array,Player* p);
void addMosic(char* array, Player* p,int index);
void resumegame(GameEngine* ge);

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

    do {
        ge->getCentreBoard()->populateFactories();

        cout << "== START ROUND ==" << endl;
        ge->playGame(); 
        cout << "\n == END ROUND == \n" << endl;
        cout << endl;
        ge->calculateRound();
        ge->printRoundResults();
        ge->checkFinished();
        if(!ge->isFinished()) {
            cout << "Preparing for next round... \n" << endl;
            ge->setEndRoundToFalse();
        }
    } while(!ge->isFinished());
    
    if(ge->isFinished()) {
        cout << "=== GAME OVER ===" << endl;
        ge->endOfGameScoring();
        ge->displayWinner();
    }

    delete ge;     
}

void loadGame(){
    // string filename;
    // cout << "Enter the filename from which loads a game" << endl;
    // cin >> filename;
    // std::ifstream  readfile;
    // GameEngine* ge = new GameEngine();
    // readfile.open(filename);

    // if(readfile.good()){
    //     while (readfile.eof() == false){
    //         readfactory(readfile,ge);
    //         readplayer(ge->getPlayer(1),readfile);
    //         readplayer(ge->getPlayer(2),readfile);
    //         // TODO impletment bool seturn value and setmethod
    //         string line;
    //         std::getline(readfile, line);
    //         int stringint = std::stoi(line);
    //         ge->setturn(stringint);
    //     }
    // }else 
    //     cout << "ERROR: file doesn't exist" << endl;
    // readfile.close();
    // resumegame(ge);
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

// void readfactory(std::ifstream& readfile, GameEngine* ge){
//     for(int i = 0; i < READ_FACTORY_NUM; i++){
//         string line;
//         std::getline(readfile, line);
//         if(line.at(0) == '#')
//             --i;
//         else{
//             char * chararray = getchar(line);
//             for(unsigned int x = 0; x < sizeof(chararray); x++){
//                 if(i == 0)
//                     // TODO need implemtentation
//                     ge->getTileBag().addTile(new Tile(chararray[x]));
//                 else if(i == 1)
//                     // TODO: need impletment of boxlid, getbox , push_back(new Tile(chararray[x]));
//                     // discardbag.pushback(new Tile(chararry[x]));
//                     cout << "discard" << endl;
//                 else if(i == 2)
//                 addcentrefactory(chararray, 0, ge);
//                 else if(i == 3)
//                 addcentrefactory(chararray, 1, ge);
//                 else if(i == 4)
//                 addcentrefactory(chararray, 2, ge);
//                 else if(i == 5)
//                 addcentrefactory(chararray, 3, ge);
//                 else if(i == 6)
//                 addcentrefactory(chararray, 4, ge);
//             }
//         }
//     }
// }

// char* getchar(string line){
//     bool allowed = false;
//     char* array = new char[100];
//     int arraysize = 0;

//     for(unsigned int i = 0; i < line.length();i++){
//         if(line.at(0) == '#')
//             --i;
//         else if(line.at(i) == '=')
//             allowed = true;
//         else if(allowed && line.at(i) != '='){
//             cout << line.at(i);
//             array[arraysize] = line.at(i);
//             arraysize++;
//         }
//     }
//     return array;
// }

// void addcentrefactory(char * array, int index, GameEngine* ge){
//     if(index == 0){
//         for(unsigned int i = 0; i < sizeof(array); i++)
//             ge->getCentreBoard()->getCentralFactory().push_back(new Tile(array[i]));
//     }else {
//         for (unsigned int i = 0; i < sizeof(array); i++)
//             ge->getCentreBoard()->getFactories()[index - 1][i] = new Tile(array[i]);
//     }
// }

// void readplayer(Player* player,std::ifstream& readfile){
//     for(int i = 0; i < READ_PLAYER_NUM; i++) {
//         string line;
//         std::getline(readfile, line);
//         if(line.at(0) == '#')
//             --i;
//         else{
//             char * chararray = getchar(line);
//             string charstring = getstring(chararray);

//             for(unsigned int x = 0; x < sizeof(chararray); x++){
//             if(i == 0)
//                 // TODO need a setname method
//                 player->setname(charstring);
//             else if(i == 1){
//                 int stringint = std::stoi(charstring);
//                 player->setPoints(stringint);
//             }else if(i == 2)
//                 addstoragerow(chararray, 1, player);
//             else if(i == 3)
//                 addstoragerow(chararray, 2, player);
//             else if(i == 4)
//                 addstoragerow(chararray, 3, player);
//             else if(i == 5)
//                 addstoragerow(chararray, 4, player);
//             else if(i == 6)
//                 addstoragerow(chararray, 2, player);
//             else if (i == 7)
//                 addbroken(chararray, player);
//             else if (i == 8)
//                 addMosic(chararray, player, 0);
//             else if (i == 9)
//                 addMosic(chararray, player, 1);
//             else if (i == 10)
//                 addMosic(chararray, player, 2);
//             else if (i == 11)
//                 addMosic(chararray, player, 3);
//             else if (i == 12)
//                 addMosic(chararray, player, 4);
//             } 
//         }
//     }
// }

// string getstring(char* array){
//     string toreturn;
//     for (unsigned int i = 0; i < sizeof(array); i++)
//         toreturn = toreturn + array[i];
//     return toreturn;
// }

// void addstoragerow(char* array, int index,Player* p){
//     for (int i = 0; i < sizeof(array); i++)
//         p->getMosaic()->getLine(index)[i] = new Tile(array[i]);
// }

// void addbroken(char* array,Player* p){
//     for (int i = 0; i < sizeof(array); i++){
//         p->getMosaic()->getBroken()[i] = new Tile(array[i]);
//     }
// }

// void addMosic(char* array, Player* p,int index){
//     for (int i = 0; i < sizeof(array); i++)
//         p->getMosaic()->getBoard()[index][i] = new Tile(array[i]);
// }

// void resumegame(GameEngine* ge){
//     do {
//         cout << "== Start Round ==" << endl;
//         ge->playGame(); 
//         //ge->calculateRound();
//         cout << "== End of Round ==" << endl;
//         ge->checkFinished();
//     } while(!ge->isFinished());
    
//     if(ge->isFinished()) {
//         //compare player points to see who won
//     }
//     //print players' mosaic, points earned for each round, total points for each player

//     delete ge;
// }
