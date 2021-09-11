#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define HS_SIZE 10
#define HS_FILE "highscores.txt"

typedef struct {
    char name[20];
    int32_t points;
} HSEntry;

HSEntry *read_HS(const char *filename);
void write_HS(const char *filename, const HSEntry *list);
bool is_new_entry(const HSEntry *list, int points);
void add_entry(HSEntry *list, const char *name, int points);
void print_HS(const HSEntry *list);

#endif //HIGHSCORE_H
