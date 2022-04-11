#include "include/raylib.h"
#include <stdio.h>
#include "game.h"

#define GR_MAX_X 5
#define GR_MAX_Z 5
#define XW_MAX_X (GR_MAX_X+1)
#define XW_MAX_Z GR_MAX_X
#define ZW_MAX_X GR_MAX_X
#define ZW_MAX_Z (GR_MAX_X+1)

//gcc main.c -o game.exe -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

int main() 
{
    const int screenWidth = 1024;
    const int screenHeight = 576;

    InitWindow(screenWidth, screenHeight, "Dungeon Crawler");

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 4.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    SetTargetFPS(144);

    //Creating 1st floor

    GR GR_floor1[GR_MAX_X][GR_MAX_Z];
    XW XW_floor1[XW_MAX_X][XW_MAX_Z];
    ZW ZW_floor1[ZW_MAX_X][ZW_MAX_Z];
    
    int x, z;
    x = 0;
    z = 0;

    //Ground parameters (all true)
    while (z < GR_MAX_Z) {
        while (x < GR_MAX_X) {
            GR_floor1[x][z].ground = true;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //X-wall parameters (all true)
    while (z < XW_MAX_Z) {
        while (x < XW_MAX_X) {
            XW_floor1[x][z].xwall = true;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;


    //Z-wall parameters (all true)
    while (z < ZW_MAX_Z) {
        while (x < ZW_MAX_X) {
            ZW_floor1[x][z].zwall = true;
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;


    //Roof parameters (all true)
    while (z < GR_MAX_Z) {
        while (x < GR_MAX_X) {
            GR_floor1[x][z].roof = true;
            x++;
        }
        x = 0;
        z++;
    }

    /*floor1[0][0].ground = true;
    floor1[0][1].ground = true;
    floor1[0][2].ground = true;
    floor1[0][3].ground = true;
    floor1[0][4].ground = true;
    floor1[0][5].ground = true;

    floor1[1][0].ground = true;
    floor1[1][1].ground = true;
    floor1[1][2].ground = true;
    floor1[1][3].ground = true;
    floor1[1][4].ground = true;
    floor1[1][5].ground = true;

    floor1[2][0].ground = true;
    floor1[2][1].ground = true;
    floor1[2][2].ground = true;
    floor1[2][3].ground = true;
    floor1[2][4].ground = true;
    floor1[2][5].ground = true;

    floor1[3][0].ground = true;
    floor1[3][1].ground = true;
    floor1[3][2].ground = true;
    floor1[3][3].ground = true;
    floor1[3][4].ground = true;
    floor1[3][5].ground = true;

    floor1[4][0].ground = true;
    floor1[4][1].ground = true;
    floor1[4][2].ground = true;
    floor1[4][3].ground = true;
    floor1[4][4].ground = true;
    floor1[4][5].ground = true;

    //Right wall parameters

    floor1[0][0].rwall = true;
    floor1[0][1].rwall = true;
    floor1[0][2].rwall = true;
    floor1[0][3].rwall = true;
    floor1[0][4].rwall = true;
    floor1[0][5].rwall = true;

    floor1[1][0].rwall = true;
    floor1[1][1].rwall = true;
    floor1[1][2].rwall = true;
    floor1[1][3].rwall = true;
    floor1[1][4].rwall = true;
    floor1[1][5].rwall = true;

    floor1[2][0].rwall = true;
    floor1[2][1].rwall = true;
    floor1[2][2].rwall = true;
    floor1[2][3].rwall = true;
    floor1[2][4].rwall = true;
    floor1[2][5].rwall = true;

    floor1[3][0].rwall = true;
    floor1[3][1].rwall = true;
    floor1[3][2].rwall = true;
    floor1[3][3].rwall = true;
    floor1[3][4].rwall = true;
    floor1[3][5].rwall = true;

    floor1[4][0].rwall = true;
    floor1[4][1].rwall = true;
    floor1[4][2].rwall = true;
    floor1[4][3].rwall = true;
    floor1[4][4].rwall = true;
    floor1[4][5].rwall = true;

    //Back wall parameters

    floor1[0][0].bwall = true;
    floor1[0][1].bwall = true;
    floor1[0][2].bwall = true;
    floor1[0][3].bwall = true;
    floor1[0][4].bwall = true;
    floor1[0][5].bwall = true;

    floor1[1][0].bwall = true;
    floor1[1][1].bwall = true;
    floor1[1][2].bwall = true;
    floor1[1][3].bwall = true;
    floor1[1][4].bwall = true;
    floor1[1][5].bwall = true;

    floor1[2][0].bwall = true;
    floor1[2][1].bwall = true;
    floor1[2][2].bwall = true;
    floor1[2][3].bwall = true;
    floor1[2][4].bwall = true;
    floor1[2][5].bwall = true;

    floor1[3][0].bwall = true;
    floor1[3][1].bwall = true;
    floor1[3][2].bwall = true;
    floor1[3][3].bwall = true;
    floor1[3][4].bwall = true;
    floor1[3][5].bwall = true;

    floor1[4][0].bwall = true;
    floor1[4][1].bwall = true;
    floor1[4][2].bwall = true;
    floor1[4][3].bwall = true;
    floor1[4][4].bwall = true;
    floor1[4][5].bwall = true;

    //Roof parameters

    floor1[0][0].roof = true;
    floor1[0][1].roof = true;
    floor1[0][2].roof = true;
    floor1[0][3].roof = true;
    floor1[0][4].roof = true;
    floor1[0][5].roof = true;

    floor1[1][0].roof = true;
    floor1[1][1].roof = true;
    floor1[1][2].roof = true;
    floor1[1][3].roof = true;
    floor1[1][4].roof = true;
    floor1[1][5].roof = true;

    floor1[2][0].roof = true;
    floor1[2][1].roof = true;
    floor1[2][2].roof = true;
    floor1[2][3].roof = true;
    floor1[2][4].roof = true;
    floor1[2][5].roof = true;

    floor1[3][0].roof = true;
    floor1[3][1].roof = true;
    floor1[3][2].roof = true;
    floor1[3][3].roof = true;
    floor1[3][4].roof = true;
    floor1[3][5].roof = true;

    floor1[4][0].roof = true;
    floor1[4][1].roof = true;
    floor1[4][2].roof = true;
    floor1[4][3].roof = true;
    floor1[4][4].roof = true;
    floor1[4][5].roof = true;*/

    //Creating positions for assets
    Vector3 g_positions[GR_MAX_X][GR_MAX_Z] = { 0 };
    Vector3 xw_positions[XW_MAX_X][XW_MAX_Z] = { 0 };
    Vector3 zw_positions[ZW_MAX_X][ZW_MAX_Z] = { 0 };
    Vector3 rf_positions[GR_MAX_X][GR_MAX_Z] = { 0 };
    
    x = 0;
    z = 0;

    //Initializing ground tile positions
    while (z < GR_MAX_Z) {
        while (x < GR_MAX_X) {
            g_positions[x][z].x = 8*x;
            g_positions[x][z].y = 0;
            g_positions[x][z].z = 8*z;
            printf("g_positions[%d][%d].x = %f\n", x, z, g_positions[x][z].x);
            printf("g_positions[%d][%d].y = %f\n", x, z, g_positions[x][z].y);
            printf("g_positions[%d][%d].z = %f\n", x, z, g_positions[x][z].z);
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing x-wall positions
    while (z < XW_MAX_Z) {
        while (x < XW_MAX_X) {
            xw_positions[x][z].x = -4+(8*x);
            xw_positions[x][z].y = 2.5;
            xw_positions[x][z].z = 8*z;
            printf("rw_positions[%d][%d].x = %f\n", x, z, xw_positions[x][z].x);
            printf("rw_positions[%d][%d].y = %f\n", x, z, xw_positions[x][z].y);
            printf("rw_positions[%d][%d].z = %f\n", x, z, xw_positions[x][z].z);
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing z-wall positions
    while (z < ZW_MAX_Z) {
        while (x < ZW_MAX_X) {
            zw_positions[x][z].x = 0.0+(8*x);
            zw_positions[x][z].y = 2.5;
            zw_positions[x][z].z = -4.0+(8*z);
            printf("bw_positions[%d][%d].x = %f\n", x, z, zw_positions[x][z].x);
            printf("bw_positions[%d][%d].y = %f\n", x, z, zw_positions[x][z].y);
            printf("bw_positions[%d][%d].z = %f\n", x, z, zw_positions[x][z].z);
            x++;
        }
        x = 0;
        z++;
    }

    x = 0;
    z = 0;

    //Initializing roof tile positions
    while (z < GR_MAX_Z) {
        while (x < GR_MAX_X) {
            rf_positions[x][z].x = 8*x;
            rf_positions[x][z].y = 5.0;
            rf_positions[x][z].z = 8*z;
            printf("rf_positions[%d][%d].x = %f\n", x, z, rf_positions[x][z].x);
            printf("rf_positions[%d][%d].y = %f\n", x, z, rf_positions[x][z].y);
            printf("rf_positions[%d][%d].z = %f\n", x, z, rf_positions[x][z].z);
            x++;
        }
        x = 0;
        z++;
    }

    while (!WindowShouldClose())
    {
        DrawFPS(0,0);

        UpdateCamera(&camera);
        
        BeginDrawing();

            ClearBackground(BLACK);

            //XYZ | width, height, length

            BeginMode3D(camera);

                //Floor
                x = 0;
                z = 0;
                while (z < GR_MAX_Z) {
                    while (x < GR_MAX_X) {
                        //printf("floor1[%d][%d].ground = %d\n", i, j, floor1[i][j].ground);
                        if (GR_floor1[x][z].ground == true) {
                            DrawPlane(g_positions[x][z], (Vector2){ 8, 8 }, GRAY);
                            DrawCubeWires(g_positions[x][z], 8.0f, 0.0f, 8.0f, BLACK);
                        }
                        x++;
                    }
                    x = 0;
                    z++;
                }
                
                //X-wall
                x = 0;
                z = 0;
                while (z < XW_MAX_Z) {
                    while (x < XW_MAX_X) {
                        if (XW_floor1[x][z].xwall == true) {
                            DrawCube(xw_positions[x][z], 0.0f, 5.0f, 8.0f, BLUE); 
                            DrawCubeWires(xw_positions[x][z], 0.0f, 5.0f, 8.0f, BLACK); 
                        }
                        x++;
                    }
                    x = 0;
                    z++;
                }

                //Z-wall
                x = 0;
                z = 0;
                while (z < (ZW_MAX_Z)) {
                    while (x < ZW_MAX_X) {
                        if (ZW_floor1[x][z].zwall == true) {
                            DrawCube(zw_positions[x][z], 8.0f, 5.0f, 0.0f, BLUE);
                            DrawCubeWires((Vector3){ 0.0f, 2.5f, 4.0f }, 8.0f, 5.0f, 0.0f, BLACK);
                        }
                        x++;
                    }
                    x = 0;
                    z++;
                }

                //Roof
                x = 0;
                z = 0;
                while (z < GR_MAX_Z) {
                    while (x < GR_MAX_X) {
                        if (GR_floor1[x][z].roof == true) {
                            DrawCube(rf_positions[x][z], 8.0f, 0.0f, 8.0f, BLUE);
                            DrawCubeWires(rf_positions[x][z], 8.0f, 0.0f, 8.0f, BLACK);
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