#include "conway.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static inline int mod(int x, int n) {
    return (x%n + n)%n;
}

static bool compute_next_cell_state(grid_t *current, size_t h_coordinate, size_t w_coordinate) {
    int live_neighbours = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            size_t h = mod((int)h_coordinate + i, current->height);
            size_t w = mod((int)w_coordinate + j, current->width);
            live_neighbours += current->grid[coordinate(h, w, current->width)];
        }
    }

    bool cell = current->grid[coordinate(h_coordinate, w_coordinate, current->width)];
    return live_neighbours == 3 || (cell && live_neighbours == 2);
}

grid_t *init_grid(size_t height, size_t width) {
    if (height == 0 || width == 0) {
        return NULL;
    }

    grid_t *new_grid = malloc(sizeof *new_grid + height*width*sizeof(cell_t));
    if (!new_grid) {
        return NULL;
    }

    new_grid->height = height;
    new_grid->width = width;

    for (size_t i = 0; i < height*width; i++) {
        new_grid->grid[i] = rand() % 2;
    }
    return new_grid;
}

void delete_grid(grid_t *grid) {
    free(grid);
}

void compute_next_state(grid_t *current, grid_t *next) {
    assert(current->width == next->width && current->height == next->height);

    for (size_t h = 0; h < current->height; h++) {
        for (size_t w = 0; w < current->width; w++) {
            next->grid[coordinate(h, w, next->width)] = compute_next_cell_state(current, h, w);
        }
    }
}

void swap_grids(grid_t **grid1, grid_t **grid2) {
    grid_t *temp = *grid1;
    *grid1 = *grid2;
    *grid2 = temp;
}
