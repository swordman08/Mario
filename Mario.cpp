#include "Mario.h"

Mario::Mario(){
    lives = 0; 
    coins = 0; 
    powerLevel = 0;
    enemiesDefeated = 0;
}
 // Initializes Mario with default values

Mario::~Mario(){}; // Default destructor

void Mario::collectCoin() {
   coins = (coins + 1) % 20; // Increment coins, and wrap around at 20
    if (coins == 0) { // If coins wrap around, Mario gains a life
        lives++;
    }
}

void Mario::upgrade() {
    if (powerLevel < 2) { // Assuming the maximum power level is 2
        powerLevel++;
    }
}

void Mario::takeDamage() {
    if (powerLevel > 0) {
        powerLevel--;
    } else if (lives > 0) {
        lives--;
        enemiesDefeated = 0;
    }
}

void Mario::recordVictory() {
    enemiesDefeated = (enemiesDefeated + 1) % 8; // Increment and reset after every 7 enemies
if (enemiesDefeated == 0) { // If reset happened, Mario defeated 7 enemies
    lives++; // Increment lives as Mario gains a life after defeating 7 enemies
}
}


bool Mario::isAlive() const {
    return lives > 0;
}

int Mario::Lives() const {
    return lives;
}

int Mario::Coins() const {
    return coins;
}

int Mario::Power() const {
    return powerLevel;
}
//mutator
void Mario::setLives(int lives1){
    lives = lives1;
}