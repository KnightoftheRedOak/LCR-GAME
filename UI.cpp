#include "UI.h"
#include <iostream>
#include <vector>
#include "Player.h"
#include <windows.h>
#include <cstdlib>

using namespace std;

// Used to keep all UI text centered on screen
const string LEFT = "                                                                        ";

// Full UI display of game:
// Clears screen,
// Prints current player turn, 
// Prints player list
// Prints center pot
void UI::displayScreen(vector<Player>& seatingChart, Player& currentPlayer, int centerPot)
{
    system("cls");

    cout << "\n";

    // Prints bot header if player is a bot
    if (currentPlayer.getId() != 0)
    {
        cout << LEFT << "====================================\n";
        cout << LEFT << "         ==== BOT " << currentPlayer.getId() << " TURN ====\n";
        cout << LEFT << "         ===== " << currentPlayer.getNumChips() << " CHIPS =====\n";
        cout << LEFT << "====================================\n\n";
    }
    // Prints player header if player is user
    else
    {
        cout << LEFT << "====================================\n";
        cout << LEFT << "         ==== " << currentPlayer.getName() << " TURN ====\n";
        cout << LEFT << "         ===== " << currentPlayer.getNumChips() << " CHIPS =====\n";
        cout << LEFT << "====================================\n\n";
    }

    // Calls function to print all players and their chip counts
    updatePlayersChips(seatingChart, currentPlayer);

    cout << "\n";

    // Displays center pot value
    cout << LEFT << "             CENTER POT: " << centerPot << "\n\n";

    // Divider line for UI
    cout << LEFT << "------------------------------------\n\n";
}

// Updates and prints all players and their chip counts
// Highlights current player with >>
void UI::updatePlayersChips(vector<Player>& seatingChart, Player& currentPlayer)
{
    for (Player& player : seatingChart)
    {
        cout << LEFT;

        // Displays indicator for current player
        if (currentPlayer.getId() == player.getId())
        {
            cout << ">> ";
        }
        else
        {
            cout << "   ";
        }

        // Prints bot info
        if (player.getId() != 0)
        {
            cout << "     BOT " << player.getId();
            cout << "        CHIPS: " << player.getNumChips();
        }
        else
        {
            // Prints player name
            cout << "      " << player.getName();

            // Adjusts spacing based on name length for alignment
            if (player.getName().length() == 3)
            {
                cout << "         CHIPS: " << player.getNumChips();
            }
            else if (player.getName().length() == 4)
            {
                cout << "        CHIPS: " << player.getNumChips();
            }
            else if (player.getName().length() == 5)
            {
                cout << "       CHIPS: " << player.getNumChips();
            }
            else if (player.getName().length() == 6)
            {
                cout << "      CHIPS: " << player.getNumChips();
            }
            else if (player.getName().length() == 7)
            {
                cout << "     CHIPS: " << player.getNumChips();
            }
            else
            {
                cout << "    CHIPS: " << player.getNumChips();
            }
        }

        cout << "\n";
    }
}

// Returns the roll result 
char UI::printRollResult(char result)
{
    return result;
}

// Handles roll animation for dice
// Displays spinning slots and final results based on number of rolls
void UI::rollAnimation(Player& player, int totalRolls, vector<char> rolls)
{
    int speed;

    // Faster animation for bots, slower for player
    if (player.getId() != 0)
    {
        speed = 40;
    }
    else
    {
        speed = 80;
    }

    cout << LEFT << "ROLLING...\n";

    // Default slot values
    char slot1 = '*';
    char slot2 = '*';
    char slot3 = '*';

    // Animation for 1 roll
    if (totalRolls == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < spinAnimation.size(); j++)
            {
                slot1 = spinAnimation[rand() % spinAnimation.size()];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "]";
                Sleep(speed);
            }

            // Locks in final result
            if (i == 3 && rolls.size() > 0)
            {
                slot1 = rolls[0];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "]";
            }

            // Delay after final roll
            if (i == 3)
            {
                Sleep(300);
            }
            else
            {
                Sleep(100);
            }
        }
    }
    // Animation for 2 rolls
    else if (totalRolls == 2)
    {
        // First slot animation
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < spinAnimation.size(); j++)
            {
                slot1 = spinAnimation[rand() % spinAnimation.size()];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "]";
                Sleep(speed);
            }

            if (i == 3 && rolls.size() > 0)
            {
                slot1 = rolls[0];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "]";
            }

            if (i == 3)
            {
                Sleep(300);
            }
            else
            {
                Sleep(100);
            }
        }

        // Second slot animation
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < spinAnimation.size(); j++)
            {
                slot2 = spinAnimation[rand() % spinAnimation.size()];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "] [" << slot2 << "]";
                Sleep(speed);
            }

            if (i == 3 && rolls.size() > 1)
            {
                slot2 = rolls[1];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "] [" << slot2 << "]";
            }

            if (i == 3)
            {
                Sleep(300);
            }
            else
            {
                Sleep(100);
            }
        }
    }
    // Animation for 3 rolls
    else if (totalRolls == 3)
    {
        // First slot
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < spinAnimation.size(); j++)
            {
                slot1 = spinAnimation[rand() % spinAnimation.size()];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "]";
                Sleep(speed);
            }

            if (i == 3 && rolls.size() > 0)
            {
                slot1 = rolls[0];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "]";
            }

            if (i == 3)
            {
                Sleep(300);
            }
            else
            {
                Sleep(100);
            }
        }

        // Second slot
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < spinAnimation.size(); j++)
            {
                slot2 = spinAnimation[rand() % spinAnimation.size()];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "] [" << slot2 << "]";
                Sleep(speed);
            }

            if (i == 3 && rolls.size() > 1)
            {
                slot2 = rolls[1];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "] [" << slot2 << "]";
            }

            if (i == 3)
            {
                Sleep(300);
            }
            else
            {
                Sleep(100);
            }
        }

        // Third slot
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < spinAnimation.size(); j++)
            {
                slot3 = spinAnimation[rand() % spinAnimation.size()];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "] [" << slot2 << "] [" << slot3 << "]";
                Sleep(speed);
            }

            if (i == 3 && rolls.size() > 2)
            {
                slot3 = rolls[2];
                cout << "\r";
                cout << LEFT << "             [" << slot1 << "] [" << slot2 << "] [" << slot3 << "]";
            }

            if (i == 3)
            {
                Sleep(300);
            }
            else
            {
                Sleep(100);
            }
        }
    }

    cout << "\n";
}