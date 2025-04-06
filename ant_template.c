#include <stdio.h>
#include <stdlib.h>
#define N 20

typedef struct Ant {
    int pi, pj;
    int direction;
} Ant;

int rnd(const int min, const int max) {
    return (rand() % (max - min)) + min;
}

void print_board(int** board, const int n) {
    // Wypisanie kolejnych wierszy planszy
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void print_ant(const Ant ant) {
    // Mapowanie kierunku na literę
    char directionsChar[4] = {'N', 'E', 'S', 'W'};
    char dirChar = '?';
    if (ant.direction >= 0 && ant.direction < 4) {
        dirChar = directionsChar[ant.direction];
    }
    printf("%d %d %c\n", ant.pi, ant.pj, dirChar);
}

void init_board(int*** board, const int n) {
    // Alokacja pamięci dla planszy n x n
    *board = (int**) malloc(n * sizeof(int*));
    if (*board == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        (*board)[i] = (int*) malloc(n * sizeof(int));
        if ((*board)[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    // Inicjalizacja planszy losowymi wartościami 1–8
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            (*board)[i][j] = rnd(1, 9); // losuje wartość od 1 do 8 włącznie
        }
    }
}

void free_board(int** board, const int n) {
    // Zwalnianie pamięci: najpierw wiersze, potem główny wskaźnik
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

void ant_move(int** board, const int n, Ant* ant) {
    // Kierunki: 0 = północ (N), 1 = wschód (E), 2 = południe (S), 3 = zachód (W)
    int state = board[ant->pi][ant->pj];
    switch (state) {
        case 1:
            // Stan 1: zmiana na 7, krok w przód
            board[ant->pi][ant->pj] = 7;
            if (ant->direction == 0) {            // jeśli N, idź w górę
                ant->pi = (ant->pi - 1 + n) % n;
            } else if (ant->direction == 1) {     // jeśli E, idź w prawo
                ant->pj = (ant->pj + 1) % n;
            } else if (ant->direction == 2) {     // jeśli S, idź w dół
                ant->pi = (ant->pi + 1) % n;
            } else if (ant->direction == 3) {     // jeśli W, idź w lewo
                ant->pj = (ant->pj - 1 + n) % n;
            }
            break;
        case 2:
            // Stan 2: zmiana na 4, obrót w prawo o 90°
            board[ant->pi][ant->pj] = 4;
            ant->direction = (ant->direction + 1) % 4;
            break;
        case 3:
            // Stan 3: zmiana na 2, obrót w lewo o 90°
            board[ant->pi][ant->pj] = 2;
            ant->direction = (ant->direction + 3) % 4;  // (ant->direction - 1 + 4) % 4
            break;
        case 4:
            // Stan 4: zmiana na 6, krok w prawy bok (na prawo względem aktualnego kierunku)
            board[ant->pi][ant->pj] = 6;
            {
                int rightDir = (ant->direction + 1) % 4;
                if (rightDir == 0) {
                    ant->pi = (ant->pi - 1 + n) % n;
                } else if (rightDir == 1) {
                    ant->pj = (ant->pj + 1) % n;
                } else if (rightDir == 2) {
                    ant->pi = (ant->pi + 1) % n;
                } else if (rightDir == 3) {
                    ant->pj = (ant->pj - 1 + n) % n;
                }
            }
            break;
        case 5:
            // Stan 5: zmiana na 3, krok w lewy bok (na lewo względem aktualnego kierunku)
            board[ant->pi][ant->pj] = 3;
            {
                int leftDir = (ant->direction + 3) % 4;
                if (leftDir == 0) {
                    ant->pi = (ant->pi - 1 + n) % n;
                } else if (leftDir == 1) {
                    ant->pj = (ant->pj + 1) % n;
                } else if (leftDir == 2) {
                    ant->pi = (ant->pi + 1) % n;
                } else if (leftDir == 3) {
                    ant->pj = (ant->pj - 1 + n) % n;
                }
            }
            break;
        case 6:
            // Stan 6: zmiana na 5, krok w tył (ruch przeciwny do aktualnego kierunku)
            board[ant->pi][ant->pj] = 5;
            if (ant->direction == 0) {            // jeśli N, idź w dół
                ant->pi = (ant->pi + 1) % n;
            } else if (ant->direction == 1) {     // jeśli E, idź w lewo
                ant->pj = (ant->pj - 1 + n) % n;
            } else if (ant->direction == 2) {     // jeśli S, idź w górę
                ant->pi = (ant->pi - 1 + n) % n;
            } else if (ant->direction == 3) {     // jeśli W, idź w prawo
                ant->pj = (ant->pj + 1) % n;
            }
            break;
        case 7:
            // Stan 7: zmiana na 8, w tył zwrot (obrót o 180°)
            board[ant->pi][ant->pj] = 8;
            ant->direction = (ant->direction + 2) % 4;
            break;
        case 8:
            // Stan 8: zmiana na 1, nic nie robi (brak ruchu i obrotu)
            board[ant->pi][ant->pj] = 1;
            // brak zmiany położenia ani kierunku
            break;
    }
}

void ant_simulation(int** board, const int n, Ant* ant, const int steps) {
    // Stan początkowy mrówki: [0][0], kierunek wschodni (E)
    ant->pi = 0;
    ant->pj = 0;
    ant->direction = 1;  // 1 = East (wschód)
    // Wykonaj zadaną liczbę kroków symulacji
    for (int s = 0; s < steps; s++) {
        ant_move(board, n, ant);
    }
}

int main(void) {
    int** board;
    int n, steps;
    unsigned seed;
    Ant ant;

    scanf("%d %d %d", &n, &seed, &steps);
    srand(seed);
    init_board(&board, n);
    ant_simulation(board, n, &ant, steps);
    print_board(board, n);
    print_ant(ant);
    free_board(board, n);
    return 0;
}
