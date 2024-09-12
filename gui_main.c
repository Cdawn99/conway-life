#include "conway.h"

#include "raylib.h"

#include <stdio.h>

#define GRID_HEIGHT_CELLS 40
#define GRID_WIDTH_CELLS 71

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

int reset_state(grid_t **grid1, grid_t **grid2) {
    if (!grid1 && !*grid1 && !grid2 && !*grid2) {
        fprintf(stderr, "ERROR: A grid is NULL");
        return 1;
    }

    delete_grid(*grid1);
    delete_grid(*grid2);

    *grid1 = init_grid(GRID_HEIGHT_CELLS, GRID_WIDTH_CELLS);
    if (!*grid1) {
        fprintf(stderr, "ERROR: Failed to allocate grid\n");
        return 1;
    }

    *grid2 = init_grid(GRID_HEIGHT_CELLS, GRID_WIDTH_CELLS);
    if (!*grid2) {
        delete_grid(*grid1);
        fprintf(stderr, "ERROR: Failed to allocate grid\n");
        return 1;
    }

    return 0;
}

int main(void) {
    int status = 0;

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
    bool playing = true;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            status = reset_state(&current, &next);
            if (status == 1) {
                break;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            playing = !playing;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            display_grid(current);
            // DrawFPS(10, 10);
        EndDrawing();

        if (playing) {
            if (frame_delay > 0) {
                frame_delay--;
            } else {
                compute_next_state(current, next);
                swap_grids(&current, &next);
                frame_delay = 10;
            }
        }
    }

    CloseWindow();

    delete_grid(current);
    delete_grid(next);

    return status;
}
