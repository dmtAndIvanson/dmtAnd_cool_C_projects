#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "stack.h"

void output(int matrix[][80], int rows, int cols);

int main(void) {
    int length;
    // Receive expression.
    char *string = get_string(&length);
    // Transpate to RPN.
    char *rpn = make_rpn(string);

    // Create matrix.
    int matrix[25][80] = {0};

    double delta = M_PI / 79 * 4;
    for (int j = 0; j < 80; j++) {
        double y = calculate_rpn(rpn, delta * j);
        if (y >= -1 && y <= 1) {
            int i = (int)round(12 + y * 12);
            matrix[i][j] = 1;
        }
    }

    output(matrix, 25, 80);

    free(rpn);
    free(string);
    return 0;
}

void output(int matrix[][80], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", matrix[i][j] == 1 ? '*' : '.');
            if (j == cols - 1) {
                printf("\n");
            }
        }
    }
}
