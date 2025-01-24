#include "Level.h"
#include <iostream>
#include <cstdlib>
#include <fstream>


Level::Level() : size(0), Levels(0), Matrix() {} //simplified constructor

Level::~Level() { //destructor to free up memory after done with world.
    for (int i = 0; i < Levels; i++) {
        for (int j = 0; j < size; j++) {
            delete[] Matrix[i][j];
        }
        delete[] Matrix[i];
    }
    delete[] Matrix;
}



char Level::determineTile(int c, int n, int g, int k, int m) {
    int total = c + n + g + k + m;
    int tileChance = rand() % total; //total snould add up to 100 as stated by assignment guidelines.

    if (tileChance < c) return 'c';
    if (tileChance < c + n) return 'x';
    if (tileChance < c + n + g) return 'g';
    if (tileChance < c + n + g + k) return 'k';
    return 'm';
}

void Level::placeSpecialTiles(int level) {
    if (level < Levels - 1) {
        placeTile(level, 'w'); // Place warp pipe in all but the last level
    }
    
    placeTile(level, 'B'); // Place boss in every level
}

void Level::placeTile(int level, char tileType) {
    int posx, posy;

    bool placed = false;
    while (!placed) { //while loop to keep continually searching for empty space to place warp or boss.
        posx = rand() % size;
        posy = rand() % size;
        
        // Check if the position is initially for 'x' (empty/navigable) and not already occupied by another special tile
        if (Matrix[level][posx][posy] == 'x') {
            Matrix[level][posx][posy] = tileType;
            placed = true; //update placed so that loop does not run forever
        }
    }
}

void Level::create(int lvls, int sizeOf, int c, int n, 
                          int g, int k, int m) {
    
    Levels = lvls;
    size = sizeOf;

    Matrix = new char**[Levels];
    for (int level = 0; level < Levels; ++level) {
        Matrix[level] = new char*[size];

        // Initialize each level's grid
        for (int posx = 0; posx < size; ++posx) {
            Matrix[level][posx] = new char[size];

            { // Determine the tile type for each position
                for (int posy = 0; posy < size; ++posy) {
                    Matrix[level][posx][posy] = determineTile(c, n, g, k, m);
                }
            }
        }

        // Place special tiles after initializing the grid
        placeSpecialTiles(level);
    }
}

void Level::world(std::ofstream& outputFile){   //display whole world.
    for (int level = 0; level < Levels; level++) {
        displayCurrentLevel(level, outputFile);
    }
}

void Level::displayCurrentLevel(int index, std::ofstream& outputFile) { //display just one level that is passed through by index of level in function.
    int posx = 0;
    while (posx < size) {
        int posy = 0;
        while (posy < size) {
            outputFile << Matrix[index][posx][posy] << ' ';
            posy++;
        }
        outputFile << '\n';
        posx++;
    }
    outputFile << "==============\n";
}
int Level::getDims() //get function
{
    return size;
}
int Level::getLevels() //get function
{
    return Levels;
}
