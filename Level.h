#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>

class Level {
public:
    Level(); // Constructor
    ~Level(); // Destructor

    // Generates the game levels based on the input parameters
    void create(int numLevels, int length, int coin, int nothing, 
                       int goomba, int koopa, int mushroom);
    
    // Prints a specific level to the provided output file stream
    void displayCurrentLevel(int index, std::ofstream& outputFile);
    
    // Prints all levels to the provided output file stream
    void world(std::ofstream& outputFile);
    int getLevels();
    int getDims();
    void placeTile(int level, char tileType);
    char determineTile(int coin, int nothing, int goomba, int koopa, int mushroom);
    void placeSpecialTiles(int level);


    int size; // The size of each level dimension
    int Levels; // The number of levels in the game
    char ***Matrix; // A 3D array representing the game world across multiple levels

    
};

#endif // LEVEL_H