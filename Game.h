#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include "Level.h"
#include "Mario.h"
#include "Reader.h"

class Game {
private:
    Mario mario; // Mario character
    Level level; // Game level handler
    Reader reader; // To load game settings
    std::ofstream output; // File stream for logging game events
    int posx, posy; // Current position of Mario
    int chosenLevel; // Current game level
    bool bossDead; // Indicates if the boss of the current level is defeated
    bool gameOver; // Indicates if the game has ended
    char currspace; // Temporarily stores the character Mario interacts with
    int moves;
    std::string Moves;
    // Utility functions for game actions
    void landOnEmptySpace();
    void collectCoin();
    void useWarpPipe();
    void decideNextMove();
    void executeRandomMove();
    void gainMushroom();
    void battleEnemy(char type);
    void moveMario(const std::string& direction);
    void startPosition();
    void executeTurn();
    void displayGameWorld();

public:
    Game(); // Constructor
    ~Game(); // Destructor
    void startGame(); // Starts the game loop
};

#endif // GAME_H
