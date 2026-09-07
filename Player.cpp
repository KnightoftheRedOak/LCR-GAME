#include "Player.h"
#include <iostream>
using namespace std;

// Bot constructor
// Sets name, id, totalChips, and isPlayer
Player::Player(int id)
{
    this->id = id;
    this->name = "BOT";
    isPlayer = false;
    totalChips = 3;
}

// Player constructor
// Sets name, id, totalChips, and isPlayer
Player::Player(string name, bool isPlayer)
{
    this->name = name;
    this->isPlayer = isPlayer;
    this->id = 0;
    totalChips = 3;
}

// Default constructor
// Sets name, id, totalChips, and isPlayer
Player::Player()
{
    id = 0;
    name = "NONE";
    isPlayer = false;
    totalChips = 3;
}

// Returns isPlayer
bool Player::getPlayer()
{
    return this->isPlayer;
}

// Returns id
int Player::getId()
{
    return this->id;
}

// Returns name
string Player::getName()
{
    return this->name;
}

// Adds to player's chip count
void Player::chipsIn(int numChips)
{
    totalChips += numChips;
}

// Decreases player's chip count
void Player::chipsOut()
{
    if (totalChips > 0)
    {
        totalChips -= 1;
    }
}

// Returns total number of chips
int Player::getNumChips()
{
    return totalChips;
}

// Displays player's id and chip count
void Player::printStatus()
{
    cout << "PLAYER " << id << " TOTAL CHIPS: " << totalChips << endl;
}