#include "conway.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int continue_generating();
size_t convert_string_to_size_t(char* str);

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <height> <width>\n", argv[0]);
        return 1;
    }
    srand((unsigned int)time(0));
    size_t height = convert_string_to_size_t(argv[1]);
    size_t width = convert_string_to_size_t(argv[2]);
    if (height == 0 || width == 0) {
        printf("Arguments must be positive integers\n");
        return 1;
    }
    grid_t* grid1 = init_grid(height, width);
    if (!grid1) {
        printf("ERROR: Failed to allocate grid1\n");
        return 1;
    }
    grid_t* grid2 = init_grid(height, width);
    if (!grid2) {
        delete_grid(grid1);
        printf("ERROR: Failed to allocate grid2\n");
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

int continue_generating() {
    char c;
    scanf_s("%c", &c, 1);
    return c == '\n';
}

size_t convert_string_to_size_t(char* str) {
    int result;
    int succ = sscanf_s(str, "%d", &result);
    if (succ == 0 || result <= 0) {
        return 0;
    }
    return (size_t)result;
}
