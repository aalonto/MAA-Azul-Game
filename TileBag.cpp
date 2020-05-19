#include <exception>
#include <iostream>
#include "TileBag.h"


Node::Node(TilePtr tile, Node* next) :
    tile(tile),
    next(next)
{}

Node::Node(Node& other) :
    Node(other.tile, other.next)
{}

TileBag::TileBag() {
    head = nullptr;
    length = 0;
}

TileBag::~TileBag() {
    clear();
}

unsigned int TileBag::size() {
    return length;   
}

void TileBag::addTile(TilePtr tile) {
    Node* toAdd = new Node(tile, nullptr);

    if(head == nullptr) {
        head = toAdd;
    } else {
        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }
        
        current->next = toAdd;    
    }
    length++;
}

void TileBag::removeTileFront() {
    if (head != nullptr){
        Node* todelete = head;
        head = head->next;
        delete todelete;
        length--;
    }else {
        throw std::logic_error("Deleting on empty list");
    }
}

TilePtr TileBag::getHead() {
    TilePtr toGet = nullptr;   
    if (head != nullptr){
        toGet = head->tile; 
        removeTileFront(); 
    }

    return toGet;

}



void TileBag::clear(){
   while (head != nullptr) {
      removeTileFront();
   }
}


void TileBag::loadTileBag(std::istream& inputStream) {
   clear();

   while (!inputStream.eof()) {
       char colour = NO_TILE;
       char readColour = NO_TILE;
      inputStream >> readColour;
      if (readColour == RED) {
         colour = RED;
      } else if (readColour == YELLOW) {
         colour = YELLOW;
      } else if (readColour == DARK_BLUE) {
         colour = DARK_BLUE;
      } else if (readColour == LIGHT_BLUE) {
         colour = LIGHT_BLUE;
      } else if (readColour == BLACK) {
         colour = BLACK;
      }


      // TODO: Add the card that is read to the deck
      TilePtr tile = new Tile(colour);
      addTile(tile);
   }    
}










