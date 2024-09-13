#ifndef CONWAY_H
#define CONWAY_H

#include <stdbool.h>
#include <stddef.h>

typedef bool cell_t;

typedef struct grid {
    size_t height;
    size_t width;
    cell_t grid[];
} grid_t;

/**
 * Initialize grid.
 * Returns NULL in the following cases.
 * height == 0 or width == 0
 * allocation failure occurs
 */
grid_t *init_grid(size_t height, size_t width);

/**
 * Free the given grid.
 */
void delete_grid(grid_t *grid);

/**
 * Compute the current grid's next state.
 * Asserts that the grids have matching widths and heights.
 */
void compute_next_state(grid_t *current, grid_t *next);

/**
 * Swap the given grids.
 */
void swap_grids(grid_t **grid1, grid_t **grid2);

static inline size_t coordinate(size_t h, size_t w, size_t width) {
    return h*width + w;
}

#endif // CONWAY_H
