#include "Game.h"
#include "Reader.h"
#include <chrono>




int main(int argc, char **argv){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //program is ran at different times, thus seed is always different (seed = time since epoch)
    srand(seed); //because seed is always different, the random number generator will always produce different numbers
    Game game;
    game.startGame(); // plays the entire game

    return 0;
}