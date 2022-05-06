#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stats {
    int LV;
    int MAX_HP;
    int HP;
    int ATK;
    int DEF;
    int Speed;
    int EXP;
    int gold;
} stats;

typedef struct equipment {
    int weapon;
    int defense;
} equipment;

typedef struct inventory {
    int potion;
    int sword;
    int shield;
} inventory;

typedef struct actor {
    char name[20];
    stats stats;
    equipment equipment;
    inventory inventory;
} actor;

typedef struct latest {
    int x;
    int y;
    int z;
} latest;

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