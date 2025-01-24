#include "Reader.h"
#include <fstream>
#include <iostream>

Reader::Reader(){} // constructor
Reader::~Reader(){} // destructor

void Reader::loadGameSettings() {
    std::ifstream specFile("input-spec.txt");
    if (!specFile) {
        std::cerr << "Failed to open spec.txt for reading game settings." << std::endl;
        return;
    }
    
    // Directly assign file input to member variables
    specFile >> levelCount >> boardDimensions >> initialLives
             >> coinRatio >> emptySpaceRatio >> goombaRatio 
             >> koopaRatio >> mushroomRatio;
}

// Inline get functions
int Reader::getLevelCount() const { return levelCount; }
int Reader::getBoardDimensions() const { return boardDimensions; }
int Reader::getInitialLives() const { return initialLives; }
double Reader::getCoinRatio() const { return coinRatio; }
double Reader::getGoombaRatio() const { return goombaRatio; }
double Reader::getKoopaRatio() const { return koopaRatio; }
double Reader::getMushroomRatio() const { return mushroomRatio; }
double Reader::getEmptySpaceRatio() const { return emptySpaceRatio; }

