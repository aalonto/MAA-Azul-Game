#include "Player.h"

Player::Player(std::string playerName) {
    this->playerName = playerName;
    points = 0;
    mosaic = new Mosaic();
}

Player::Player(Player& other) : Player(other.playerName) {
    this->points = other.points;
    mosaic = other.mosaic;
}

Player::~Player() {
    delete mosaic;
}

std::string Player::getPlayerName() {
    return playerName;
}

Mosaic* Player::getMosaic() {
    return mosaic;
}

int Player::getPoints() {
    return points;
}

void Player::setPoints(int points) {
    this->points = points;
}

void Player::updatePoints(int points) {
    this->points += points;
}

void Player::setPointsforRound(int points) {
    this->pointsForRound = points;
}

int Player:: getPointsForRound() {
    return this->pointsForRound;
}