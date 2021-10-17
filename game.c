/**
 * File Name: game.c
 * Author: Yannick Brenning
 * Date: 01.09.2021
 * Description: SoSe-21 MuP2 UEB03 A2
 */

#include "game.h"
#include "highscore.h"
#include "riddles.h"

char *create_riddle(char const *const str) {
    // Memory allocation for the riddle string on the heap
    char *riddle = (char *) malloc(strlen(str) * sizeof(char));
    if (riddle == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Generating the riddle
    int i = 0;
    while (str[i] != '\0') {
        if ('A' <= str[i] && str[i] <= 'Z') riddle[i] = '*';
        else riddle[i] = str[i];
        i++;
    }

    riddle[strlen(str)] = '\0';
    return riddle;
}

int uncover_letter(char *riddle, const char *solution, char letter) {
    int j = 0, counter = 0;
    char letter_caps = toupper(letter);

    // Uncovers every instance of the letter in the solution
    while (solution[j] != '\0') {
        if (solution[j] == letter_caps) {
            if (solution[j] != riddle[j]) {
                riddle[j] = letter_caps;
                counter++;
            }
        } j++;
    }

    return counter;
}

int gaming_loop(const char *solution) {
    // Initializing values for points and riddle
    int points; char letter;
    int total_points = 0; int *ptr_total = &total_points;

    char *riddle = create_riddle(solution);
    printf("%s\n", riddle);

    while (strcmp(riddle, solution) != 0) {
        points = 100 + (100 * (rand() % 10));
        printf("--- Erreichbare Punkte: %d ---\n", points);
        printf("Buchstaben eingeben:");
        scanf(" %c", &letter);

        int correct_guesses = uncover_letter(riddle, solution, letter);
        printf("Richtige Antworten: %d\n", correct_guesses);

        // Show current riddle status
        printf("----------------\n");
        printf("%s\n", riddle);
        printf("----------------\n");

        // Calculate points
        if (correct_guesses > 0) {
            *ptr_total += (correct_guesses * points);
            printf("!!! Du hast %dP gewonnen. Gesamt: %dP !!!\n\n", points * correct_guesses, *ptr_total);
        } else if (correct_guesses == 0) {
            *ptr_total -= points;
            printf("!!! Du hast %dP verloren. Gesamt: %dP !!!\n\n", (-1) * points, *ptr_total);
        }
    }

    printf("RICHTIG!\n");
    free(riddle);
    return *ptr_total;
}

void start_game() {
    // Choosing random string from riddles.h:
    srand(time(NULL));
    char *solution = riddles[rand() % 96];

    // Enable if you want solution to be printed:
    // printf("%s\n", solution);

    // Execution of game
    int total_points = gaming_loop(solution);
    printf("\nGESAMTPUNKTE: %dP\n", total_points);

    // Logging of highscores
    HSEntry *hs_list = read_HS(HS_FILE);
    if (is_new_entry(hs_list, total_points)) {
        char name[50];
        printf("\nDu hast einen HIGHSCORE! Gebe bitte deinen Namen an:\n");
        scanf("%s", name);
        printf("Neue Highscore-Tabelle:\n");

        add_entry(hs_list, name, total_points);
        write_HS(HS_FILE, hs_list);
        print_HS(hs_list);
    } else {
        printf("Leider kein Highscore...\n");
    }

    free(hs_list);
}