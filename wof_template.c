#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTS 20

int guess_a_letter(char* text, const char* original_text) {
    char guessed_letter = 'A' + rand() % 26;
    int found = 0;
    for (int i = 0; original_text[i] != '\0'; i++) {
        if (original_text[i] == guessed_letter && text[i] == '_') {
            text[i] = guessed_letter;
            found = 1;
        }
    }
    return found;
}

int is_fully_revealed(const char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '_') return 0;
    }
    return 1;
}

char* play(const char* original_text, const int number_of_players, const int turns, int* p_player) {
    int len = strlen(original_text);
    char* current_text = malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++) {
        current_text[i] = (original_text[i] == ' ') ? ' ' : '_';
    }
    current_text[len] = '\0';

    int player = 0;
    for (int i = 0; i < turns; i++) {
        *p_player = player;
        if (guess_a_letter(current_text, original_text)) {
            if (is_fully_revealed(current_text)) break;
            i--; // stay on same player
        } else {
            player = (player + 1) % number_of_players;
        }
    }

    return current_text;
}

int main() {
    const char* texts[MAX_TEXTS] = {
        "PAN TADEUSZ",
        "HENRYK SIENKIEWICZ",
        "MORZE KASPIJSKIE",
        "POGODA DLA BOGACZY",
        "CZERWONE GITARY",
        "KAZANIE PIOTRA SKARGI",
        "QUO VADIS",
        "ADAM MICKIEWICZ",
        "ALBERT EINSTEIN",
        "DENNIS RITCHIE",
        "FIZYKA KWANTOWA",
        "PROGRAMOWANIE IMPERATYWNE",
        "ALGORYTMY I STRUKTURY DANYCH",
        "BRIAN KERNIGHAN",
        "CZERWONY KAPTUREK",
        "MARIA KONOPNICKA",
        "WILLIAM SHAKESPEARE",
        "ZBIGNIEW ZAPASIEWICZ",
        "MAGDALENA SAMOZWANIEC",
        "JEZIORO ONTARIO"
    };

    int number_of_players, turns, player;
    unsigned seed;

    scanf("%d %u %d", &number_of_players, &seed, &turns);
    srand(seed);
    const int number = rand() % MAX_TEXTS;
    char* text = play(texts[number], number_of_players, turns, &player);
    printf("%s\n", text);
    printf("%d\n", player);
    free(text);

    return 0;
}
