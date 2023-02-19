#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_string(int *len) {
    *len = 0;          // изначально строка пуста
    int capacity = 1;  // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char *s = (char *)malloc(sizeof(char));  // динамическая пустая строка

    char c = getchar();  // символ для чтения данных

    // читаем символы, пока не получим символ переноса строки (\n)
    while (c != '\n') {
        s[(*len)++] = c;  // заносим в строку новый символ

        // если реальный размер больше размера контейнера, то увеличим его размер
        if (*len >= capacity) {
            capacity *= 2;  // увеличиваем ёмкость строки в два раза
            s = (char *)realloc(s, capacity * sizeof(char));  // создаём новую строку с увеличенной ёмкостью
        }

        c = getchar();  // считываем следующий символ
    }

    s[*len] = '\0';  // завершаем строку символом конца строки

    return s;  // возвращаем указатель на считанную строку
}

struct node *init(void) {
    struct node *root = malloc(sizeof(struct node));
    if (root != NULL) {
        root->opertr = '\0';
        root->next_node = NULL;
    }
    return root;
}

void push(struct node *root, char opertr) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node != NULL) {
        // Change pointers.
        struct node *tmp_node = root->next_node;
        root->next_node = new_node;

        // Initialize new node.
        new_node->opertr = opertr;
        new_node->prior = get_prior(opertr);
        new_node->next_node = tmp_node;
    }
}

char pop(struct node *root) {
    char return_n = 's';
    if (root->next_node != NULL) {
        // Change pointers.
        struct node *tmp_node = root->next_node;
        root->next_node = root->next_node->next_node;

        // Pop value and delete node.
        return_n = tmp_node->opertr;
        free(tmp_node);
    }
    return return_n;
}

void destroy(struct node *root) {
    if (root->next_node != NULL) {
        destroy(root->next_node);
    }
    free(root);
}

int get_prior(char opertr) {
    int prior = -1;
    if (opertr == '(' || opertr == ')') {
        prior = -1;
    } else if (opertr == '*' || opertr == '/') {
        prior = 1;
    } else if (opertr == '-' || opertr == '+') {
        prior = 0;
    } else {
        prior = 1;
    }
    return prior;
}

char *make_rpn(char *infix) {
    // Make string for polish notation.
    char *rpn = malloc(sizeof(char) * strlen(infix) * 4);
    char *t_rpn = rpn;

    // Make variable for stack.
    struct node *root = NULL;

    // Run through every element in string.
    for (; *infix; infix++) {
        if (*infix == ' ') {
            continue;
        }
        if ((*infix >= '0' && *infix <= '9') || *infix == 'x') {
            // Add element to the rpn-string.
            *t_rpn++ = *infix;
            if (*(infix + 1) < '0' || *(infix + 1) > '9') {
                *t_rpn++ = ' ';
            }
        } else {
            // TODO: initialize stack, if it wasn't.
            if (root == NULL) {
                root = init();
            }
            if (root == NULL) {
                // Remove break!
                break;
            }
            // If not '(' and ')'.
            if (*infix != '(' && *infix != ')') {
                if (root->next_node == NULL && strchr("sctl", *infix) == NULL) {
                    push(root, *infix);
                } else {
                    // Detemine priority.
                    int prior = get_prior(*infix);
                    if (strchr("sctl", *infix) != NULL) {
                        char tmp = 'a';
                        if (infix == strstr(infix, "sin")) {
                            tmp = 's';
                            infix += 2;

                        } else if (infix == strstr(infix, "cos")) {
                            tmp = 'c';
                            infix += 2;
                        } else if (infix == strstr(infix, "tan")) {
                            tmp = 't';
                            infix += 2;
                        } else if (infix == strstr(infix, "ctg")) {
                            tmp = 'g';
                            infix += 2;
                        } else if (infix == strstr(infix, "sqrt")) {
                            tmp = 'q';
                            infix += 3;
                        } else if (infix == strstr(infix, "ln")) {
                            tmp = 'l';
                            infix += 1;
                        }
                        if (root->next_node == NULL) {
                            push(root, tmp);
                        }
                        // If priority > than in stack:
                        else if (prior > root->next_node->prior) {
                            // Add element to stack.
                            push(root, tmp);
                        }
                        // Else:
                        else {
                            // Pop value from stack.
                            char tmp = pop(root);
                            // Add it to string.
                            *t_rpn++ = tmp;
                            *t_rpn++ = ' ';
                            // Push current element.
                            push(root, tmp);
                        }
                    } else {
                        // If priority > than in stack:
                        if (root->next_node == NULL) {
                            push(root, *infix);
                        } else if (prior > root->next_node->prior) {
                            // Add element to stack.
                            push(root, *infix);
                        }
                        // Else:
                        else {
                            // Pop value from stack.
                            char tmp = pop(root);
                            // Add it to string.
                            *t_rpn++ = tmp;
                            *t_rpn++ = ' ';
                            // Push current element.
                            push(root, *infix);
                        }
                    }
                }
            } else {
                // If '(':
                if (*infix == '(') {
                    // Add '('.
                    push(root, *infix);
                }
                // Else:
                else {
                    // Pop elements to '('.
                    char tmp;
                    char tmp2 = root->next_node->opertr;
                    while (tmp2 != '(') {
                        tmp = pop(root);
                        // Add it to string.
                        *t_rpn++ = tmp;
                        *t_rpn++ = ' ';
                        tmp2 = root->next_node->opertr;
                    }
                    tmp = pop(root);
                }
            }
        }
    }
    while (root != NULL && root->next_node != NULL) {
        char tmp = pop(root);
        // Add it to string.
        *t_rpn++ = tmp;
        *t_rpn++ = ' ';
        // Push current element.
    }
    *t_rpn = '\0';

    free(root);

    return rpn;
}
