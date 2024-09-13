#include "conway.h"

#include "raylib.h"

#include <stdio.h>

#define GRID_HEIGHT_CELLS 40
#define GRID_WIDTH_CELLS 71

#define MAXIMUM_MAX_FRAME_DELAY 20
#define MINIMUM_MAX_FRAME_DELAY 1
#define DEFAULT_MAX_FRAME_DELAY 10

void display_grid(grid_t *grid) {
    Rectangle cell = {
        .width = (float)GetScreenWidth() / grid->width,
        .height = (float)GetScreenHeight() / grid->height,
    };

    for (size_t y = 0; y < grid->height; y++) {
        for (size_t x = 0; x < grid->width; x++) {
            Color cell_colour = grid->grid[coordinate(y, x, grid->width)] ? BLACK : WHITE;
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

    int max_frame_delay = DEFAULT_MAX_FRAME_DELAY;
    int frame_delay = max_frame_delay;
    bool playing = true;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            max_frame_delay = DEFAULT_MAX_FRAME_DELAY;
            status = reset_state(&current, &next);
            if (status == 1) {
                break;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            playing = !playing;
        }

        if (IsKeyDown(KEY_RIGHT) && max_frame_delay > MINIMUM_MAX_FRAME_DELAY) {
            max_frame_delay--;
        }

        if (IsKeyDown(KEY_LEFT) && max_frame_delay < MAXIMUM_MAX_FRAME_DELAY) {
            max_frame_delay++;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            display_grid(current);

            // char frame_delay_text[30] = {0};
            // sprintf(frame_delay_text, "Frame delay: %d", max_frame_delay);
            // DrawText(frame_delay_text, 10, 10, 20, RED);

            // DrawFPS(10, 10);
        EndDrawing();

        if (playing) {
            if (frame_delay > 0) {
                frame_delay--;
            } else {
                compute_next_state(current, next);
                swap_grids(&current, &next);
                frame_delay = max_frame_delay;
            }
        }
    }

    CloseWindow();

    delete_grid(current);
    delete_grid(next);

    return status;
}
