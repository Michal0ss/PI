#include <stdio.h>
#include <stdlib.h>
#define N 20

int cnt[2];
char filler = '_';

int rnd(const int min, const int max) {
    return (rand() % (max - min)) + min;
}

void print(char board[][N], const int n) {
}

void start(char board[][N], const int n) {
}

int move(char board[][N], const int i, const int j, const int n) {
}

int capture(char board[][N], const int i, const int j, const int n) {
}


int main(void) {
    char board[N][N];
    int n, steps;
    unsigned seed;
    scanf("%d %u %d", &n, &seed, &steps);
    srand(seed);
    cnt[0] = cnt[1] = 2 * n;
    start(board, n);
    for (int i = 0; i < steps; i++) {
        int ix, iy;
        const char turn = (i % 2 == 0) ? '1' : '2';
        do {
            ix = rnd(0, n);
            iy = rnd(0, n);
        } while (board[ix][iy] != turn);
        if (!capture(board, ix, iy, n)) {
            move(board, ix, iy, n);
        }
    }
    print(board, n);
    printf("%d %d\n", cnt[0], cnt[1]);

    return 0;
}

