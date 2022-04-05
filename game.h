#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stats {
    int HP;
    int ATK;
    int DEF;
    int Speed;
} stats;

typedef struct character {
    char name[20];
    stats stats;
} character;

typedef struct monster {
    char name[20];
    stats stats;
} monster;

typedef struct floor { 
    bool ground;
    bool rwall;
    bool lwall;
    bool bwall;
    bool fwall;
    bool roof;
    
} floor;

void printTitle(void);
void printRoom(floor f);