#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
    public:
        Enemy();
        ~Enemy();
        bool isDead(char type); // Determines wether mario beats boss with boolean value as return.
};

#endif