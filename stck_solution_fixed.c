#include <stdio.h>

#define STACK_SIZE 10
#define QUEUE_SIZE 10
#define CBUFF_SIZE 10

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

// Stack
int stack[STACK_SIZE];
int top = 0;

int stack_push(int x) {
    if (top >= STACK_SIZE) return OVERFLOW;
    stack[top++] = x;
    return OK;
}

int stack_pop(void) {
    if (top == 0) return UNDERFLOW;
    return stack[--top];
}

int stack_state(void) {
    return top;
}

// FIFO queue with shifts
int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

int queue_push(int in_nr) {
    int space = QUEUE_SIZE - in;
    for (int i = 0; i < in_nr; i++) {
        curr_nr++;
        if (i < space) {
            queue[in++] = curr_nr;
        }
    }
    return (in_nr > space) ? OVERFLOW : OK;
}

int queue_pop(int out_nr) {
    if (out_nr > in) return UNDERFLOW;
    for (int i = 0; i < in - out_nr; i++) {
        queue[i] = queue[i + out_nr];
    }
    in -= out_nr;
    return in;
}

int queue_state(void) {
    return in;
}

void queue_print(void) {
    for (int i = 0; i < in; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

// Queue with cyclic buffer
int cbuff[CBUFF_SIZE];
int out = 0, len = 0;

int cbuff_push(int cli_nr) {
    if (len >= CBUFF_SIZE) return OVERFLOW;
    int idx = (out + len) % CBUFF_SIZE;
    cbuff[idx] = cli_nr;
    len++;
    return OK;
}

int cbuff_pop(void) {
    if (len == 0) return UNDERFLOW;
    int val = cbuff[out];
    out = (out + 1) % CBUFF_SIZE;
    len--;
    return val;
}

int cbuff_state(void) {
    return len;
}

void cbuff_print(void) {
    for (int i = 0; i < len; i++) {
        int idx = (out + i) % CBUFF_SIZE;
        printf("%d ", cbuff[idx]);
    }
    printf("\n");
}

int main(void) {
    int to_do, n, client_no, answer;
    scanf("%d", &to_do);
    switch(to_do) {
        case 1: // stack
            do {
                scanf("%d", &n);
                if (n > 0) {
                    if ((answer = stack_push(n)) < 0) printf("%d ", answer);
                } else if (n < 0) {
                    printf("%d ", stack_pop());
                } else printf("\n%d\n", stack_state());
            } while(n != 0);
            break;
        case 2: // FIFO queue with shifts
            do {
                scanf("%d", &n);
                if (n > 0) {
                    if ((answer = queue_push(n)) < 0) printf("%d ", answer);
                } else if (n < 0) {
                    if ((answer = queue_pop(-n)) < 0) printf("%d ", answer);
                } else {
                    printf("\n%d\n", queue_state());
                    queue_print();
                }
            } while(n != 0);
            break;
        case 3: // queue with cyclic buffer
            client_no = 0;
            do {
                scanf("%d", &n);
                if (n > 0) {
                    if ((answer = cbuff_push(++client_no)) < 0) printf("%d ", answer);
                } else if (n < 0) {
                    printf("%d ", cbuff_pop());
                } else {
                    printf("\n%d\n", cbuff_state());
                    cbuff_print();
                }
            } while(n != 0);
            break;
        default: 
            printf("NOTHING TO DO!\n");
    }
    return 0;
}
