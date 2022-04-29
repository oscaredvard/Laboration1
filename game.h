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
} stats;

typedef struct actor {
    char name[20];
    stats stats;
} actor;

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