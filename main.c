#include "include/raylib.h"
#include "include/raymath.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "game.h"

//gcc main.c -o game.exe -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

#define MAX 5

//Size parameters for 1st floor
#define GR_MAX_X_1 5
#define GR_MAX_Z_1 5
#define XW_MAX_X_1 (GR_MAX_X_1+1)
#define XW_MAX_Z_1 GR_MAX_Z_1
#define ZW_MAX_X_1 GR_MAX_X_1
#define ZW_MAX_Z_1 (GR_MAX_Z_1+1)

//Size parameters for 2nd floor
#define GR_MAX_X_2 5
#define GR_MAX_Z_2 5
#define XW_MAX_X_2 (GR_MAX_X_2+1)
#define XW_MAX_Z_2 GR_MAX_Z_2
#define ZW_MAX_X_2 GR_MAX_X_2
#define ZW_MAX_Z_2 (GR_MAX_Z_2+1)

int main() 
{
    srand(time(NULL));
    rand();

    int M2 = 1000, N2 = 2000;
    int random = 
    M2 + rand() / (RAND_MAX / (N2 - M2 + 1) + 1);

    int monsterlevel = 1;
    int characterlevel = 5;

    int fcounter = 1;

    //Player
    actor I;
    I.stats.LV = 1;
    I.stats.MAX_HP = 10;
    I.stats.HP = 10;
    I.stats.ATK = 5;
    I.stats.DEF = 2;
    I.stats.Speed = 5;
    I.stats.EXP = 0;
    I.stats.gold = 100;
    I.equipment.weapon = 0;
    I.equipment.defense = 0;
    I.inventory.potion = 2;

    //Monsters
    actor Slime;
    Slime.stats.LV = 1;
    Slime.stats.HP = 10;
    Slime.stats.ATK = 5;
    Slime.stats.DEF = 5;
    Slime.stats.Speed = 2;
    Slime.stats.EXP = 50;
    Slime.stats.gold = 5;

    actor Bat;
    Bat.stats.LV = 1;
    Bat.stats.HP = 7;
    Bat.stats.ATK = 5;
    Bat.stats.DEF = 5;
    Bat.stats.Speed = 7;
    Bat.stats.EXP = 50;
    Bat.stats.gold = 10;

    actor Ghost;
    Ghost.stats.LV = 1;
    Ghost.stats.HP = 10;
    Ghost.stats.ATK = 5;
    Ghost.stats.DEF = 5;
    Ghost.stats.Speed = 6;
    Ghost.stats.EXP = 50;

    actor * aptr;

    typedef enum BattleScreen {INTRO = 0, OPT1, OPT2, OPT3, OPT4, ATK_SEQ1, ATK_SEQ2, ATK_SEQ3, ATK_SEQ4, DEF_SEQ1, DEF_SEQ2, DEF_SEQ3, ITEM_OPT1, ITEM_SEQ1, ITEM_ERR, ITEM_SEQ2, ITEM_SEQ3, ITEM_SEQ4, ITEM_SEQ5, FLEE, FLEE_S, FLEE_F, VICTORY, EXP, COINS, LVL_UP, DEAD, GAME_OVER} BattleScreen;

    BattleScreen Battle = INTRO;

    typedef enum Menu {START = 0, M_OPT1, M_OPT2, STATS, ITEMS1, ITEMS2, ITEMS3, ITEMS4} Menu;

    Menu menu = START;

    typedef enum Chest {INITIAL = 0, GOT, DESC} Chest;

    Chest chest1 = INITIAL;

    typedef enum Shop {ITEM1 = 0, ITEM2, ITEM3} Shop;

    Shop shop_nav = ITEM1;

    time_t timer;
    time_t c_timer;
    int exit = 1; 

    int HPcpy;

    int HPcounter;

    int nxtlvlEXP = pow(2,I.stats.LV)*50;

    int done = 0;

    int i;

    char * text;

    char * tip_ptr;

    char tiptext[30] = {"PRESS SPACE FOR MENU"};

    tip_ptr = tiptext;
    
    char * menutext;

    char menu_opt1[20] = {">Stats   Items"};

    menutext = menu_opt1;

    char menu_opt2[20] = {" Stats  >Items"};

    char stats[50];

    sprintf(stats, "LV:%d\nHP:%d/%d\nATK:%d\nDEF:%d\nSpeed:%d\nEXP:%d/%d -> LV:%d\nGold:%d\n", I.stats.LV, I.stats.HP, I.stats.MAX_HP, I.stats.ATK, I.stats.DEF, I.stats.Speed, I.stats.EXP, nxtlvlEXP, I.stats.LV+1, I.stats.gold);

    char underscore[10] = {"_"};
    char inventory_opt1[60];
    sprintf(inventory_opt1, ">Potion x%d\n %s\n %s\n %s", I.inventory.potion, underscore, underscore, underscore);
    char inventory_opt2[60];
    sprintf(inventory_opt2, " Potion x%d\n>%s\n %s\n %s", I.inventory.potion, underscore, underscore, underscore);
    char inventory_opt3[60];
    sprintf(inventory_opt3, " Potion x%d\n %s\n>%s\n %s", I.inventory.potion, underscore, underscore, underscore);
    char inventory_opt4[60];
    sprintf(inventory_opt4, " Potion x%d\n %s\n %s\n>%s", I.inventory.potion, underscore, underscore, underscore);

    char * floortext;

    char floor[4] = "FL1";

    floortext = floor;

    //Player HP

    char HP[3];

    sprintf(HP,"%d", I.stats.HP);

    char HPtext[6] = {"HP:"};

    strcat(HPtext, HP);

    char * HPptr = HPtext;

    //Monster HP
    char mHP[3];

    sprintf(mHP,"%d", Slime.stats.HP);

    char mHPtext[6] = {"HP:"};

    strcat(mHPtext, mHP);

    char * mHPptr = mHPtext;

    char name[20] = {"Oscar "};

    char defend1[20];

    char flee1[20] = {"You try to flee..."};

    char flee_f[30] = {"But the monster cornered you!"};

    char dead[20] = {"You died"};

    char game_over[20] = {"GAME OVER"};

    char flee_s[20] = {"You succeed!"};

    char item[20];

    sprintf(item, ">Potion x%d", I.inventory.potion); 

    char item_err[20] = {"You have no left!"};

    char use_item[20] = {"You used the potion"};

    char level_up[20] = {"You gained a level!"};

    //Monster names
    char mn1[20] = {"Slime"};

    char monstertext[20] = {"A monster attacks!"};

    char I_HP_lose[20] = {"You lose __ HP"};
    char I_HP_gain[20] = {"You gain __ HP"};
    char monster_HP_lose[30] = {"The monster loses __ HP"};

    char defeat[30] = {"You defeated the monster!"};

    char EXP_gain[20] = {"You gain __ EXP"};

    char gold[20] = {"You get __ gold"};

    char got_tele[30] = {"You got a Teleporter!"};
    char desc_tele[60] = {"With this you can teleport\nto the last ladder you used."};
    char * chesttext;
    chesttext = got_tele;

    //text = monstertext;

    char battlemenu1[100] = {">Attack  Defend  Items  Flee"};
    char battlemenu2[100] = {" Attack >Defend  Items  Flee"};
    char battlemenu3[100] = {" Attack  Defend >Items  Flee"};
    char battlemenu4[100] = {" Attack  Defend  Items >Flee"};

    char I_attack[30] = {"You attack the monster"};
    char monster_attack[30] = {"The monster attacks you!"};

    char I_defend[20] = {"You defend yourself"};

    text = monstertext;

    char * shop_item_text;
    char * shop_q_text;
    char question[30] = {"What would you like to buy?"};
    shop_q_text = question;
    char thanks[30] = {"Thank you for your purchase!"};
    char cant_afford[50] = {"You don't have enough gold for this item."};
    char already_bought[50] = {"You've already bought this item."};
    char shop_sword[100];
    char shop_shield[100];
    char shop_potion[100];
    int sword_cost = 30;
    int shield_cost = 20;
    int potion_cost = 10;
    sprintf(shop_sword, ">Sword          Shield          Potion\n  %d G            %d G            %d G", sword_cost, shield_cost, potion_cost);
    sprintf(shop_shield," Sword         >Shield          Potion\n  %d G            %d G            %d G", sword_cost, shield_cost, potion_cost);
    sprintf(shop_potion," Sword          Shield         >Potion\n  %d G            %d G            %d G", sword_cost, shield_cost, potion_cost);

    char goldtext[20];
    sprintf(goldtext, "My gold: %d G", I.stats.gold);

    const int screenWidth = 1024;
    const int screenHeight = 576;

    InitWindow(screenWidth, screenHeight, "Dungeon Crawler");

    Camera camera = { 0 };
    camera.position = (Vector3){ 1.0f, 2.0f, 1.0f };
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Camera2D camera2D = { 0 };

    Texture2D w_texture = LoadTexture("img/stonewall.png");
    Texture2D g_texture = LoadTexture("img/stonefloor.png");
    Texture2D rf_texture = LoadTexture("img/stonewall.png");
    Texture2D ladder = LoadTexture("img/ladder.png");
    Texture2D hole = LoadTexture("img/hole2.png");

    Texture2D slime_png = LoadTexture("img/slime.png");
    Texture2D bat_png = LoadTexture("img/bat.png");

    Model chest = LoadModel("models/chest.vox");      
    Model openchest = LoadModel("models/openchest.vox");  
    Vector3 chest_pos = { 0.0f, 0.0f, 8.0f };   
    Model * chestptr = &chest;

    Model shop = LoadModel("models/shop.vox");  
    Vector3 shop_pos = {1.5f, 0.0f, 34.0f};

    //fcounter = 2;

    Texture2D  * imgptr;

    SetCameraMode(camera, CAMERA_FIRST_PERSON);  

    SetTargetFPS(144);

    //Spacial coordinates
    int x, z;
    x = 0;
    z = 0;

    //General floor pointers
    GR (*GR_floor)[GR_MAX_X_1][GR_MAX_Z_1];
    XW (*XW_floor)[XW_MAX_X_1][XW_MAX_Z_1];
    ZW (*ZW_floor)[ZW_MAX_X_1][ZW_MAX_Z_1];

    //Creating 1st floor
    GR GR_floor1[GR_MAX_X_1][GR_MAX_Z_1];
    XW XW_floor1[XW_MAX_X_1][XW_MAX_Z_1];
    ZW ZW_floor1[ZW_MAX_X_1][ZW_MAX_Z_1];

    //Determining layout for 1st floor

    //Ground parameters
    GR_floor1[0][0].ground = true;
    GR_floor1[0][1].ground = true;
    GR_floor1[0][2].ground = true;
    GR_floor1[0][3].ground = true;
    GR_floor1[0][4].ground = true;

    GR_floor1[1][0].ground = false;
    GR_floor1[1][1].ground = false;
    GR_floor1[1][2].ground = false;
    GR_floor1[1][3].ground = false;
    GR_floor1[1][4].ground = true;

    GR_floor1[2][0].ground = true;
    GR_floor1[2][1].ground = true;
    GR_floor1[2][2].ground = true;
    GR_floor1[2][3].ground = true;
    GR_floor1[2][4].ground = true;

    GR_floor1[3][0].ground = true;
    GR_floor1[3][1].ground = false;
    GR_floor1[3][2].ground = false;
    GR_floor1[3][3].ground = false;
    GR_floor1[3][4].ground = false;

    GR_floor1[4][0].ground = true;
    GR_floor1[4][1].ground = true;
    GR_floor1[4][2].ground = true;
    GR_floor1[4][3].ground = true;
    GR_floor1[4][4].ground = true;

    //X-wall parameters
    XW_floor1[0][0].xwall = true;
    XW_floor1[0][1].xwall = true;
    XW_floor1[0][2].xwall = true;
    XW_floor1[0][3].xwall = true;
    XW_floor1[0][4].xwall = true;

    XW_floor1[1][0].xwall = true;
    XW_floor1[1][1].xwall = true;
    XW_floor1[1][2].xwall = true;
    XW_floor1[1][3].xwall = true;
    XW_floor1[1][4].xwall = false;

    XW_floor1[2][0].xwall = true;
    XW_floor1[2][1].xwall = true;
    XW_floor1[2][2].xwall = true;
    XW_floor1[2][3].xwall = true;
    XW_floor1[2][4].xwall = false;

    XW_floor1[3][0].xwall = false;
    XW_floor1[3][1].xwall = true;
    XW_floor1[3][2].xwall = true;
    XW_floor1[3][3].xwall = true;
    XW_floor1[3][4].xwall = true;

    XW_floor1[4][0].xwall = false;
    XW_floor1[4][1].xwall = true;
    XW_floor1[4][2].xwall = true;
    XW_floor1[4][3].xwall = true;
    XW_floor1[4][4].xwall = true;

    XW_floor1[5][0].xwall = true;
    XW_floor1[5][1].xwall = true;
    XW_floor1[5][2].xwall = true;
    XW_floor1[5][3].xwall = true;
    XW_floor1[5][4].xwall = true;

    //Z-wall parameters
    ZW_floor1[0][0].zwall = true;
    ZW_floor1[0][1].zwall = false;
    ZW_floor1[0][2].zwall = false;
    ZW_floor1[0][3].zwall = false;
    ZW_floor1[0][4].zwall = false;
    ZW_floor1[0][5].zwall = true;

    ZW_floor1[1][0].zwall = false;
    ZW_floor1[1][1].zwall = false;
    ZW_floor1[1][2].zwall = false;
    ZW_floor1[1][3].zwall = false;
    ZW_floor1[1][4].zwall = true;
    ZW_floor1[1][5].zwall = true;

    ZW_floor1[2][0].zwall = true;
    ZW_floor1[2][1].zwall = false;
    ZW_floor1[2][2].zwall = false;
    ZW_floor1[2][3].zwall = false;
    ZW_floor1[2][4].zwall = false;
    ZW_floor1[2][5].zwall = true;

    ZW_floor1[3][0].zwall = true;
    ZW_floor1[3][1].zwall = true;
    ZW_floor1[3][2].zwall = false;
    ZW_floor1[3][3].zwall = false;
    ZW_floor1[3][4].zwall = false;
    ZW_floor1[3][5].zwall = false;

    ZW_floor1[4][0].zwall = true;
    ZW_floor1[4][1].zwall = false;
    ZW_floor1[4][2].zwall = false;
    ZW_floor1[4][3].zwall = false;
    ZW_floor1[4][4].zwall = false;
    ZW_floor1[4][5].zwall = true;

    //Roof parameters
    GR_floor1[0][0].roof = true;
    GR_floor1[0][1].roof = true;
    GR_floor1[0][2].roof = true;
    GR_floor1[0][3].roof = true;
    GR_floor1[0][4].roof = true;

    GR_floor1[1][0].roof = false;
    GR_floor1[1][1].roof = false;
    GR_floor1[1][2].roof = false;
    GR_floor1[1][3].roof = false;
    GR_floor1[1][4].roof = true;

    GR_floor1[2][0].roof = true;
    GR_floor1[2][1].roof = true;
    GR_floor1[2][2].roof = true;
    GR_floor1[2][3].roof = true;
    GR_floor1[2][4].roof = true;

    GR_floor1[3][0].roof = true;
    GR_floor1[3][1].roof = false;
    GR_floor1[3][2].roof = false;
    GR_floor1[3][3].roof = false;
    GR_floor1[3][4].roof = false;

    GR_floor1[4][0].roof = true;
    GR_floor1[4][1].roof = true;
    GR_floor1[4][2].roof = true;
    GR_floor1[4][3].roof = true;
    GR_floor1[4][4].roof = true;

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //Creating 2nd floor
    GR GR_floor2[GR_MAX_X_1][GR_MAX_Z_1];
    XW XW_floor2[XW_MAX_X_1][XW_MAX_Z_1];
    ZW ZW_floor2[ZW_MAX_X_1][ZW_MAX_Z_1];

    GR_floor2[0][0].ground = true;
    GR_floor2[0][1].ground = true;
    GR_floor2[0][2].ground = true;
    GR_floor2[0][3].ground = true;
    GR_floor2[0][4].ground = true;

    GR_floor2[1][0].ground = true;
    GR_floor2[1][1].ground = false;
    GR_floor2[1][2].ground = true;
    GR_floor2[1][3].ground = false;
    GR_floor2[1][4].ground = true;

    GR_floor2[2][0].ground = true;
    GR_floor2[2][1].ground = true;
    GR_floor2[2][2].ground = true;
    GR_floor2[2][3].ground = true;
    GR_floor2[2][4].ground = true;

    GR_floor2[3][0].ground = true;
    GR_floor2[3][1].ground = false;
    GR_floor2[3][2].ground = true;
    GR_floor2[3][3].ground = false;
    GR_floor2[3][4].ground = true;

    GR_floor2[4][0].ground = true;
    GR_floor2[4][1].ground = true;
    GR_floor2[4][2].ground = true;
    GR_floor2[4][3].ground = true;
    GR_floor2[4][4].ground = true;

    //X-wall parameters
    XW_floor2[0][0].xwall = true;
    XW_floor2[0][1].xwall = true;
    XW_floor2[0][2].xwall = true;
    XW_floor2[0][3].xwall = true;
    XW_floor2[0][4].xwall = true;

    XW_floor2[1][0].xwall = false;
    XW_floor2[1][1].xwall = true;
    XW_floor2[1][2].xwall = false;
    XW_floor2[1][3].xwall = true;
    XW_floor2[1][4].xwall = false;

    XW_floor2[2][0].xwall = false;
    XW_floor2[2][1].xwall = true;
    XW_floor2[2][2].xwall = false;
    XW_floor2[2][3].xwall = true;
    XW_floor2[2][4].xwall = false;

    XW_floor2[3][0].xwall = false;
    XW_floor2[3][1].xwall = true;
    XW_floor2[3][2].xwall = false;
    XW_floor2[3][3].xwall = true;
    XW_floor2[3][4].xwall = false;

    XW_floor2[4][0].xwall = false;
    XW_floor2[4][1].xwall = true;
    XW_floor2[4][2].xwall = false;
    XW_floor2[4][3].xwall = true;
    XW_floor2[4][4].xwall = false;

    XW_floor2[5][0].xwall = true;
    XW_floor2[5][1].xwall = true;
    XW_floor2[5][2].xwall = true;
    XW_floor2[5][3].xwall = true;
    XW_floor2[5][4].xwall = true;

    //Z-wall parameters
    ZW_floor2[0][0].zwall = true;
    ZW_floor2[0][1].zwall = false;
    ZW_floor2[0][2].zwall = false;
    ZW_floor2[0][3].zwall = false;
    ZW_floor2[0][4].zwall = false;
    ZW_floor2[0][5].zwall = true;

    ZW_floor2[1][0].zwall = true;
    ZW_floor2[1][1].zwall = true;
    ZW_floor2[1][2].zwall = true;
    ZW_floor2[1][3].zwall = true;
    ZW_floor2[1][4].zwall = true;
    ZW_floor2[1][5].zwall = true;

    ZW_floor2[2][0].zwall = true;
    ZW_floor2[2][1].zwall = false;
    ZW_floor2[2][2].zwall = false;
    ZW_floor2[2][3].zwall = false;
    ZW_floor2[2][4].zwall = false;
    ZW_floor2[2][5].zwall = true;

    ZW_floor2[3][0].zwall = true;
    ZW_floor2[3][1].zwall = true;
    ZW_floor2[3][2].zwall = true;
    ZW_floor2[3][3].zwall = true;
    ZW_floor2[3][4].zwall = true;
    ZW_floor2[3][5].zwall = true;

    ZW_floor2[4][0].zwall = true;
    ZW_floor2[4][1].zwall = false;
    ZW_floor2[4][2].zwall = false;
    ZW_floor2[4][3].zwall = false;
    ZW_floor2[4][4].zwall = false;
    ZW_floor2[4][5].zwall = true;

    //Roof parameters
    GR_floor2[0][0].roof = true;
    GR_floor2[0][1].roof = true;
    GR_floor2[0][2].roof = true;
    GR_floor2[0][3].roof = true;
    GR_floor2[0][4].roof = true;

    GR_floor2[1][0].roof = true;
    GR_floor2[1][1].roof = false;
    GR_floor2[1][2].roof = true;
    GR_floor2[1][3].roof = false;
    GR_floor2[1][4].roof = true;

    GR_floor2[2][0].roof = true;
    GR_floor2[2][1].roof = true;
    GR_floor2[2][2].roof = true;
    GR_floor2[2][3].roof = true;
    GR_floor2[2][4].roof = true;

    GR_floor2[3][0].roof = true;
    GR_floor2[3][1].roof = false;
    GR_floor2[3][2].roof = true;
    GR_floor2[3][3].roof = false;
    GR_floor2[3][4].roof = true;

    GR_floor2[4][0].roof = true;
    GR_floor2[4][1].roof = true;
    GR_floor2[4][2].roof = true;
    GR_floor2[4][3].roof = true;
    GR_floor2[4][4].roof = true;

    GR_floor = &GR_floor1;
    XW_floor = &XW_floor1;
    ZW_floor = &ZW_floor1;

    //Creating sizes for walls

    //Ground size
    float g_width = 8.0f;
    float g_height = 0.0f;
    float g_length = 8.0f;

    //X-wall size
    float xw_width = 0.0f;
    float xw_height = 5.0f;
    float xw_length = 8.0f;
    Vector3 xw_size = {xw_width, xw_height, xw_length};

    //Z-wall size
    float zw_width = 8.0f;
    float zw_height = 5.0f;
    float zw_length = 0.0f;
    Vector3 zw_size = {zw_width, zw_height, zw_length};

    //Roof size
    float rf_width = 8.0f;
    float rf_height = 0.0f;
    float rf_length = 8.0f;

    //Colors
    Color w_color = GRAY;
    Color g_color = GRAY;
    Color rf_color = GRAY;

    //Old cam position
    Vector3 oldcam_pos;

    Vector3 playerSize = { 1.0f, 2.0f, 1.0f };

    //General positions pointers
    Vector3 (*g_positions)[GR_MAX_X_1][GR_MAX_Z_1] = { 0 };
    Vector3 (*xw_positions)[XW_MAX_X_1][XW_MAX_Z_1] = { 0 };
    Vector3 (*zw_positions)[ZW_MAX_X_1][ZW_MAX_Z_1] = { 0 };
    Vector3 (*rf_positions)[GR_MAX_X_1][GR_MAX_Z_1] = { 0 };

    //Creating positions for walls on 1st floor
    Vector3 g_positions_1[GR_MAX_X_1][GR_MAX_Z_1] = { 0 };
    Vector3 xw_positions_1[XW_MAX_X_1][XW_MAX_Z_1] = { 0 };
    Vector3 zw_positions_1[ZW_MAX_X_1][ZW_MAX_Z_1] = { 0 };
    Vector3 rf_positions_1[GR_MAX_X_1][GR_MAX_Z_1] = { 0 };
    
    x = 0;
    z = 0;

    //Initializing ground tile positions for 1st floor
    while (z < GR_MAX_Z_1) {
        while (x < GR_MAX_X_1) {
            g_positions_1[x][z].x = 8*x;
            g_positions_1[x][z].y = 0;
            g_positions_1[x][z].z = 8*z;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing x-wall positions for 1st floor
    while (z < XW_MAX_Z_1) {
        while (x < XW_MAX_X_1) {
            xw_positions_1[x][z].x = -4+(8*x);
            xw_positions_1[x][z].y = 2.5;
            xw_positions_1[x][z].z = 8*z;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing z-wall positions for 1st floor
    while (z < ZW_MAX_Z_1) {
        while (x < ZW_MAX_X_1) {
            zw_positions_1[x][z].x = 0.0+(8*x);
            zw_positions_1[x][z].y = 2.5;
            zw_positions_1[x][z].z = -4.0+(8*z);
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing roof tile positions for 1st floor
    while (z < GR_MAX_Z_1) {
        while (x < GR_MAX_X_1) {
            rf_positions_1[x][z].x = 8*x;
            rf_positions_1[x][z].y = 5.0;
            rf_positions_1[x][z].z = 8*z;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    x = 0;

    g_positions = &g_positions_1;
    xw_positions = &xw_positions_1;
    zw_positions = &zw_positions_1;
    rf_positions = &rf_positions_1;

    //Creating positions for walls on 2st floor
    Vector3 g_positions_2[GR_MAX_X_2][GR_MAX_Z_2] = { 0 };
    Vector3 xw_positions_2[XW_MAX_X_2][XW_MAX_Z_2] = { 0 };
    Vector3 zw_positions_2[ZW_MAX_X_2][ZW_MAX_Z_2] = { 0 };
    Vector3 rf_positions_2[GR_MAX_X_2][GR_MAX_Z_2] = { 0 };
    
    x = 0;
    z = 0;

    //Initializing ground tile positions for 2st floor
    while (z < GR_MAX_Z_2) {
        while (x < GR_MAX_X_2) {
            g_positions_2[x][z].x = 8*x;
            g_positions_2[x][z].y = 0;
            g_positions_2[x][z].z = 8*z;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing x-wall positions for 2st floor
    while (z < XW_MAX_Z_2) {
        while (x < XW_MAX_X_2) {
            xw_positions_2[x][z].x = -4+(8*x);
            xw_positions_2[x][z].y = 2.5;
            xw_positions_2[x][z].z = 8*z;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing z-wall positions for 2st floor
    while (z < ZW_MAX_Z_2) {
        while (x < ZW_MAX_X_2) {
            zw_positions_2[x][z].x = 0.0+(8*x);
            zw_positions_2[x][z].y = 2.5;
            zw_positions_2[x][z].z = -4.0+(8*z);
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing roof tile positions for 2st floor
    while (z < GR_MAX_Z_2) {
        while (x < GR_MAX_X_2) {
            rf_positions_2[x][z].x = 8*x;
            rf_positions_2[x][z].y = 5.0;
            rf_positions_2[x][z].z = 8*z;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    x = 0;

    bool collision = false;

    int stepcounter = 0;

    int battlestatus = 0;

    int option = 0;

    int counter = 0;

    int access = 0;

    int interrupt = 0;

    int option_pressed = 0;

    int atk_seq = 0;

    int win = 0;

    int main_menu_exit = 0;

    int levelcpy; 

    int draw_menu = 0;

    int m_height = 150;

    int tip = 0;

    int chest_done1 = 0;

    int chest_open1 = 0;

    int shop_open = 0;

    int floortext_switch = 1;

    int sword_possession;

    int shield_possession;

    int teleporter_possession = 0;

    latest latest;

    latest.x = 32;
    latest.z = 32; 

    Vector3 zw_battleposition = {0, 2.5, 12};

    //Game loop
    while (!WindowShouldClose())
    {
        DrawFPS(0,0);

        //Title screen
        while (main_menu_exit != 1) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Dungeon Crawler", 250, 100, 60, WHITE);
            DrawText("Press ENTER", 400, 355, 30, WHITE);
            DrawText("Made by Oscar Eriksson, 2021", 355, 500, 20, WHITE);
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER)) {
                main_menu_exit = 1;
                camera.position = (Vector3){ 1.0f, 2.0f, 1.0f };
                I.inventory.potion = 2;
                I.stats.LV = 1;
                I.stats.MAX_HP = 10;
                I.stats.HP = 10;
                I.stats.ATK = 5;
                I.stats.DEF = 2;
                I.stats.Speed = 5;
                I.stats.EXP = 0;
                sprintf(item, ">Potion x%d", I.inventory.potion);
                sprintf(inventory_opt1, ">Potion x%d\n %s\n %s\n %s", I.inventory.potion, underscore, underscore, underscore);
                GR_floor = &GR_floor1;
                XW_floor = &XW_floor1;
                ZW_floor = &ZW_floor1;
                sprintf(floor, "FL1");
            }
        }

        if (camera.position.x != oldcam_pos.x || camera.position.z != oldcam_pos.z) {
            stepcounter++;
            //printf("Stepcounter: %d\n", stepcounter);
        }

        //printf("x: %f, y: %f. z: %f\n", camera.position.x, camera.position.y, camera.position.z);

        //Battle sequence
        if (stepcounter > random) {
            SetCameraMode(camera, CAMERA_PERSPECTIVE);  
            camera.fovy = 45.0f;
            camera.up.y = 2.0f;
            camera.target.x = 0.0f;
            camera.target.z = 0.5f;
            camera.target.y = 1.5f;
            camera.position.x = 0.0f;
            camera.position.z = 0.0f;
            camera.position.y = 1.5f;

            levelcpy = I.stats.LV;

            text = monstertext;

            if (random > 1500) {
                aptr = &Slime;
                imgptr = &slime_png;
            }
            else {
                aptr = &Bat;
                imgptr = &bat_png;
            }
            
            battlestatus = 1;
            while (interrupt != 1) {

                switch (Battle)
                {
                    case INTRO: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = OPT1;
                        }
                    } break;
                    case OPT1: {
                        done = 0;
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ATK_SEQ1;                            
                        }
                        else if (IsKeyPressed(KEY_LEFT)) {
                            Battle = OPT4;
                        }
                        else if (IsKeyPressed(KEY_RIGHT)) {
                            Battle = OPT2;
                        }
                    } break;
                    case OPT2: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = DEF_SEQ1;
                        }
                        else if (IsKeyPressed(KEY_LEFT)) {
                            Battle = OPT1;
                        }
                        else if (IsKeyPressed(KEY_RIGHT)) {
                            Battle = OPT3;
                        }
                    } break;
                    case OPT3: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ITEM_OPT1;
                        }
                        else if (IsKeyPressed(KEY_LEFT)) {
                            Battle = OPT2;
                        }
                        else if (IsKeyPressed(KEY_RIGHT)) {
                            Battle = OPT4;
                        }
                    } break;
                    case OPT4: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = FLEE;
                        }
                        else if (IsKeyPressed(KEY_LEFT)) {
                            Battle = OPT3;
                        }
                        else if (IsKeyPressed(KEY_RIGHT)) {
                            Battle = OPT1;
                        }
                    } break;
                    case ATK_SEQ1: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ATK_SEQ2;
                        }
                    } break;
                    case ATK_SEQ2: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ATK_SEQ3;
                        }
                    } break;
                    case ATK_SEQ3: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ATK_SEQ4;
                        }
                    } break;
                    case ATK_SEQ4: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = OPT1;
                        }
                    } break;
                    case DEF_SEQ1: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = DEF_SEQ2;
                        }
                    } break;
                    case DEF_SEQ2: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = DEF_SEQ3;
                        }
                    } break;
                    case DEF_SEQ3: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = OPT1;
                        }
                    } break;
                    case ITEM_OPT1: {
                        if (I.inventory.potion != 0) {
                            if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ITEM_SEQ1;
                            }
                        }                       
                        if (IsKeyPressed(KEY_ENTER) && I.inventory.potion == 0) {
                            Battle = ITEM_ERR;
                        }                                                  
                        if (IsKeyPressed(KEY_BACKSPACE)) {
                            Battle = OPT3;
                        }                   
                    } break;
                    case ITEM_SEQ1: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            done = 0;
                            Battle = ITEM_SEQ2;
                        }
                    } break;
                    case ITEM_SEQ2: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ITEM_SEQ3;
                        }
                    } break;
                    case ITEM_SEQ3: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ITEM_SEQ4;
                        }
                    } break;
                    case ITEM_SEQ4: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            done = 0;
                            Battle = OPT3;
                        }
                    } break;
                    case ITEM_ERR: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = ITEM_OPT1;
                        }
                    } break;
                    case FLEE: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            if (Slime.stats.LV > I.stats.LV) {
                                Battle = FLEE_F;
                            }
                            else {
                                Battle = FLEE_S;
                            }
                        }
                    } break;
                    case FLEE_S: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            interrupt = 1;
                        }
                    } break;
                    case FLEE_F: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            interrupt = 1;
                        }
                    } break;
                    case VICTORY: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = EXP;
                        }
                    } break;
                    case EXP: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = COINS;
                            done = 0;
                        } 
                    } break;                       
                    case COINS: {
                        if (levelcpy < I.stats.LV) {
                            if (IsKeyPressed(KEY_ENTER)) {
                                Battle = LVL_UP;
                            }
                        }
                        else {
                            if (IsKeyPressed(KEY_ENTER)) {
                            interrupt = 1;
                            }
                        }
                    } break;
                    case LVL_UP: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            interrupt = 1;
                        }
                    } break;
                    case DEAD: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            Battle = GAME_OVER;
                        }
                    } break;
                    case GAME_OVER: {
                        if (IsKeyPressed(KEY_ENTER)) {
                            interrupt = 1;
                            main_menu_exit = 0;
                            I.stats.HP = 10;
                            I.stats.EXP = 0;
                        }
                    } break;
                }

                UpdateCamera(&camera);

                BeginDrawing();

                    ClearBackground(BLACK);

                    BeginMode3D(camera);
                       
                        DrawCubeTexture(g_texture, (Vector3){0, 0, 0}, g_width, g_height, g_length, g_color);
                        DrawCubeWires((Vector3){0, 0, 0}, 8.0f, 0.0f, 8.0f, BLACK);
                        DrawCubeTexture(g_texture, (Vector3){0, 0, 8}, g_width, g_height, g_length, g_color);
                        DrawCubeWires((Vector3){0, 0, 8}, 8.0f, 0.0f, 8.0f, BLACK);
                        
                        DrawCubeTexture(w_texture, (Vector3){4, 2.5, 0}, xw_width, xw_height, xw_length, w_color); 
                        DrawCubeWires((Vector3){4, 2.5, 0}, 0.0f, 5.0f, 8.0f, BLACK); 
                        DrawCubeTexture(w_texture, (Vector3){-4, 2.5, 0}, xw_width, xw_height, xw_length, w_color); 
                        DrawCubeWires((Vector3){-4, 2.5, 0}, 0.0f, 5.0f, 8.0f, BLACK); 
                        DrawCubeTexture(w_texture, (Vector3){4, 2.5, 8}, xw_width, xw_height, xw_length, w_color); 
                        DrawCubeWires((Vector3){4, 2.5, 8}, 0.0f, 5.0f, 8.0f, BLACK); 
                        DrawCubeTexture(w_texture, (Vector3){-4, 2.5, 8}, xw_width, xw_height, xw_length, w_color); 
                        DrawCubeWires((Vector3){-4, 2.5, 8}, 0.0f, 5.0f, 8.0f, BLACK); 
                        
                        DrawCubeTexture(w_texture, zw_battleposition, zw_width, zw_height, zw_length, w_color);
                        DrawCubeWires(zw_battleposition, 8.0f, 5.0f, 0.0f, BLACK);
                        
                        DrawCubeTexture(rf_texture, (Vector3){0, 5, 0}, rf_width, rf_height, rf_length, rf_color);
                        DrawCubeWires((Vector3){0, 0, 0}, 8.0f, 0.0f, 8.0f, BLACK);
                        DrawCubeTexture(rf_texture, (Vector3){0, 5, 8}, rf_width, rf_height, rf_length, rf_color);
                        DrawCubeWires((Vector3){0, 0, 8}, 8.0f, 0.0f, 8.0f, BLACK);

                    EndMode3D();

                    if (win != 1) {
                        DrawTexture((*imgptr), 250, 30, WHITE);
                    }  

                    DrawRectangle(10, 470, 1000, 100, BLACK);

                    switch (Battle)
                    {
                        case INTRO: {
                            text = monstertext;
                        } break;
                        case OPT1: {
                            text = battlemenu1;
                        } break;
                        case OPT2: {
                            text = battlemenu2;
                        } break;
                        case OPT3: {
                            text = battlemenu3;
                        } break;
                        case OPT4: {
                            text = battlemenu4;
                        } break;
                        case ATK_SEQ1: {
                            if (aptr->stats.Speed > I.stats.Speed) {
                                text = monster_attack;
                                done = 0;
                            }
                            else {
                                text = I_attack;
                                done = 0;
                            }
                        } break;
                        case ATK_SEQ2: {
                            if (aptr->stats.Speed > I.stats.Speed) {
                                if (done != 1) {
                                    I.stats.HP = I.stats.HP - aptr->stats.ATK;
                                    sprintf(I_HP_lose, "You lose %d HP", Slime.stats.ATK);
                                    text = I_HP_lose;   
                                    if (I.stats.HP <= 0) {
                                        if (done != 1) {
                                            Battle = DEAD;
                                            done = 1;
                                            }
                                    }
                                    done = 1;                                  
                                }                                                               
                            }
                            else {
                                if (done != 1)
                                aptr->stats.HP = aptr->stats.HP - I.stats.ATK;
                                sprintf(monster_HP_lose, "The monster loses %d HP", aptr->stats.ATK);
                                text = monster_HP_lose;
                                if (aptr->stats.HP <= 0) {
                                    Battle = VICTORY;
                                    win = 1;
                                }
                                done = 1;                               
                            }
                        } break;
                        case ATK_SEQ3: {
                            if (aptr->stats.Speed > I.stats.Speed) {
                                text = I_attack;
                                done = 0;
                            }
                            else {
                                text = monster_attack;
                                done = 0;
                            }
                        } break;
                        case ATK_SEQ4: {
                            if (aptr->stats.Speed > I.stats.Speed) {
                                if (done != 1) {
                                aptr->stats.HP = (aptr->stats.HP - I.stats.ATK);
                                sprintf(monster_HP_lose, "The monster loses %d HP", aptr->stats.ATK);
                                text = monster_HP_lose;
                                    if (aptr->stats.HP <= 0) {
                                        Battle = VICTORY;
                                        win = 1;
                                    }                                   
                                    done = 1;
                                    }
                            }
                            else {
                                if (done != 1) {
                                    I.stats.HP = (I.stats.HP - aptr->stats.ATK);
                                    sprintf(I_HP_lose, "You lose %d HP", aptr->stats.ATK);
                                    text = I_HP_lose;
                                    if (I.stats.HP <= 0) {
                                        if (done != 1) {
                                            Battle = DEAD;
                                            done = 1;
                                        }
                                    }
                                    done = 1;
                                }                               
                            }
                        } break;
                        case DEF_SEQ1: {
                            text = I_defend;
                        } break;
                        case DEF_SEQ2: {
                            text = monster_attack;
                        } break;
                        case DEF_SEQ3: {
                            text = I_HP_lose;
                            if (done != 1) {
                                I.stats.HP = I.stats.HP - (aptr->stats.ATK - I.stats.DEF);
                                sprintf(I_HP_lose, "You lose %d HP", (aptr->stats.ATK - I.stats.DEF));
                                if (I.stats.HP <= 0) {
                                    Battle = DEAD;
                                    done = 1;
                                }
                                done = 1;
                            }
                        } break;
                        case ITEM_OPT1: {
                            text = item;
                        } break;
                        case ITEM_SEQ1: {                            
                            text = use_item;
                            if (done != 1) {
                                I.inventory.potion = I.inventory.potion - 1;
                                sprintf(item, ">Potion x%d", I.inventory.potion);
                                sprintf(inventory_opt1, ">Potion x%d\n %s\n %s\n %s", I.inventory.potion, underscore, underscore, underscore);
                                done = 1;
                            }                           
                        } break;
                        case ITEM_SEQ2: {
                            text = I_HP_gain;
                            if (done != 1) {
                                HPcpy = I.stats.HP;
                                HPcounter = 0;
                                while (I.stats.HP < (HPcpy+10) && I.stats.HP < I.stats.MAX_HP) {
                                    I.stats.HP = I.stats.HP + 1;         
                                    HPcounter++;                           
                                }
                                sprintf(I_HP_gain, "You gain %d HP", HPcounter);
                                done = 1;
                            }
                        } break;
                        case ITEM_SEQ3: {
                            text = monster_attack;    
                            done = 0;                       
                        } break;
                        case ITEM_SEQ4: {                            
                            if (done != 1) {
                                I.stats.HP = I.stats.HP - aptr->stats.ATK;
                                sprintf(I_HP_lose, "You lose %d HP", aptr->stats.ATK);
                                text = I_HP_lose;
                                done = 1;
                            }                           
                        } break;
                        case ITEM_ERR: {
                            text = item_err;
                        } break;
                        case FLEE: {
                            text = flee1;
                        } break;
                        case FLEE_F: {
                            text = flee_f;
                        } break;
                        case FLEE_S: {
                            text = flee_s;
                        } break;
                        case VICTORY: {
                            text = defeat;
                            done = 0;
                        } break;
                        case EXP: {
                            text = EXP_gain;
                            if (done != 1) {
                                I.stats.EXP = I.stats.EXP + aptr->stats.EXP;
                                if (I.stats.EXP >= pow(2, I.stats.LV)*50) {
                                    I.stats.LV = I.stats.LV + 1;                                    
                                    I.stats.MAX_HP = I.stats.MAX_HP + 1;
                                    I.stats.ATK = I.stats.ATK + 1;
                                    I.stats.DEF = I.stats.DEF + 1;
                                    I.stats.Speed = I.stats.Speed + 1;
                                }
                                done = 1;
                            }
                        } break;
                        case COINS: {
                            text = gold;
                            if (done != 1) {
                                I.stats.gold = I.stats.gold + aptr->stats.gold;
                                done = 1;
                            }
                        } break;
                        case LVL_UP: {
                            text = level_up;
                        } break;
                        case DEAD: {
                            text = dead;
                        } break;
                        case GAME_OVER: {
                            text = game_over;
                        } break;
                    }

                    //printf("lvlcpy: %d, level: %d\n", levelcpy, I.stats.LV);

                    if (I.stats.HP <= 0) {
                        sprintf(HP,"%d", 0);
                    }
                    else {
                        sprintf(HP,"%d", I.stats.HP);
                    }
                    
                    strcpy(HPtext, "HP:");
                    strcat(HPtext, HP);

                    if (aptr->stats.HP <= 0) {
                        sprintf(mHP,"%d", 0);
                    }
                    else {
                        sprintf(mHP,"%d", aptr->stats.HP);
                    }

                    strcpy(mHPtext, "HP:");
                    strcat(mHPtext, mHP);

                    /*sprintf(I_HP_gain, "You gain %d HP", 10);
                    sprintf(I_HP_lose, "You lose %d HP", Slime.stats.ATK);
                    sprintf(monster_HP_lose, "The monster loses %d HP", Slime.stats.ATK);
                    */

                    sprintf(EXP_gain, "You gain %d EXP", aptr->stats.EXP);       

                    sprintf(gold, "You get %d gold", aptr->stats.gold);

                    sprintf(goldtext, "My gold: %d G", I.stats.gold);

                    DrawText(text, 300, 500, 40, WHITE);
                    DrawText(HPptr, 100, 500, 40, WHITE);
                    DrawText(mHPptr, 250, 100, 40, WHITE);

                EndDrawing();
            }
            stepcounter = 0;
            battlestatus = 0;
            option = 0;
            counter = 0;
            access = 0;
            interrupt = 0;
            exit = 1;
            
            nxtlvlEXP = pow(2,I.stats.LV)*50;
            sprintf(stats, "LV:%d\nHP:%d/%d\nATK:%d\nDEF:%d\nSpeed:%d\nEXP:%d/%d -> LV:%d\nGold:%d\n", I.stats.LV, I.stats.HP, I.stats.MAX_HP, I.stats.ATK, I.stats.DEF, I.stats.Speed, I.stats.EXP, nxtlvlEXP, I.stats.LV+1, I.stats.gold);

            srand(time(NULL));
            rand();
            random = M2 + rand() / (RAND_MAX / (N2 - M2 + 1) + 1);

            camera.position = oldcam_pos;
            camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
            camera.fovy = 60.0f;
            camera.projection = CAMERA_PERSPECTIVE;
            SetCameraMode(camera, CAMERA_FIRST_PERSON); 

            if (aptr == &Slime) {
                aptr->stats.HP = 10;
            }
            else if (aptr == &Bat) {
                aptr->stats.HP = 7;
            }
        
            win = 0;

            Battle = INTRO;
        }

        oldcam_pos = camera.position;

        //Menu navigation
            switch (menu) {
                case START: {
                    if (IsKeyPressed(KEY_ENTER)) {
                        menu = M_OPT1;
                    }
                } break;
                case M_OPT1: {
                    if (IsKeyPressed(KEY_ENTER)) {
                        menu = STATS;
                    }
                    if (IsKeyPressed(KEY_RIGHT)) {
                        menu = M_OPT2;
                    }
                } break;
                case M_OPT2: {
                    if (IsKeyPressed(KEY_ENTER)) {
                        menu = ITEMS1;
                        done = 0;
                    }
                    if (IsKeyPressed(KEY_LEFT)) {
                        menu = OPT1;
                    }
                } break;
                case STATS: {
                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        menu = M_OPT1;
                    }
                } break;
                case ITEMS1: {
                    if (IsKeyPressed(KEY_ENTER) && draw_menu == 1) {
                        if (done != 1 && I.inventory.potion != 0) {
                            HPcpy = I.stats.HP;
                            HPcounter = 0;
                            while (I.stats.HP < (HPcpy+10) && I.stats.HP < I.stats.MAX_HP) {
                                I.stats.HP = I.stats.HP + 1;         
                                HPcounter++;  
                            }
                            I.inventory.potion = I.inventory.potion - 1;
                            if (teleporter_possession > 0) {
                                    sprintf(inventory_opt1, ">Potion x%d\n Teleporter\n _\n _", I.inventory.potion);
                                    sprintf(inventory_opt2, " Potion x%d\n>Teleporter\n _ \n _", I.inventory.potion);        
                                    sprintf(inventory_opt3, " Potion x%d\n Teleporter\n>_\n _", I.inventory.potion);
                                    sprintf(inventory_opt4, " Potion x%d\n Teleporter\n _ \n>_", I.inventory.potion);  
                            }  
                            else {
                                sprintf(inventory_opt1, ">Potion x%d\n %s\n %s\n %s", I.inventory.potion, underscore, underscore, underscore);
                                sprintf(inventory_opt2, " Potion x%d\n>%s\n %s\n %s", I.inventory.potion, underscore, underscore, underscore);
                                sprintf(inventory_opt3, " Potion x%d\n %s\n>%s\n %s", I.inventory.potion, underscore, underscore, underscore);
                                sprintf(inventory_opt4, " Potion x%d\n %s\n %s\n>%s", I.inventory.potion, underscore, underscore, underscore);
                            }
                            sprintf(item, ">Potion x%d", I.inventory.potion);
                            sprintf(stats, "LV:%d\nHP:%d/%d\nATK:%d\nDEF:%d\nSpeed:%d\nEXP:%d/%d -> LV:%d\nGold:%d\n", I.stats.LV, I.stats.HP, I.stats.MAX_HP, I.stats.ATK, I.stats.DEF, I.stats.Speed, I.stats.EXP, nxtlvlEXP, I.stats.LV+1, I.stats.gold);
                            done = 1;                    
                        }
                    }
                    else if (IsKeyPressed(KEY_UP)) {
                        menu = ITEMS4;
                    }
                    else if (IsKeyPressed(KEY_DOWN)) {
                        menu = ITEMS2;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE)) {
                        menu = M_OPT2;
                    }
                } break;
                case ITEMS2: {
                    if (IsKeyPressed(KEY_ENTER) && fcounter == 2) {
                        camera.position.x = latest.x;
                        camera.position.y = 0;
                        camera.position.z = latest.z;                          
                    }
                    else if (IsKeyPressed(KEY_UP)) {
                        menu = ITEMS1;
                    }
                    else if (IsKeyPressed(KEY_DOWN)) {
                        menu = ITEMS3;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE)) {
                        menu = M_OPT2;
                    }
                } break;
                case ITEMS3: {
                    if (IsKeyPressed(KEY_ENTER)) {
                                         
                    }
                    else if (IsKeyPressed(KEY_UP)) {
                        menu = ITEMS2;
                    }
                    else if (IsKeyPressed(KEY_DOWN)) {
                        menu = ITEMS4;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE)) {
                        menu = M_OPT2;
                    }
                } break;
                case ITEMS4: {
                    if (IsKeyPressed(KEY_ENTER)) {
                                 
                    }
                    else if (IsKeyPressed(KEY_UP)) {
                        menu = ITEMS3;
                    }
                    else if (IsKeyPressed(KEY_DOWN)) {
                        menu = ITEMS1;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE)) {
                        menu = M_OPT2;
                    }
                } break;
            }

            //Chest navigation
            switch (chest1) {
                case INITIAL: {
                    if (IsKeyPressed(KEY_ENTER)) {
                        chest1 = GOT;
                    }
                } break;
                case GOT: {
                    if (chest_open1 == 1) {
                        chesttext = got_tele;
                        teleporter_possession = 1;
                        sprintf(inventory_opt1, ">Potion x%d\n Teleporter\n _\n _", I.inventory.potion);
                        sprintf(inventory_opt2, " Potion x%d\n>Teleporter\n _ \n _", I.inventory.potion);        
                        sprintf(inventory_opt3, " Potion x%d\n Teleporter\n>_\n _", I.inventory.potion);
                        sprintf(inventory_opt4, " Potion x%d\n Teleporter\n _ \n>_", I.inventory.potion);           
                        if (IsKeyPressed(KEY_ENTER)) {
                            chest1 = DESC;
                        }
                    }  
                } break;
                case DESC: {
                    chesttext = desc_tele;
                    if (IsKeyPressed(KEY_ENTER) && chest_open1 == 1) {
                        chest_open1 = 0;
                        chest_done1 = 1;
                        camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
                        SetCameraMode(camera, CAMERA_FIRST_PERSON);
                    }  
                } break;
            }

            //Shop navigation
            switch (shop_nav) {
                case ITEM1: {
                    if (IsKeyPressed(KEY_ENTER) && shop_open == 1) {    
                        done = 0;                   
                        if (I.stats.gold >= sword_cost) {
                            shop_q_text = thanks;
                            if (done != 1) {
                                I.stats.gold = I.stats.gold - sword_cost;
                                sprintf(goldtext, "My gold: %d G", I.stats.gold);
                                sword_possession = 1;
                                if (shield_possession > 0) {
                                    sprintf(inventory_opt1, ">Potion x%d\n Sword\nShield");
                                }
                                done = 1;
                            }
                        }
                        else {
                            shop_q_text = cant_afford;
                        }
                    }
                    else if (IsKeyPressed(KEY_RIGHT)) {
                        shop_q_text = question;
                        shop_nav = ITEM2;
                    }
                    else if (IsKeyPressed(KEY_LEFT)) {
                        shop_q_text = question;
                        shop_nav = ITEM3;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE) && shop_open == 1) {
                        shop_open = 0;
                        camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
                        SetCameraMode(camera, CAMERA_FIRST_PERSON);
                    }  
                } break;
                case ITEM2: {
                    if (IsKeyPressed(KEY_ENTER) && shop_open == 1) {
                        done = 0;
                        if (I.stats.gold >= shield_cost) {
                            shop_q_text = thanks;
                            if (done != 1) {
                                I.stats.gold = I.stats.gold - shield_cost;
                                sprintf(goldtext, "My gold: %d G", I.stats.gold);
                                done = 1;
                            }
                        }
                        else {
                            shop_q_text = cant_afford;
                        }
                    }
                    else if (IsKeyPressed(KEY_RIGHT)) {
                        shop_q_text = question;
                        shop_nav = ITEM3;
                    }
                    else if (IsKeyPressed(KEY_LEFT)) {
                        shop_q_text = question;
                        shop_nav = ITEM1;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE) && shop_open == 1) {
                        shop_open = 0;
                        camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
                        SetCameraMode(camera, CAMERA_FIRST_PERSON);
                    }  
                } break;
                case ITEM3: {
                    if (IsKeyPressed(KEY_ENTER) && shop_open == 1) {
                        done = 0;
                        if (I.stats.gold >= potion_cost) {
                            shop_q_text = thanks;
                            if (done != 1) {
                                I.stats.gold = (I.stats.gold - potion_cost);
                                I.inventory.potion++;                  
                                if (teleporter_possession > 0) {
                                    sprintf(inventory_opt1, ">Potion x%d\n Teleporter\n _\n _", I.inventory.potion);
                                    sprintf(inventory_opt2, " Potion x%d\n>Teleporter\n _ \n _", I.inventory.potion);        
                                    sprintf(inventory_opt3, " Potion x%d\n Teleporter\n>_\n _", I.inventory.potion);
                                    sprintf(inventory_opt4, " Potion x%d\n Teleporter\n _ \n>_", I.inventory.potion);  
                                }  
                                else {
                                    sprintf(inventory_opt1, ">Potion x%d\n %s\n %s\n %s", I.inventory.potion, underscore, underscore, underscore);
                                    sprintf(inventory_opt2, " Potion x%d\n>%s\n %s\n %s", I.inventory.potion, underscore, underscore, underscore);
                                    sprintf(inventory_opt3, " Potion x%d\n %s\n>%s\n %s", I.inventory.potion, underscore, underscore, underscore);
                                    sprintf(inventory_opt4, " Potion x%d\n %s\n %s\n>%s", I.inventory.potion, underscore, underscore, underscore);
                                }
                                sprintf(item, ">Potion x%d", I.inventory.potion); 
                                sprintf(stats, "LV:%d\nHP:%d/%d\nATK:%d\nDEF:%d\nSpeed:%d\nEXP:%d/%d -> LV:%d\nGold:%d\n", I.stats.LV, I.stats.HP, I.stats.MAX_HP, I.stats.ATK, I.stats.DEF, I.stats.Speed, I.stats.EXP, nxtlvlEXP, I.stats.LV+1, I.stats.gold);
                                sprintf(goldtext, "My gold: %d G", I.stats.gold);
                                done = 1;
                            }
                        }
                        else {
                            shop_q_text = cant_afford;
                        }
                    }
                    else if (IsKeyPressed(KEY_RIGHT)) {
                        shop_q_text = question;
                        shop_nav = ITEM1;
                    }
                    else if (IsKeyPressed(KEY_LEFT)) {
                        shop_q_text = question;
                        shop_nav = ITEM2;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE)  && shop_open == 1) {
                        done = 0;
                        shop_open = 0;
                        floortext_switch = 1;
                        camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
                        SetCameraMode(camera, CAMERA_FIRST_PERSON);
                    }  
                } break;                
            }
            
        UpdateCamera(&camera);  

        if (camera.position.x > 32 && camera.position.z > 32) {
            GR_floor = &GR_floor2;
            XW_floor = &XW_floor2;
            ZW_floor = &ZW_floor2;
            fcounter = 2;
            sprintf(floor, "FL2");
        }
        
        collision = false;

        x = 0;
        z = 0;

        //Check collisions player vs x-wall
        while (z < XW_MAX_Z_1) {
            while (x < XW_MAX_X_1) {
                if (CheckCollisionBoxes(
                    (BoundingBox){(Vector3){ camera.position.x - playerSize.x/2, 
                                             camera.position.y - playerSize.y/2, 
                                             camera.position.z - playerSize.z/2 },
                                  (Vector3){ camera.position.x + playerSize.x/2, 
                                             camera.position.y + playerSize.y/2, 
                                             camera.position.z + playerSize.z/2 }},
                    (BoundingBox){(Vector3){ xw_positions_1[x][z].x - xw_size.x/2, 
                                             xw_positions_1[x][z].y - xw_size.y/2, 
                                             xw_positions_1[x][z].z - xw_size.z/2 },
                                  (Vector3){ xw_positions_1[x][z].x + xw_size.x/2, 
                                             xw_positions_1[x][z].y + xw_size.y/2, 
                                             xw_positions_1[x][z].z + xw_size.z/2 }})) {
                                                 if ((*XW_floor)[x][z].xwall == true) {
                                                     collision = true;
                                                 }
                                                }
                                
                x++;
            }
            x = 0;
            z++;
        }

        x = 0;
        z = 0;

        // Check collisions player vs z-wall
        while (z < ZW_MAX_Z_1) {
            while (x < ZW_MAX_X_1) {
                if (CheckCollisionBoxes(
                    (BoundingBox){(Vector3){ camera.position.x - playerSize.x/2, 
                                             camera.position.y - playerSize.y/2, 
                                             camera.position.z - playerSize.z/2 },
                                  (Vector3){ camera.position.x + playerSize.x/2, 
                                             camera.position.y + playerSize.y/2, 
                                             camera.position.z + playerSize.z/2 }},
                    (BoundingBox){(Vector3){ (*zw_positions)[x][z].x - zw_size.x/2, 
                                             (*zw_positions)[x][z].y - zw_size.y/2, 
                                             (*zw_positions)[x][z].z - zw_size.z/2 },
                                  (Vector3){ (*zw_positions)[x][z].x + zw_size.x/2, 
                                             (*zw_positions)[x][z].y + zw_size.y/2, 
                                             (*zw_positions)[x][z].z + zw_size.z/2 }})) {
                                                 if ((*ZW_floor)[x][z].zwall == true) {
                                                     collision = true;
                                                 }
                                                }

                x++;
            }
            x = 0;
            z++;
        }

        x = 0;
        z = 0;                     

        if (collision) {
            camera.position = oldcam_pos;
        }
        
        BeginDrawing();

            ClearBackground(BLACK);            

            //XYZ | width, height, length

            BeginMode3D(camera);

                //Floor
                x = 0;
                z = 0;
                while (z < GR_MAX_Z_1) {
                    while (x < GR_MAX_X_1) {
                        //printf("floor1[%d][%d].ground = %d\n", i, j, floor1[i][j].ground);
                        if ((*GR_floor)[x][z].ground == true) {
                            DrawCubeTexture(g_texture, (*g_positions)[x][z], g_width, g_height, g_length, g_color);
                            DrawCubeWires((*g_positions)[x][z], 8.0f, 0.0f, 8.0f, BLACK);
                        }
                        x++;
                    }
                    x = 0;
                    z++;
                }
                
                //X-wall
                x = 0;
                z = 0;
                while (z < XW_MAX_Z_1) {
                    while (x < XW_MAX_X_1) {
                        if ((*XW_floor)[x][z].xwall == true) {
                            DrawCubeTexture(w_texture, (*xw_positions)[x][z], xw_width, xw_height, xw_length, w_color); 
                            DrawCubeWires((*xw_positions)[x][z], 0.0f, 5.0f, 8.0f, BLACK); 
                        }
                        x++;
                    }
                    x = 0;
                    z++;
                }

                //Z-wall
                x = 0;
                z = 0;
                while (z < (ZW_MAX_Z_1)) {
                    while (x < ZW_MAX_X_1) {
                        if ((*ZW_floor)[x][z].zwall == true) {
                            DrawCubeTexture(w_texture, (*zw_positions)[x][z], zw_width, zw_height, zw_length, w_color);
                            DrawCubeWires((*zw_positions)[x][z], 8.0f, 5.0f, 0.0f, BLACK);
                        }
                        x++;
                    }
                    x = 0;
                    z++;
                }

                //Roof
                x = 0;
                z = 0;
                while (z < GR_MAX_Z_1) {
                    while (x < GR_MAX_X_1) {
                        if ((*GR_floor)[x][z].roof == true) {
                            DrawCubeTexture(rf_texture, (*rf_positions)[x][z], rf_width, rf_height, rf_length, rf_color);
                            DrawCubeWires((*rf_positions)[x][z], 8.0f, 0.0f, 8.0f, BLACK);
                        }
                        x++;
                    }
                    x = 0;
                    z++;

                    if (fcounter == 1) {
                        DrawCubeTexture(ladder, (*zw_positions)[4][5], zw_width, zw_height, zw_length, w_color); 
                        DrawCubeTexture(hole, (*g_positions)[4][4], g_width, g_height, g_length, g_color);
                    }   
                }

                if (fcounter == 2) {
                    DrawModel((*chestptr), chest_pos, 0.25f, WHITE);
                    DrawModelEx(shop, shop_pos, (Vector3){ 0, 100, 0}, 180, (Vector3){0.3f, 0.3f, 0.3f}, WHITE);
                }        

            EndMode3D(); 

            switch (menu) {
                case M_OPT1: {
                    menutext = menu_opt1;
                    m_height = 150;
                } break;
                case M_OPT2: {
                    menutext = menu_opt2;
                    m_height = 150;
                } break;
                case STATS: {
                    menutext = stats;
                    m_height = 340;
                } break;
                case ITEMS1: {
                    menutext = inventory_opt1;
                    m_height = 220;
                } break;
                case ITEMS2: {
                    menutext = inventory_opt2;
                } break;
                case ITEMS3: {
                    menutext = inventory_opt3;
                } break;
                case ITEMS4: {
                    menutext = inventory_opt4;
                } break;
            }

            switch (shop_nav) {
                case ITEM1: {
                    shop_item_text = shop_sword;             
                } break;
                case ITEM2: {
                    shop_item_text = shop_shield;
                } break;
                case ITEM3: {
                    shop_item_text = shop_potion;
                } break;                
            }

            if (tip != 1) {
                DrawText(tip_ptr, 700, 0, 20, WHITE);
            }

            if (IsKeyPressed(KEY_SPACE)) {
                tip = 1;
                if (draw_menu == 0) {
                    draw_menu = 1;
                }
                else {
                    draw_menu = 0;
                }
            }

            if (camera.position.x > 1 && camera.position.x < 2 && camera.position.z > 11 && camera.position.z < 12 && fcounter == 2 && chest_done1 != 1) {
                chest_open1 = 1;    
                chestptr = &openchest;
                SetCameraMode(camera, CAMERA_PERSPECTIVE);
            }

            if (camera.position.x > 0 && camera.position.x < 1 && camera.position.z > 31 && camera.position.z < 32 && fcounter == 2) {
                shop_open = 1;    
                floortext_switch = 0;
                SetCameraMode(camera, CAMERA_PERSPECTIVE);
            }

            if (chest_open1 == 1) {
                DrawRectangle(250, 100, 500, 250, BLACK);
                DrawText(chesttext, 290, 190, 30, WHITE); 
                camera.position = oldcam_pos;            
            }

            if (shop_open == 1) {
                DrawRectangle(20, 30, 1000, 500, BLACK);
                DrawText(shop_item_text, 160, 300, 40, WHITE);
                DrawText(shop_q_text, 150, 450, 40, WHITE);   
                DrawText(goldtext, 50, 50, 40, WHITE);
                camera.position = oldcam_pos;          
            }

            if (draw_menu == 1) {
                DrawRectangle(690, 0, 410, m_height, BLACK);
                DrawText(menutext, 710, 20, 30, WHITE);
            }
            
            if (floortext_switch == 1) {
                DrawRectangle(0, 0, 95, 50, BLACK);
                DrawText(floortext, 0, 0, 50, WHITE);                
            }         

        EndDrawing();
    }

    CloseWindow();

    return 0;
}