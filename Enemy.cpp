#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(){

}
//default constructor

Enemy::~Enemy(){

}
// default destructor


bool Enemy::isDead(char type){
    if(type == 'B')
    {
        int luck = rand() % 100; // Generate a random number between 0 and 99
        return luck < 50; // 50% chance that Mario defeats da Enemy
    }
    else if(type == 'k')
    {
        int luck = rand() % 100; // Generate a random number between 0 and 99
        return luck < 65; // 65% chance that Mario defeats the Koopa
    }
    else if(type == 'g')
    {
        int luck = rand() % 100; // Generate a random number between 0 and 99
        return luck < 80; // 80% chance mario defeats  Goomba
    }
    
}