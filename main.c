#include "include/raylib.h"
#include <stdio.h>
#include "game.h"

#define DEBUGON
#ifdef DEBUGON
#define DEBUG(msg) printf("DEBUG: %s\n", msg)
#else 
#define DEBUG(msg)
#endif

//gcc main.c -o game.exe -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

int main() 
{
    const int screenWidth = 1024;
    const int screenHeight = 576;

    InitWindow(screenWidth, screenHeight, "Dungeon Crawler");

    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    SetTargetFPS(60);

    int x = 5;
    int z = 5;

    floor floor[5][5];

    floor[0][0].ground = true;
    floor[0][1].ground = false;
    floor[0][2].ground = true;
    floor[0][3].ground = false;
    floor[0][4].ground = true;

    floor[1][0].ground = true;
    floor[1][1].ground = false;
    floor[1][2].ground = true;
    floor[1][3].ground = false;
    floor[1][4].ground = true;

    floor[2][0].ground = true;
    floor[2][1].ground = false;
    floor[2][2].ground = true;
    floor[2][3].ground = false;
    floor[2][4].ground = true;

    floor[3][0].ground = true;
    floor[3][1].ground = false;
    floor[3][2].ground = true;
    floor[3][3].ground = false;
    floor[3][4].ground = true;

    floor[4][0].ground = true;
    floor[4][1].ground = false;
    floor[4][2].ground = true;
    floor[4][3].ground = false;
    floor[4][4].ground = true;

    Vector3 positions[5][5] = { 0 };
    
    int i, j;
    i = 0;
    j = 0;

    while (i < 5) {
        DEBUG("in loop #1 (i < 5)\n");
        while (j < 5) {
            DEBUG("in loop #1 (j < 5)\n");
            positions[i][j].x = 8*j;
            positions[i][j].z = -8*i;
            printf("positions[%d][%d].x = %f\n", i, j, positions[i][j].x);
            printf("positions[%d][%d].z = %f\n", i, j, positions[i][j].z);
            j++;
        }
        j = 0;
        i++;
    }

    i = 0;
    j = 0;
        
    while (i < 5) {
        DEBUG("in loop #2 (i < 5)");
        while (j < 5) {
            DEBUG("in loop #2 (i < 5)");
            printf("Positions[%d][%d]: x: %f, y: %f, z: %f\n", i, j, positions[i][j].x, positions[i][j].y, positions[i][j].z);
            j++;
        }
        j = 0;
        i++;
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
                i = 0;
                j = 0;
                while (i < 5) {
                    while (j < 5) {
                        if (floor[i][j].ground == true) {
                            DrawPlane(positions[i][j], (Vector2){ 8, 8 }, GRAY);
                        }
                        j++;
                    }
                    j = 0;
                    i++;
                }
                
                //Right wall
                i = 0;
                j = 0;
                while (i < 5) {
                    while (j < 5) {
                        if (floor[i][j].rwall == true) {
                            DrawCube((Vector3){ 4.0f, 2.5f, 0.0f }, 0.25f, 5.0f, 8.0f, BLUE); 
                            DrawCubeWires((Vector3){ 4.0f, 2.5f, 0.0f }, 0.26f, 5.0f, 8.0f, BLACK); 
                        }
                        j++;
                    }
                    j = 0;
                    i++;
                }
                  

                //Left wall
                i = 0;
                j = 0;
                while (i < 5) {
                    while (j < 5) {
                        if (floor[i][j].lwall == true) {
                            DrawCube((Vector3){ -4.0f, 2.5f, 0.0f }, 0.25f, 5.0f, 8.0f, BLUE);      
                            DrawCubeWires((Vector3){ -4.0f, 2.5f, 0.0f }, 0.26f, 5.0f, 8.0f, BLACK);
                        }
                        j++;
                    }
                    j = 0;
                    i++;
                }
                

                //Back wall
                i = 0;
                j = 0;
                while (i < 5) {
                    while (j < 5) {
                        if (floor[i][j].bwall == true) {
                            DrawCube((Vector3){ 0.0f, 2.5f, 8.0f }, 8.0f, 5.0f, 8.0f, BLUE);
                            DrawCubeWires((Vector3){ 0.0f, 2.5f, 8.0f }, 8.0f, 5.0f, 8.0f, BLACK);
                        }
                        j++;
                    }
                    j = 0;
                    i++;
                }
                

                //Front wall
                i = 0;
                j = 0;
                while (i < 5) {
                    while (j < 5) {
                        if (floor[i][j].fwall == true) {
                            DrawPlane(positions[i][j], (Vector2){ 8, 8 }, GRAY);
                        }
                        j++;
                    }
                    j = 0;
                    i++;
                }

                //Roof
                i = 0;
                j = 0;
                while (i < 5) {
                    while (j < 5) {
                        if (floor[i][j].roof == true) {
                            DrawCube((Vector3){ 0.0f, 5.15f, 0.0f }, 8.25f, 0.25f, 8.0f, BLUE);
                            DrawCubeWires((Vector3){ 0.0f, 5.15f, 0.0f }, 8.25f, 0.25f, 8.0f, BLACK);
                        }
                        j++;
                    }
                    j = 0;
                    i++;
                }

            EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}