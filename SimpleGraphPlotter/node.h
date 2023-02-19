char *get_string(int *len);

struct node {
    int prior;
    char opertr;
    struct node *next_node;
};

struct node *init(void);
void push(struct node *root, char opertr);
char pop(struct node *root);
void destroy(struct node *root);

int get_prior(char opertr);
char *make_rpn(char *infix);