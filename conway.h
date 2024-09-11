#ifndef CONWAY_H
#define CONWAY_H

#include <stddef.h>

typedef struct grid {
    size_t height;
    size_t width;
    char grid[];
} grid_t;

grid_t *init_grid(size_t height, size_t width);
void delete_grid(grid_t *grid);

void print_grid(grid_t *grid);

void compute_next_state(grid_t *current, grid_t *next);
void swap_grids(grid_t **grid1, grid_t **grid2);

static inline size_t coordinate(size_t h, size_t w, size_t width) {
    return h*width + w;
}

#endif // CONWAY_H
