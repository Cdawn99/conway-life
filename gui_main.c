#include "raylib.h"

int main(void) {
    InitWindow(1600, 900, "Conway's Game of Life");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
