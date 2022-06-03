#include "raylib.h"

#define ScreenWidth 900
#define ScreenHeight 600

#define MinWindowWidth 700
#define MinWindowHeight 500

#define FPS 120

int main()
{

    // Window Configuration:
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "Algo_Visualiser");
    SetWindowMinSize(MinWindowWidth, MinWindowHeight);

    // Set FPS
    SetTargetFPS(FPS);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(PURPLE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}