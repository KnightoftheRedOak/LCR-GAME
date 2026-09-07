#pragma once
#include<string>
using namespace std;

// Player class
// Stores player data and handles chip logic
class Player
{
private:
	// Tracks total number of chips the player has
	int totalChips = 3;

	// Stores player id (0 = user, >0 = bots)
	int id = 0;

	// Stores player name
	string name;

	// Tracks if this is the user or a bot
	bool isPlayer;

public:
	// Bot constructor
	// Sets id for bot player
	Player(int id);

	// Player constructor
	// Sets name and isPlayer for user
	Player(string name, bool isPlayer);

	// Default constructor
	// Sets default values for player
	Player();

	// Returns if player is user or bot
	bool getPlayer();

	// Returns player id
	int getId();

	// Returns player name
	string getName();

	// Adds to player's chip count
	void chipsIn(int numChips);

	// Decreases player's chip count
	void chipsOut();

	// Returns total number of chips
	int getNumChips();

	// Displays player's id and chip count
	void printStatus();

};