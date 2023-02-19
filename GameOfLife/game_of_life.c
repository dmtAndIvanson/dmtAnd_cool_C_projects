#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TOPEDGE 0
#define LOWEDGE 24
#define LEFTEDGE 0
#define RIGHTEDGE 79
#define WIDTH 80
#define HEIGHT 25
#define DEAD ' '
#define ALIVE '*'

// Дима
int **input(int *y, int *x);
int receive_matrix(int **matrix, int rows, int cols);
void insertMatrix(int matrix[][WIDTH], int **insertion, int i_rows, int i_cols);
int choose_speed(int *speed);
void make_pause(int speed_mode);
void print_greeting(void);
void print_modes(void);

// Софья
void resetMatrix(int matrix[][WIDTH], int y, int x);
void output(int matrix[][WIDTH], int y, int x);
int makeStep(int old[][WIDTH], int new[][WIDTH], int y, int x);
int compareMatrix(int old[][WIDTH], int new[][WIDTH], int y, int x);
void copyMatrix(int old[][WIDTH], int new[][WIDTH], int y, int x);

// Денис
int checkNeighbours(int matrix[][WIDTH], int cell_y, int cell_x, int ifAlive);

// Командная работа
void start_game(void);

int main() {
    system("clear");
    print_greeting();
    start_game();

    return 0;
}

//____________________Софья____________________//
void resetMatrix(int matrix[][WIDTH], int y, int x) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            matrix[i][j] = 0;
        }
    }
}
void output(int matrix[][WIDTH], int y, int x) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (matrix[i][j] != 1 && ((i == TOPEDGE || i == LOWEDGE) || (j == LEFTEDGE || j == RIGHTEDGE))) {
                printf(".");
            } else {
                printf("%c", matrix[i][j] == 0 ? DEAD : ALIVE);
            }
        }
        printf("\n");
    }
}

int makeStep(int old[][WIDTH], int new[][WIDTH], int y, int x) {
    resetMatrix(new, y, x);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            new[i][j] = checkNeighbours(old, i, j, old[i][j]);
        }
    }
    int breakCond = compareMatrix(old, new, y, x);
    copyMatrix(old, new, y, x);
    return breakCond;
}

int compareMatrix(int old[][WIDTH], int new[][WIDTH], int y, int x) {
    int breakCond = 1;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (new[i][j] != old[i][j]) {
                breakCond = 0;
                break;
            }
        }
    }
    return breakCond;
}

void copyMatrix(int old[][WIDTH], int new[][WIDTH], int y, int x) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            old[i][j] = new[i][j];
        }
    }
}
//____________________Софья____________________//

//____________________Дима____________________//
int **input(int *rows, int *cols) {
    int **matrix = NULL;

    int correct_input = scanf("%d %d", rows, cols) == 2;

    if (correct_input && ((*rows > 0 && *rows <= HEIGHT) && (*cols > 0 && *cols <= WIDTH))) {
        // Allocate memory.
        matrix = malloc(sizeof(int) * *rows * *cols + sizeof(int *) * *rows);
        if (matrix != NULL) {
            // Set poinetrs.
            int *ptr = (int *)(matrix + *rows);
            for (int i = 0; i < *rows; i++) {
                *(matrix + i) = ptr + i * *cols;
            }

            // Receive matrix.
            correct_input = receive_matrix(matrix, *rows, *cols);
            if (!correct_input) {
                free(matrix);
                matrix = NULL;
            }
        }
    }
    return matrix;
}

int receive_matrix(int **matrix, int rows, int cols) {
    int return_v = 21;
    for (int i = 0; i < rows; i++) {
        // Extra check for input.
        if (!return_v) {
            break;
        }
        for (int j = 0; j < cols; j++) {
            int check = scanf("%d", *(matrix + i) + j) == 1;

            if (j == cols - 1) {
                if (!check) {
                    return_v = 0;
                    break;
                }
            } else {
                if (!check) {
                    return_v = 0;
                    break;
                }
            }

            if (matrix[i][j] != 1 && matrix[i][j] != 0) {
                return_v = 0;
                break;
            }
        }
    }
    return return_v;
}

void insertMatrix(int matrix[][WIDTH], int **insertion, int i_rows, int i_cols) {
    for (int i = 0; i < i_rows; i++) {
        for (int j = 0; j < i_cols; j++) {
            matrix[i][j] = insertion[i][j];
        }
    }
}

int choose_speed(int *speed) {
    int return_v = 0;
    int check_speed = scanf("%d", speed) == 1;
    if (check_speed && (*speed >= 1 && *speed <= 3)) {
        return_v = 21;
    }
    return return_v;
}

void make_pause(int speed_mode) {
    if (speed_mode == 1) {
        usleep(1000000);
    } else if (speed_mode == 2) {
        usleep(100000);
    } else {
        usleep(30000);
    }
}

void print_greeting(void) {
    printf("................................................................................\n");
    printf(".                                             _____  .__   .__   _____         .\n");
    printf(".     ____ _____     _____    ____     ____ _/ ____\\ |  |  |__|_/ ____\\ ____   .\n");
    printf(".    / ___\\\\__  \\   /     \\ _/ __ \\   /  _ \\\\   __\\  |  |  |  |\\   __\\_/ __ \\  .\n");
    printf(".   / /_/  >/ __ \\_|  Y Y  \\\\  ___/  (  <_> )|  |    |  |__|  | |  |  \\  ___/  .\n");
    printf(".   \\___  /(____  /|__|_|  / \\___  >  \\____/ |__|    |____/|__| |__|   \\___  > .\n");
    printf(".  /_____/      \\/       \\/      \\/                                        \\/  .\n");
    printf(".                                                                              .\n");
    printf(".                                                                              .\n");
    printf(".                  __                                  __                      .\n");
    printf(".                 |__|  ____    ______  ____ _______ _/  |_                    .\n");
    printf(".                 |  | /    \\  /  ___/_/ __ \\\\_  __ \\\\   __\\                   .\n");
    printf(".                 |  ||   |  \\ \\___ \\ \\  ___/ |  | \\/ |  |                     .\n");
    printf(".                 |__||___|  //____  > \\___  >|__|    |__|                     .\n");
    printf(".                          \\/      \\/      \\/                                  .\n");
    printf(".                           __            __                                   .\n");
    printf(".                   _______/  |_ _____  _/  |_   ____                          .\n");
    printf(".                  /  ___/\\   __\\\\__  \\ \\   __\\_/ __ \\                         .\n");
    printf(".                  \\___ \\  |  |   / __ \\_|  |  \\  ___/                         .\n");
    printf(".                 /____  > |__|  (____  /|__|   \\___  >                        .\n");
    printf(".                      \\/             \\/            \\/                         .\n");
    printf(".                                                                              .\n");
    printf(".                                                                              .\n");
    printf(".                                                                              .\n");
    printf("................................................................................\n");
}

void print_modes(void) {
    printf("................................................................................\n");
    printf(".                                       .___                                   .\n");
    printf(".       ____________    ____   ____    __| _/  /\\                              .\n");
    printf(".      /  ___/\\____ \\ _/ __ \\_/ __ \\  / __ |   \\/                              .\n");
    printf(".      \\___ \\ |  |_> >\\  ___/\\  ___/ / /_/ |   /\\                              .\n");
    printf(".     /____  >|   __/  \\___  >\\___  >\\____ |   \\/                              .\n");
    printf(".          \\/ |__|         \\/     \\/      \\/                                   .\n");
    printf(".   ____                    .__                                                .\n");
    printf(".  /_   |             ______|  |    ____ __  _  __                             .\n");
    printf(".   |   |   ______   /  ___/|  |   /  _ \\\\ \\/ \\/ /                             .\n");
    printf(".   |   |  /_____/   \\___ \\ |  |__(  <_> )\\     /                              .\\\n");
    printf(".   |___|           /____  >|____/ \\____/  \\/\\_/                               .\n");
    printf(".                        \\/                                                    .\n");
    printf(".  ________                                                     .__            .\n");
    printf(".  \\_____  \\              ____    ____ _______   _____  _____   |  |           .\n");
    printf(".   /  ____/    ______   /    \\  /  _ \\\\_  __ \\ /     \\ \\__  \\  |  |           .\n");
    printf(".  /       \\   /_____/  |   |  \\(  <_> )|  | \\/|  Y Y  \\ / __ \\_|  |__         .\n");
    printf(".  \\_______ \\           |___|  / \\____/ |__|   |__|_|  /(____  /|____/         .\n");
    printf(".          \\/                \\/                      \\/      \\/                .\n");
    printf(".  ________               _____                   __                           .\n");
    printf(".  \\_____  \\            _/ ____\\_____     _______/  |_                         .\n");
    printf(".    _(__  <    ______  \\   __\\ \\__  \\   /  ___/\\   __\\                        .\n");
    printf(".   /       \\  /_____/   |  |    / __ \\_ \\___ \\  |  |                          .\n");
    printf(".  /______  /            |__|   (____  //____  > |__|                          .\n");
    printf(".         \\/                         \\/      \\/                                .\n");
    printf("................................................................................\n");
}

void start_game(void) {
    sleep(1);
    system("clear");

    int rows, cols;
    int **matrix = input(&rows, &cols);
    if (matrix != NULL) {
        // Make two matrixes.
        int matrix1[HEIGHT][WIDTH];

        // Initialize first matrix.
        resetMatrix(matrix1, HEIGHT, WIDTH);
        insertMatrix(matrix1, matrix, rows, cols);
        free(matrix);

        system("clear");
        print_modes();
        sleep(1);

        // Choose speed mode for game.
        int speed;
        int correct_speed = choose_speed(&speed);
        system("clear");

        if (correct_speed) {
            output(matrix1, HEIGHT, WIDTH);

            int game_condition = 21;
            int matrix2[HEIGHT][WIDTH];

            // Run game.
            while (game_condition) {
                if (makeStep(matrix1, matrix2, HEIGHT, WIDTH) == 1) {
                    game_condition = 0;
                } else {
                    system("clear");
                    output(matrix1, HEIGHT, WIDTH);
                    make_pause(speed);
                }
            }
        }
    }
}
//____________________Дима____________________//

//____________________Денис____________________//
int checkNeighbours(int matrix[][WIDTH], int cell_y, int cell_x, int ifAlive) {
    int countLive = 0;
    int life = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == j && i == 0) {
                continue;
            }

            int yToCheck = i + cell_y;
            if (yToCheck < TOPEDGE) {
                yToCheck = LOWEDGE;
            }
            if (yToCheck > LOWEDGE) {
                yToCheck = TOPEDGE;
            }

            int xToCheck = j + cell_x;
            if (xToCheck < LEFTEDGE) {
                xToCheck = RIGHTEDGE;
            }
            if (xToCheck > RIGHTEDGE) {
                xToCheck = LEFTEDGE;
            }

            if (matrix[yToCheck][xToCheck] == 1) {
                countLive++;
            }
        }
    }
    if (ifAlive == 0) {
        if (countLive == 3) {
            life = 1;
        }
    } else {
        if (countLive == 2 || countLive == 3) {
            life = 1;
        }
    }
    return life;
}

//____________________Денис____________________//
