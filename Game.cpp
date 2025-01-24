
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Game.h"
#include "Level.h"
#include "Mario.h"
#include "Reader.h"
#include <string>
#include "Enemy.h"

// Includes necessary headers for game mechanics, entities, and utility

// Default destructor for Game
Game::~Game() {}

// Game constructor:
Game::Game() {
   
}

// Begins the game loop, executing turns until the game ends
void Game::startGame() {
    reader.loadGameSettings(); // Loads game configuration from a settings file
     // Sets up the game level with parameters obtained from the reader
    level.create(reader.getLevelCount(), reader.getBoardDimensions(),
    reader.getCoinRatio(),reader.getEmptySpaceRatio(),
    reader.getGoombaRatio(), reader.getKoopaRatio(),
    reader.getMushroomRatio());

    posx = rand() % level.getDims();
    posy = rand() % level.getDims();

    gameOver = false; // Initial game state setup
    chosenLevel = 0;
    bossDead = false;

    mario.setLives(reader.getInitialLives()); // Assigns Mario's initial number of lives
    output.open("game_log.txt"); // Opens the game log file for output
    displayGameWorld(); // Displays the initial state of the game world
    startPosition(); // Outputs Mario's starting position

    // Continues executing game turns until the game is over
    while (!gameOver && mario.isAlive()) {
        executeTurn();
        moves++;
    }

    output.close(); // Closes the game log file
}

void Game::displayGameWorld() {
    level.world(output);
}

void Game::startPosition() {
    output << "Mario starts at (" << posx << ", " << posy << ")" << std::endl;
    output << "==============" << std::endl;
}

// Executes a single turn of the game
void Game::executeTurn() {
    currspace = level.Matrix[chosenLevel][posx][posy]; // Retrieves the character at Mario's current position
    
    level.Matrix[chosenLevel][posx][posy] = 'H'; // Marks Mario's position on the game world

    level.displayCurrentLevel(chosenLevel, output); // Displays the current level state

    output << "Level: " << chosenLevel << ": Mario is at position: (" << posx << ", " << posy << "). ";

    // Decides Mario's interaction based on the space he lands on
    switch (currspace) {
        case 'c': collectCoin(); break;
        case 'B': battleEnemy('B'); break;
        case 'x': landOnEmptySpace(); break;
        case 'w': useWarpPipe(); break;
        case 'k': battleEnemy('k'); break;
        case 'm': gainMushroom(); break;
        case 'g': battleEnemy('g'); break;
        
    }

    output << "Power Level: " << mario.Power() << ", Lives: " << mario.Lives() << ", Coins: " << mario.Coins() << ". ";

    level.Matrix[chosenLevel][posx][posy] = currspace; // Restores the character at Mario's previous position
    decideNextMove(); // Decides the next move based on the game state
    

    output << "==============\n";
}

void Game::gainMushroom() {
    // This function is called when Mario gains a mushroom.
    mario.upgrade(); // increase power or lives
    currspace = 'x'; // Mark the mushroom as used
    output << "Mario ate a mushroom" << std::endl;
}

void Game::collectCoin() {
    // This function is called when Mario collects a coin.
    mario.collectCoin(); // increment coin count
    currspace = 'x'; // Mark the space as collected/empty
    output << "Mario collected a coin. " << std::endl;
}


void Game::landOnEmptySpace() {
    // This function is called when Mario lands on an empty space.
    output << "The position is empty. " << std::endl;
}
void Game::battleEnemy(char type){
    Enemy enemy;
    switch(type){
        case 'B': if(enemy.isDead(type))
            {   
            mario.recordVictory();
            currspace = 'x';
            bossDead = true;
            output << "Mario fought the level boss and won. " <<std::endl;
            break;

            } else {
            mario.takeDamage(); //or took L and takes damage.
            output << "Mario fought da boss and lost. " << std::endl ;
            break;
            } 

        case 'k': if(enemy.isDead(type))
        {
            mario.recordVictory();
            currspace = 'x';
            output << "Mario fought a koopa and won. " << std::endl;
            break;
        } else {
            mario.takeDamage(); //or took L and takes damage.
            output << "Mario fought a koopa and lost. " << std::endl ;
            break;
        }
        case 'g': if(enemy.isDead(type))
        {
            mario.recordVictory();
            currspace = 'x';
            output << "Mario fought a goomba and won. " << std::endl;
            break;
        } else {
            mario.takeDamage();
            output << "Mario lost to a Goomba. " << std::endl;
            break;
        }
        default: break; // just incase
    }
}

void Game::useWarpPipe() {
    
    

    if(currspace == 'w')
    {
    output << "Mario warped. " << std::endl;
    }
    //warp is used for level boss too, as this sends player to next level, dual functionality.
    if(currspace != 'w')
    {
    output << "Level boss defeated voyaging to the next level." <<std::endl;
    }
    currspace = 'x';
    chosenLevel++; // Advance to the next level
    // Generate new random location for Mario
    posx = rand() % level.getDims();
    posy = rand() % level.getDims();
    
}


void Game::executeRandomMove() {
    int direction = rand() % 4; // Randomly choose a direction: 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
    switch (direction) {
        case 0: moveMario("UP"); break;
        case 1: moveMario("RIGHT"); break;
        case 2: moveMario("DOWN"); break;
        case 3: moveMario("LEFT"); break;
        default: break; // Just for safety
    }
}

void Game::decideNextMove() {

    if (!mario.isAlive()) {
        output << "Game Over. Mario has no lives left." << std::endl;
        // weird case, had to subtract 65535, weird, it is the maximum number that can be stored in unsigned short int
        output << "Moves taken : " << (moves - 65535) << std::endl;
        if(moves-65535 < 10 )
        {
            output << "You are not the best at this game" << std::endl;
        }
        else if(moves-65535 < 30)
        {
            output << "That's not a lot of moves, better luck next time" << std::endl;
        }
       
       
        gameOver = true;
        
    }
    else if (bossDead && chosenLevel == level.getLevels()-1) {
        output << "Mario will stay put and relax... Victory! The princess has been rescued, and the hero triumphs!" << std::endl;
        // same case as above function ----------
        output << "Moves taken : " << (moves - 65535) << std::endl;
        if(moves-65535 < 10)
        {
            output << "You are a pro, or should I say, random number generator is." << std::endl;
        }
        else if(moves-65535 < 30)
        {
            output << "Not bad, " << (moves - 65535) <<  " moves is pretty good" << std::endl;
        }
        
        gameOver = true;
    }
    else if (bossDead) {
        useWarpPipe();
        bossDead = false;
    }
    else {
        //if it reaches here, keep the game going and do not do any of the special cases.
    executeRandomMove();
    }
}


void Game::moveMario(const std::string& direction) {
    // Update Mario's position based on the direction
    // Ternary operator, if pos(x == 0 is true, posx = level.getDims()-1, if its false posx = posx - 1)
    if (direction == "UP") {
        posx = (posx == 0) ? level.getDims() - 1 : posx - 1;
    } else if (direction == "RIGHT") {
        posy = (posy == level.getDims() - 1) ? 0 : posy + 1;
    } else if (direction == "DOWN") {
        posx = (posx == level.getDims() - 1) ? 0 : posx + 1;
    } else if (direction == "LEFT") {
        posy = (posy == 0) ? level.getDims() - 1 : posy - 1;
    }
    output << "Mario moves " << direction << "." << std::endl;
    // After moving, you could check for interactions with the new space Mario lands on
}






