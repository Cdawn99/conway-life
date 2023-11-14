#include "conway.h"

typedef struct grid {
    size_t height;
    size_t width;
    char grid[];
} grid_t;

static size_t coordinate(size_t h, size_t w, size_t width) {
    return h*width + w;
}

static char compute_next_cell_state(size_t h_coordinate, size_t w_coordinate, grid_t* current) {
    size_t coordinates[8];
    coordinates[0] = coordinate(h_coordinate == 0 ? current->height - 1 : h_coordinate - 1,
                                w_coordinate == 0 ? current->width - 1 : w_coordinate - 1,
                                current->width);
    coordinates[1] = coordinate(h_coordinate == 0 ? current->height - 1 : h_coordinate - 1,
                                w_coordinate,
                                current->width);
    coordinates[2] = coordinate(h_coordinate == 0 ? current->height - 1 : h_coordinate - 1,
                                w_coordinate == current->width - 1 ? 0 : w_coordinate + 1,
                                current->width);
    coordinates[3] = coordinate(h_coordinate,
                                w_coordinate == 0 ? current->width - 1 : w_coordinate - 1,
                                current->width);
    coordinates[4] = coordinate(h_coordinate,
                                w_coordinate == current->width - 1 ? 0 : w_coordinate + 1,
                                current->width);
    coordinates[5] = coordinate(h_coordinate == current->height - 1 ? 0 : h_coordinate + 1,
                                w_coordinate == 0 ? current->width - 1 : w_coordinate - 1,
                                current->width);
    coordinates[6] = coordinate(h_coordinate == current->height - 1 ? 0 : h_coordinate + 1,
                                w_coordinate,
                                current->width);
    coordinates[7] = coordinate(h_coordinate == current->height - 1 ? 0 : h_coordinate + 1,
                                w_coordinate == current->width - 1 ? 0 : w_coordinate + 1,
                                current->width);
    int live_neighbours = 0;
    for (int i = 0; i < 8; i++) {
        if (current->grid[coordinates[i]] == '#') {
            live_neighbours++;
        }
    }
    if (current->grid[coordinate(h_coordinate, w_coordinate, current->width)] == ' ') {
        return live_neighbours == 3 ? '#' : ' ';
    }
    return live_neighbours == 2 || live_neighbours == 3 ? '#' : ' ';
}

grid_t* init_grid(size_t height, size_t width) {
    if (height == 0 || width == 0) {
        return NULL;
    }
    grid_t* new_grid = malloc(sizeof(grid_t) + height*width);
    if (!new_grid) {
        return NULL;
    }
    new_grid->height = height;
    new_grid->width = width;
    for (size_t i = 0; i < height*width; i++) {
        new_grid->grid[i] = rand() % 2 == 0 ? '#' : ' ';
    }
    return new_grid;
}

void delete_grid(grid_t* grid) {
    free(grid);
}

err_t print_grid(grid_t* grid) {
    if (!grid) {
        return NULL_GRID;
    }
    for (size_t h = 0; h < grid->height; h++) {
        for(size_t w = 0; w < grid->width; w++) {
            printf("%c", grid->grid[coordinate(h, w, grid->width)]);
        }
        printf("\n");
    }
    return SUCCESS;
}

err_t compute_next_state(grid_t* current, grid_t* next) {
    if (current->width != next->width || current->height != next->height) {
        return SIZE_MISMATCH;
    }
    for (size_t h = 0; h < current->height; h++) {
        for (size_t w = 0; w < current->width; w++) {
            next->grid[coordinate(h, w, next->width)] = compute_next_cell_state(h, w, current);
        }
    }
    return SUCCESS;
}

err_t swap_grids(grid_t** grid1, grid_t** grid2) {
    grid_t* temp = *grid1;
    *grid1 = *grid2;
    *grid2 = temp;
    return SUCCESS;
}
