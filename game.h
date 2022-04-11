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

typedef struct GR { 
    bool ground;
    bool roof;
} GR;

typedef struct XW {
    bool xwall;
} XW;

typedef struct ZW {
    bool zwall;
} ZW;

void printTitle(void);
void printRoom(GR f);