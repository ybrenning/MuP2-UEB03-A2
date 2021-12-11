/**
 * @file game.h
 * @author Yannick Brenning
 * @date 01.09.2021
 * @brief Header file for the main game
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

char *create_riddle(char const *const str);
int uncover_letter(char *riddle, const char *solution, char letter);
int gaming_loop(const char *solution);
void start_game();

#endif //GAME_H