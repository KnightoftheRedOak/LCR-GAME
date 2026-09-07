#pragma once
#include <vector>
#include "Player.h"

using namespace std;

// UI class
class UI
{
public:
    // Full UI display of game:
    // Clears screen,
    // Prints current player turn, 
    // Prints player list,
    // Prints center pot
    void displayScreen(vector<Player>& seatingChart, Player& currentPlayer, int centerPot);

    // Prints all players and their chip counts
    // Shows current player with >>
    void updatePlayersChips(vector<Player>& seatingChart, Player& currentPlayer);

    // Returns roll result 
    char printRollResult(char result);

    // roll animation
    // Shows spinning slots and final dice results
    void rollAnimation(Player& player, int totalRolls, vector<char> rolls);

private:
    // Stores values for dice animation
    vector<char> spinAnimation = { 'L', 'R', 'C', '*' };
};