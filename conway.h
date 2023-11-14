#ifndef CONWAY_H
#define CONWAY_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct grid grid_t;

typedef enum err {
    SUCCESS = 0,
    SIZE_MISMATCH = 1,
    NULL_GRID = 2
} err_t;

grid_t* init_grid(size_t height, size_t width);
void delete_grid(grid_t* grid);

err_t print_grid(grid_t* grid);

err_t compute_next_state(grid_t* current, grid_t* next);
err_t swap_grids(grid_t** grid1, grid_t** grid2);

#endif

// cl /W4 /std:c17 main.c conway.c /link /out:conway.exe