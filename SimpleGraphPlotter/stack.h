struct stack {
    double number;
    char x;
    struct stack *next_node;
};

#define M_PI 3.14159265358979323846

struct stack *init_s(int number);
void push_s(struct stack *root, double number, char x);
double pop_s(struct stack *root);
void destroy_s(struct stack *root);

double get_x(struct stack *root, double val);
double calculate_rpn(char *rpn, double x);

// Functioms for work with stack.
// void make_stack(struct stack *root, int size);
// void print_stack(struct stack *root);
