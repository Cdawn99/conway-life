#include "conway.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_grid(grid_t *grid) {
    if (!grid) {
        puts("NULL grid");
        return;
    }

    for (size_t h = 0; h < grid->height; h++) {
        for(size_t w = 0; w < grid->width; w++) {
            char c = grid->grid[coordinate(h, w, grid->width)] ? '#' : ' ';
            putchar(c);
        }
        putchar('\n');
    }
}

int continue_generating() {
    char c;
    scanf("%c", &c);
    return c == '\n';
}

size_t convert_string_to_size_t(char *str) {
    int result;
    int succ = sscanf(str, "%d", &result);
    if (succ != 1 || result <= 0) {
        return 0;
    }
    return (size_t)result;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc != 3) {
        printf("Usage: %s <height> <width>\n", argv[0]);
        return 1;
    }

    size_t height = convert_string_to_size_t(argv[1]);
    size_t width = convert_string_to_size_t(argv[2]);
    if (height == 0 || width == 0) {
        printf("Arguments must be positive integers\n");
        return 1;
    }

    grid_t *grid1 = init_grid(height, width);
    if (!grid1) {
        fprintf(stderr, "ERROR: Failed to allocate grid1\n");
        return 1;
    }

    grid_t *grid2 = init_grid(height, width);
    if (!grid2) {
        delete_grid(grid1);
        fprintf(stderr, "ERROR: Failed to allocate grid2\n");
        return 1;
    }

    print_grid(grid1);
    while (continue_generating()) {
        printf("---------------------------------------------------\n");
        compute_next_state(grid1, grid2);
        swap_grids(&grid1, &grid2);
        print_grid(grid1);
    }

    delete_grid(grid1);
    delete_grid(grid2);

    return 0;
}
