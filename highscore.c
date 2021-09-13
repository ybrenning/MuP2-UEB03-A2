/**
 * File Name: highscore.c
 * Author: Yannick Brenning
 * Date: 01.09.2021
 * Description: SoSe-21 MuP2 UEB03 A2
 */

#include "highscore.h"

HSEntry *read_HS(const char *filename) {
    char line[255];

    // Allocating memory for HSEntries and corresponding error handling
    HSEntry *list = (HSEntry *) malloc(HS_SIZE * sizeof(HSEntry));
    if (list == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    FILE *file = fopen(filename, "r");
    // Error handling for nonexistent file
    if (file == NULL) {
        for (int i = 0; i < HS_SIZE; i++) {
            strcpy(list[i].name, "");
            list[i].points = 0;
        } fopen("highscores.txt", "ab");

        return list;
    }

    // Error handling for empty file
    int c = fgetc(file);
    if (c == EOF) {
        for (int i = 0; i < HS_SIZE; i++) {
            strcpy(list[i].name, "");
            list[i].points = 0;
        }

        return list;
    } ungetc(c, file);

    // Reading entries from file
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (i >= HS_SIZE) break;
        sscanf(line, "%*u %s %d", list[i].name, &list[i].points);
        i++;
    }

    // Replacing leftover empty entries
    if (i < HS_SIZE) {
        for (int j = i; j < HS_SIZE; j++) {
            strcpy(list[j].name, "");
            list[j].points = 0;
        }
    }

    fclose(file);
    return list;
}

void write_HS(const char *filename, const HSEntry *list) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error occurred while opening file.\n");
        exit(1);
    }

    int i = 0;
    while (i < HS_SIZE && strcmp(list[i].name, "") != 0) {
        fprintf(file, "%-5d %-25s %10d\n", i + 1, list[i].name, list[i].points);
        i++;
    }
}

bool is_new_entry(const HSEntry *list, int points) {
    int i = 0;
    while (strcmp(list[i].name, "") != 0) {
        i++;
    } i--;
    if (list[i].points < points) {
        return true;
    } else return false;
}

int compare_entries(const void *entry_1, const void *entry_2) {
    // Comparison function for the quicksort algorithm
    HSEntry *e1 = (HSEntry *) entry_1;
    HSEntry *e2 = (HSEntry *) entry_2;
    return (e2->points - e1->points);
}

void add_entry(HSEntry *list, const char *name, int points) {
    if (is_new_entry(list, points)) {
        int i = 0;
        while (strcmp(list[i + 1].name, "") != 0) i++;
        if (i == HS_SIZE) i--;

        strcpy(list[i].name, name);
        list[i].points = points;
    }

    qsort(list, HS_SIZE, sizeof(HSEntry), compare_entries);
}

void print_HS(const HSEntry *list) {
    int i = 0;
    while (i < HS_SIZE && strcmp(list[i].name, "") != 0) {
        printf("%-5d %-25s %10d\n", i + 1, list[i].name, list[i].points);
        i++;
    }
}