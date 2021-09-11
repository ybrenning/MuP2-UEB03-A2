/**
 * File Name: highscore.c
 * Author: Yannick Brenning
 * Date: 01.09.2021
 * Description: SoSe-21 MuP2 UEB03 A2
 */

#include "highscore.h"

HSEntry *read_HS(const char *filename) {
    char entry[255];

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
        }
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
    while (fgets(entry, sizeof(entry), file) != NULL) {
        if (i >= HS_SIZE) break;
        sscanf(entry, "%s - %d", list[i].name, &list[i].points);
        // printf("Just read:\t %s - %d\n", list[i].name, list[i].points);
        i++;
    }

    // Replacing leftover empty entries
    if (i < HS_SIZE) {
        for (i; i < HS_SIZE; i++) {
            strcpy(list[i].name, "");
            list[i].points = 0;
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

    for (int j = 0; j < HS_SIZE; j++) {
        fprintf(file, "%s - %d\n", list[j].name, list[j].points);
    }

}

bool is_new_entry(const HSEntry *list, int points) {
    int k = 0;
    while (strcmp(list[k].name, "") != 0) {
        k++;
    }
    k--;
    if (list[k].points < points) {
        return true;
    } else return false;
}

int compare_entries(const void *entry_1, const void *entry_2) {
    HSEntry *e1 = (HSEntry *) entry_1;
    HSEntry *e2 = (HSEntry *) entry_2;
    return (e2->points - e1->points);
}

void add_entry(HSEntry *list, const char *name, int points) {
    if (is_new_entry(list, points)) {
        int l = 0;
        while (strcmp(list[l + 1].name, "") != 0) {
            l++;
        }
        if (l == HS_SIZE) {
            l--;
        }
        strcpy(list[l].name, name);
        list[l].points = points;
    }
    qsort(list, HS_SIZE, sizeof(HSEntry), compare_entries);
}

void print_HS(const HSEntry *list) {
    for (int m = 0; m < HS_SIZE; m++){
        printf("Name: %s --- Points: %d\n", list[m].name, list[m].points);
    }
}