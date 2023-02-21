/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"

// colors
#define BYEL "\e[1;93m"
#define BLUB "\e[44m"
#define reset "\e[0m"
#define BRED "\e[1;31m"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
    // loop through each players
    for (int i=0; i<num_players; i++)
    {
        // if player was found
        if (strcmp(players[i].name, name) == 0)
        {
            return true;
        }
    }

    // if player was not found
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, int num_players, char *name, int score)
{
    // loop through each players
    for (int i=0; i<num_players; i++)
    {
        // if player was found
        if (strcmp(players[i].name, name) == 0)
        {
            players[i].score += score;
            return;
        }
    }

    // if player was not found
    printf("Player name was not found\n");
}

// prints each players name and current score
void print_score(player *players, int num_players)
{
    printf("\n%s                                   %s\n", BLUB, reset);
    printf("%s %s %sPLAYER\t\tPOINTS   %s %s %s\n", BLUB, reset, BYEL, reset, BLUB, reset);
    printf("%s %s %s-------------------------------%s %s %s\n", BLUB, reset, BYEL, reset, BLUB, reset);
    
    // loop through each players
    for (int i=0; i<num_players; i++)
    {
        // format output
        if (players[i].score == 0)
        {
            printf("%s %s %s%s\t\t$ %d%s               %s %s\n", BLUB, reset, BYEL, players[i].name, players[i].score, reset, BLUB, reset);
        }
        else
        {
            printf("%s %s %s%s\t\t$ %d%s             %s %s\n", BLUB, reset, BYEL, players[i].name, players[i].score, reset, BLUB, reset);\
        }
    }

    printf("%s                                   %s\n", BLUB, reset);
}