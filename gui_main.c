#include "conway.h"

#include "raylib.h"

#include <stdio.h>

#define GRID_HEIGHT_CELLS 40
#define GRID_WIDTH_CELLS 40

void display_grid(grid_t *grid) {
    Rectangle cell = {
        .width = (float)GetScreenWidth() / grid->width,
        .height = (float)GetScreenHeight() / grid->height,
    };

    for (size_t y = 0; y < grid->height; y++) {
        for (size_t x = 0; x < grid->width; x++) {
            Color cell_colour = grid->grid[coordinate(y, x, grid->width)] == '#' ? BLACK : WHITE;
            DrawRectangleRec(cell, cell_colour);
            cell.x += cell.width;
        }
        cell.x -= cell.width * grid->width;
        cell.y += cell.height;
    }
}

int main(void) {
    grid_t *current = init_grid(GRID_HEIGHT_CELLS, GRID_WIDTH_CELLS);
    if (!current) {
        fprintf(stderr, "ERROR: Failed to allocate grid\n");
        return 1;
    }

    grid_t *next = init_grid(GRID_HEIGHT_CELLS, GRID_WIDTH_CELLS);
    if (!next) {
        delete_grid(current);
        fprintf(stderr, "ERROR: Failed to allocate grid\n");
        return 1;
    }

    InitWindow(1600, 900, "Conway's Game of Life");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    int frame_delay = 10;
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            display_grid(current);
        EndDrawing();

        if (frame_delay > 0) {
            frame_delay--;
        } else {
            compute_next_state(current, next);
            swap_grids(&current, &next);
            frame_delay = 10;
        }
    }

    CloseWindow();

    delete_grid(current);
    delete_grid(next);

    return 0;
}
