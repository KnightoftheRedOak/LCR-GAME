#pragma once
#include "Player.h"
#include "UI.h"
#include <vector>

using namespace std;

// Controls all main gameplay 
class GameManager
{
public:
    // GameManager constructor
    // Sets core gameplay variables to zero at the start of the game
    GameManager();

    // Asks the user for the number of players
    // Only allows 3 or more players
    void getNumberOfPlayers();

    // Creates bot players and adds all players to the playerPool
    void createPlayers();

    // Randomly assigns players from the playerPool into the seatingChart
    void assignSeats();

    // Controls the main game loop and player turns
    void playGame();

    // Prints banner, gets user name, and displays game rules
    void introText();

private:
    // Stores all players before seating is assigned
    vector<Player> playerPool;

    // Stores players in their final seating order
    vector<Player> seatingChart;

    // Handles dice roll logic and returns the results
    vector<char> rollDice(Player& player);

    // Handles passing chips left, right, or into the center pot
    void anteUp(char letter, Player& currentPlayer);

    // Stores number of bot players
    int players;

    // Stores the user player
    Player user;

    // Stores the user's name
    string userName;

    // Tracks number of chips in the center pot
    int centerPot;

    // Tracks current player's position in seatingChart
    int index;

    // Handles UI display and animation
    UI ui;
};