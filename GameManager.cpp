#include "GameManager.h"
#include "Player.h"
#include "UI.h"
#include <windows.h>
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

const string LEFT = "                                                                        ";

// Controls the typewriter effect in the game
void typeText(string text, int delay = 15)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << endl;
}

// GameManager constructor
// Sets core gameplay variables to zero at the start of the game
GameManager::GameManager()
{
    players = 0;
    centerPot = 0;
    index = 0;
    srand(time(0));
}

// Asks the user for the number of players
// Only allows 3 or more players
void GameManager::getNumberOfPlayers()
{
    cout << "\nHow many BOT's will be playing today?\n";

    while (true)
    {
        int number = 0;
        cin >> number;

        if (cin.fail() || number < 3)
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nSorry human!!\n";
            cout << "Three or more players today!!\n";
            cout << "Please enter again.\n\n";
        }
        else
        {
            players = number;
            break;
        }
    }
}

// Creates new players for the game
// Loops through the number of players the user has given
// Creates a Player object for each one
// Adds each one to the playerPool
// Adds the user to the playerPool
void GameManager::createPlayers()
{
    for (int i = 1; i <= players; i++)
    {
        Player newPlayer(i);
        playerPool.push_back(newPlayer);
    }

    playerPool.push_back(user);
}

// Randomly selects one player from the playerPool
// Adds that player to the seatingChart
// Removes that player from the playerPool
// Repeats until the playerPool is empty
void GameManager::assignSeats()
{
    int index = 1;

    while (playerPool.size() > 0)
    {
        int chosenPlayer = rand() % playerPool.size();

        seatingChart.push_back(playerPool[chosenPlayer]);
        playerPool.erase(playerPool.begin() + chosenPlayer);

        index++;
    }
}

// Sets the player's number of rolls based on the amount
// of chips that they currently have
// Randomly selects a number between 1–6 for each roll
// 1 = L; 2 = R; 3 = C; 4, 5, 6 = *
// Will return those values
// Passes the values and the current player to the anteUp function
// Calls roll animation
vector<char> GameManager::rollDice(Player& player)
{
    int totalNumOfTurns = 0;
    int counter = 0;

    if (player.getNumChips() == 0)
    {
        cout << LEFT << "ROLL SKIPPED (no chips)\n\n";
        Sleep(2000);
        return {};
    }

    if (player.getNumChips() == 1)
    {
        totalNumOfTurns = 1;
    }
    else if (player.getNumChips() == 2)
    {
        totalNumOfTurns = 2;
    }
    else
    {
        totalNumOfTurns = 3;
    }

    vector<char> rolls;

    while (counter < totalNumOfTurns && player.getNumChips() > 0)
    {
        int diceRoll = (rand() % 6) + 1;

        if (diceRoll == 1)
        {
            anteUp('L', player);
            rolls.push_back('L');
        }
        else if (diceRoll == 2)
        {
            anteUp('R', player);
            rolls.push_back('R');
        }
        else if (diceRoll == 3)
        {
            anteUp('C', player);
            rolls.push_back('C');
        }
        else
        {
            rolls.push_back('*');
        }

        counter++;
    }

    ui.rollAnimation(player, totalNumOfTurns, rolls);

    cout << "\n";

    return rolls;
}

// Uses pointers to keep track of the players on the left and right
// Compares the current player's memory address to the memory address of
// the players in the seatingChart
// If they match, use the i position from the for loop
// to figure out the location of the current player
// Logic for when the player is at the start or end of the vector
// Finally passes chip to correct player or into pot
void GameManager::anteUp(char letter, Player& currentPlayer)
{
    Player* playerOnRight;
    Player* playerOnLeft;

    int currentPlayersIndexInGame = -1;

    for (int i = 0; i < seatingChart.size(); i++)
    {
        if (&currentPlayer == &seatingChart[i])
        {
            currentPlayersIndexInGame = i;
            break;
        }
    }

    if (currentPlayersIndexInGame == -1)
    {
        return;
    }

    if (currentPlayersIndexInGame == 0)
    {
        playerOnLeft = &seatingChart[seatingChart.size() - 1];
        playerOnRight = &seatingChart[currentPlayersIndexInGame + 1];
    }
    else if (currentPlayersIndexInGame == seatingChart.size() - 1)
    {
        playerOnLeft = &seatingChart[currentPlayersIndexInGame - 1];
        playerOnRight = &seatingChart[0];
    }
    else
    {
        playerOnLeft = &seatingChart[currentPlayersIndexInGame - 1];
        playerOnRight = &seatingChart[currentPlayersIndexInGame + 1];
    }

    if (letter == 'L')
    {
        playerOnLeft->chipsIn(1);
        currentPlayer.chipsOut();
    }
    else if (letter == 'R')
    {
        playerOnRight->chipsIn(1);
        currentPlayer.chipsOut();
    }
    else if (letter == 'C')
    {
        centerPot++;
        currentPlayer.chipsOut();
    }
}

// Loops through all players to check if more than one player
// still has chips
// if only one winner is declared
// if not, continue the game
// calls ui to update current stats for game
void GameManager::playGame()
{
    // Always start with player no matter where they are seated
    for (int i = 0; i < seatingChart.size(); i++)
    {
        if (seatingChart[i].getId() == 0)
        {
            index = i;
            break;
        }
    }

    while (true)
    {
       
        Player& currentPlayer = seatingChart[index];

        // Skips player turn if they have no chips
        if (currentPlayer.getNumChips() == 0)
        {
            ui.displayScreen(seatingChart, currentPlayer, centerPot);

            cout << LEFT;
            typeText("TURN SKIPPED (no chips)");
            Sleep(800);

            index++;

            if (index >= seatingChart.size())
            {
                index = 0;
            }

            continue;
        }

        ui.displayScreen(seatingChart, currentPlayer, centerPot);

        // If user, prompt to press SPACE to roll
        if (currentPlayer.getId() == 0)
        {
            cout << LEFT;
            typeText("Press SPACE to roll...");


            while (_getch() != ' ')
            {
            }

            cout << "\r";
            cout << LEFT << "                         ";
            cout << "\r";
        }
        else
        {
            Sleep(800);
        }

        // Gets the current roll results from the dice
        vector<char> rolls = rollDice(currentPlayer);

        cout << "\n";

        string name;

        // Prints bot's name or player's name
        if (currentPlayer.getId() != 0)
        {
            name = "BOT " + to_string(currentPlayer.getId());
        }
        else
        {
            name = currentPlayer.getName();
        }

        // Prints a static empty string to align the display
        // Uses typewriter effect to print results
        cout << LEFT;
        typeText(name + "'s results:");

        for (char r : rolls)
        {
            cout << LEFT;

            if (r == 'L')
            {
                typeText(">> Tosses a chip LEFT");
            }
            else if (r == 'R')
            {
                typeText(">> Tosses a chip RIGHT");
            }
            else if (r == 'C')
            {
                typeText(">> Places a chip in the CENTER");
            }
            else
            {
                typeText(">> Escapes Danger (*)");
            }
        }

        // Adds a delay for the user to read the results
        Sleep(3000);
               
        // Calculate how many players still have chips AFTER the turn
        int totalPlayersInGame = 0;

        for (Player& player : seatingChart)
        {
            if (player.getNumChips() > 0)
            {
                totalPlayersInGame++;
            }
        }

        // Check for winner
        if (totalPlayersInGame == 1)
        {
            ui.displayScreen(seatingChart, currentPlayer, centerPot);

            Sleep(500);
            cout << LEFT;
            typeText("GAME OVER");

            for (Player& player : seatingChart)
            {
                if (player.getNumChips() > 0)
                {
                    cout << LEFT;

                    if (player.getId() != 0)
                    {
                        typeText("BOT " + to_string(player.getId()) + " WINS!");
                    }
                    else
                    {
                        typeText(player.getName() + " WINS!");
                    }
                }
            }

            break;
        }

        index++;

        if (index >= seatingChart.size())
        {
            index = 0;
        }
    }
}
// Prints banner for the game
// Asks the user for their name
// Passes the name to the Player class
// Reads PorgsLCR.txt for the game rules
void GameManager::introText()
{
    cout << "\n";

    cout << "                        **************************************************************\n";

    cout << "                                            _       _____   _____ \n";
    cout << "                                           | |     / ____| |  __ \\\n";
    cout << "                                           | |    | |      | |__) |\n";
    cout << "                                           | |    | |      |  _  / \n";
    cout << "                                           | |____| |____  | | \\ \\ \n";
    cout << "                                           |______|\\_____| |_|  \\_\\\n";

    cout << "               ******************************************************************************\n\n";

    cout << "WELCOME TO Porgs Cantina!!!!\n";
    cout << "What is your name human?\n";
    cin >> userName;
    cout << "Hello, " << userName << "!\n\n";

    user = Player(userName, true);

    cout << "Press ENTER to continue...";
    cin.ignore();
    cin.get();
    system("cls");

    ifstream file("PorgsLCR.txt");

    if (!file)
    {
        cout << "Error opening file." << endl;
    }

    string line;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();

    cout << "\nPress ENTER to continue...";
    cin.get();
    system("cls");
}