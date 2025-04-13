#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTS 20

int guess_a_letter(char* text, const char* original_text) {
    // Losowanie litery od 'A' do 'Z'
    char letter = 'A' + rand() % 26;
    int found = 0;
    
    // Sprawdzenie czy litera występuje w oryginalnym tekście i nie została jeszcze odkryta
    for (int i = 0; original_text[i] != '\0'; i++) {
        if (original_text[i] == letter && text[i] == '_') {
            text[i] = letter;
            found = 1;
        }
    }
    
    return found;
}

char* play(const char* original_text, const int number_of_players, const int turns, int* p_player) {
    // Inicjalizacja zakrytego tekstu
    int length = strlen(original_text);
    char* text = (char*)malloc((length + 1) * sizeof(char));
    
    for (int i = 0; i < length; i++) {
        if (original_text[i] == ' ') {
            text[i] = ' ';
        } else {
            text[i] = '_';
        }
    }
    text[length] = '\0';
    
    *p_player = 0; // Rozpoczyna gracz 0
    int rounds_played = 0;
    int game_over = 0;
    
    while (rounds_played < turns && !game_over) {
        int result = guess_a_letter(text, original_text);
        
        // Sprawdzenie czy całe hasło zostało odgadnięte
        game_over = 1;
        for (int i = 0; i < length; i++) {
            if (original_text[i] != ' ' && text[i] == '_') {
                game_over = 0;
                break;
            }
        }
        
        if (!result || game_over) {
            // Zmiana gracza tylko jeśli litera nie została znaleziona lub gra się zakończyła
            *p_player = (*p_player + 1) % number_of_players;
        }
        
        if (!game_over) {
            rounds_played++;
        }
    }
    
    return text;
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