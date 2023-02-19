#include "stack.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct stack *init_s(int number) {
    struct stack *root = malloc(sizeof(struct stack));
    if (root != NULL) {
        root->number = number;
        root->x = 0;
        root->next_node = NULL;
    }
    return root;
}

void push_s(struct stack *root, double number, char x) {
    struct stack *new_node = malloc(sizeof(struct stack));
    if (new_node != NULL) {
        // Change pointers.
        struct stack *tmp_node = root->next_node;
        root->next_node = new_node;

        // Initialize new node.
        new_node->number = number;
        new_node->x = x;
        new_node->next_node = tmp_node;
    }
}

double pop_s(struct stack *root) {
    double return_n = 0;
    if (root->next_node != NULL) {
        // Change pointers.
        struct stack *tmp_node = root->next_node;
        root->next_node = root->next_node->next_node;

        // Pop value and delete node.
        return_n = tmp_node->number;
        free(tmp_node);
    }
    return return_n;
}

void destroy_s(struct stack *root) {
    if (root->next_node != NULL) {
        destroy_s(root->next_node);
    }
    free(root);
}

double get_x(struct stack *root, double val) {
    double return_v = val;
    if (root->next_node != NULL) {
        if (root->next_node->x != 'x') {
            return_v = root->next_node->number;
        }
        pop_s(root);
    }
    return return_v;
}

double calculate_rpn(char *rpn, double x) {
    struct stack *root = init_s(21);

    double sum = 0.0;
    for (; *rpn; rpn++) {
        if (*rpn >= '0' && *rpn <= '9') {
            double num = 0;
            while (*rpn >= '0' && *rpn <= '9') {
                num = num * 10 + *rpn - '0';
                rpn++;
            }
            rpn--;
            push_s(root, num, 0);
        } else if (*rpn == 'x') {
            push_s(root, 0, 'x');
        } else {
            if (*rpn == '+') {
                sum = get_x(root, x) + get_x(root, x);

                push_s(root, sum, 0);
            } else if (*rpn == '-') {
                sum = get_x(root, x) - get_x(root, x);
                push_s(root, sum, 0);
            } else if (*rpn == '*') {
                sum = get_x(root, x) * get_x(root, x);
                push_s(root, sum, 0);
            } else if (*rpn == '/') {
                double one = get_x(root, x);
                double two = get_x(root, x);
                sum = two / one;
                push_s(root, sum, 0);
            } else if (*rpn == 's') {
                double tmp = get_x(root, x);
                //printf("tmp: %lf\n", tmp);
                sum = sin(tmp);  // * M_PI / 180.0);
                push_s(root, sum, 0);
            } else if (*rpn == 'c') {
                sum = cos(get_x(root, x));  //* M_PI / 180.0);
                push_s(root, sum, 0);
            } else if (*rpn == 't') {
                sum = tan(get_x(root, x));  //* M_PI / 180.0);
                push_s(root, sum, 0);
            } else if (*rpn == 'g') {
                sum = 1.0 / tan(get_x(root, x));  //* M_PI / 180.0);
                push_s(root, sum, 0);
            } else if (*rpn == 'q') {
                sum = sqrt(get_x(root, x));
                push_s(root, sum, 0);
            } else if (*rpn == 'l') {
                sum = log(get_x(root, x));
                push_s(root, sum, 0);
            }
        }
    }

    destroy_s(root);
    return sum;
}