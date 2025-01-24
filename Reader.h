#ifndef READER_H
#define READER_H

class Reader {
public:
    Reader(); // Default constructor
    ~Reader(); // Default destructor

    void loadGameSettings(); // Loads game settings from a file

    // Getter functions to access game settings
    int getLevelCount() const;
    int getBoardDimensions() const;
    int getInitialLives() const;
    double getCoinRatio() const;
    double getGoombaRatio() const;
    double getKoopaRatio() const;
    double getMushroomRatio() const;
    double getEmptySpaceRatio() const;
    

private:
    int levelCount; // Number of levels
    int boardDimensions; // Dimensions of the game board
    int initialLives; // Initial number of lives for Mario
    double goombaRatio; // Percentage of Goombas
    double koopaRatio; // Percentage of Koopas
    double mushroomRatio; // Percentage of Mushrooms
    double coinRatio; // Percentage of coins
    double emptySpaceRatio; // Percentage of empty spaces
};

#endif // READER_H
