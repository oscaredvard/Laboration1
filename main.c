#include "include/raylib.h"
#include <stdio.h>
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
    const int screenWidth = 1024;
    const int screenHeight = 576;

    InitWindow(screenWidth, screenHeight, "Dungeon Crawler");

    Camera camera = { 0 };
    camera.position = (Vector3){ 1.0f, 2.0f, 1.0f };
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Texture2D w_texture = LoadTexture("stonewall.png");
    Texture2D g_texture = LoadTexture("stonefloor.png");
    Texture2D rf_texture = LoadTexture("stonewall.png");

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

    //Game loop
    while (!WindowShouldClose())
    {
        DrawFPS(0,0);

        //printf("x: %f, t: %f, z: %f\n", camera.position.x, camera.position.y, camera.position.z);

        oldcam_pos = camera.position;

        UpdateCamera(&camera);  

        if (camera.position.x > 29 && camera.position.z > 29) {
            GR_floor = &GR_floor2;
            XW_floor = &XW_floor2;
            ZW_floor = &ZW_floor2;
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

        //printf("Current position: x: %f, y: %f, z: %f\n", camera.position.x, camera.position.y, camera.position.z);

        if (collision) {
            camera.position = oldcam_pos;
        }

        //printf("Collision: %d\n", collision);

        //Update floor in case
        /*if (camera.position.x == 32 && camera.position.z == 32) {
            GR_floor = &GR_floor2;
            XW_floor = &XW_floor2;
            ZW_floor = &ZW_floor2; 
        }*/
        
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
                }

            EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}