

#include <iostream>

#include "Player.h"
#include "GameManager.h"
#include "Player.h"
using namespace std;

// Create GameManager instance
// Call functions off GameManager to start game play
int main()
{
    GameManager manager;
    
    manager.introText();
    manager.getNumberOfPlayers();
    manager.createPlayers();
    manager.assignSeats();
    manager.playGame();

}


