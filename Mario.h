#ifndef MARIO_H
#define MARIO_H

class Mario {
public:
    Mario(); // Constructor
    ~Mario(); // Destructor

    // Interactions
    void collectCoin(); // Increments Mario's coin count
    void upgrade(); // Increases Mario's power level
    void takeDamage(); // Decreases Mario's power level or lives
    void recordVictory(); // Actions to take when Mario defeats an enemy
    void setLives(int lives);

    // Status checks
    bool isAlive() const; // Checks if Mario still has lives left
    int Lives() const; // Returns the number of lives Mario has
    int Coins() const; // Returns the number of coins collected
    int Power() const; // Returns Mario's current power level

private:
    int lives; // Number of lives Mario has
    int coins; // Number of coins collected
    int powerLevel; // Mario's power level
    int enemiesDefeated; //How many enemies defeated in one life.
};

#endif // MARIO_H
