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
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4
const char *DELIMITER = " \n\t\a\r";

// colors
#define BGRN "\e[1;32m"
#define BRED "\e[1;31m"
#define BYEL "\e[1;93m"
#define WHTB "\e[47m"
#define reset "\e[0m"

// print welcome message
void init(void)
{
    FILE *fptr = fopen("welcome.txt", "r"); // input file
    char buf[1024];                         // buffer
 
    // error management
    if (fptr == NULL)
    {
        printf("error opening welcome file\n");
        return;
    }
 
    // print welcome message
    printf("--------------------------------------------------------------\n");
    while(fgets(buf,sizeof(buf),fptr) != NULL)
    {
        printf("%s",buf);
    }
    printf("--------------------------------------------------------------\n\n\n");

    // close pointer
    fclose(fptr);                                            
}

// counts the number of tokens
int count_tokens(char *cmd)
{
    char *cmd_copy = NULL;     // stores command
    cmd_copy = malloc(256+1); // allocate memory

    // error management
    if (!cmd_copy)
    {
        printf("%sError: Failed to Allocate Memory.%s\n", BRED, reset);
        return 0;
    }

    // copy command
    strcpy(cmd_copy, cmd);

    int token_count = 0;                       // holds number of tokens
    char *token = strtok(cmd_copy, DELIMITER); // first token
    token_count++;                             // increment counter

    // determine number of tokens
    while (token != NULL)
    {
        token_count ++;
        token = strtok(NULL, DELIMITER);
    }

    // free pointer
    free(token);

    // return count
    return token_count;
}

// tokenize command by whitespace
char **parse_cmd(char *cmd)
{
    // holds number of tokens
    int token_count = count_tokens(cmd);

    char **tokens = NULL;                          // stores tokens
    tokens = malloc(sizeof(char *) * token_count); // allocate memory

    // error management
    if (!tokens)
    {
        printf("%sError: Failed to Allocate Memory.%s\n", BRED, reset);
        return NULL;
    }

    // get first token
    char *token = strtok(cmd, DELIMITER);

    // store all tokens
    int i;
    for (i = 0; token != NULL; i++)
    {
        tokens[i] = malloc(sizeof(char) * strlen(token)); // allocate space
        strcpy(tokens[i], token);                         // copy token
        token = strtok(NULL, DELIMITER);                  // get next token
    }

    tokens[i] = NULL; // null terminate the array

    // return all tokens
    return tokens;
}

int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS] = {
        {"null", 0},
        {"null", 0},
        {"null", 0},
        {"null", 0},
    };
    
    // Display the game introduction and initialize the questions
    init();

    // Prompt for players names
    for(int i = 0; i < 4; i++)
    {
        // initialize each of the players in the array
        printf("%sEnter Player Name:%s ", BGRN, reset);
        scanf("%s", players[i].name);
    }

    // Perform an infinite loop getting command input from users until game ends
    while (finished() == false)
    {
        char *answer[MAX_LEN];
        char cur_player[MAX_LEN];
        char cur_category[MAX_LEN];
        int cur_price;

        // print catagories
        display_categories();

        // pick a player
        do
        {
            printf("%sWhich Player will be Selecting a Category? %s", BGRN, reset);
            scanf("%s", cur_player);
            if (player_exists(players, NUM_PLAYERS, cur_player) == false)
            {
                printf("%serror: name not found%s\n\n", BRED, reset);
            }
            //validate player
        } while (player_exists(players, NUM_PLAYERS, cur_player)  == false);
        printf("%s%s, Will be Selecting.%s\n\n", BYEL, cur_player, reset);

        // pick a category and price
        do
        {
            printf("%sPlease Pick a Category. %s", BGRN, reset);
            scanf("%s", cur_category);

            printf("%sGreat choice! Now please pick a price. %s", BGRN, reset);
            scanf("%d", &cur_price);

            if (already_answered(cur_category, cur_price) == true)
            {
                printf("%sError, Please Try Again\n\n%s", BRED, reset);
            }
            else
            {
                printf("%sQuestion Successfuly Selected\n%s", BYEL, reset);
            }
            //validate question
        } while (already_answered(cur_category, cur_price) == true);

        // display question
        display_question(cur_category, cur_price);

        // get answer
        printf("%sPlease Enter Your Answer. %s", BGRN, reset);
        getchar();
        fgets((char *)answer, MAX_LEN, stdin);

        // tokenize answer
        char **tokens = parse_cmd(answer);

        // check answer
        if (strcmp(tokens[0], "who") == 0 || strcmp(tokens[0], "what") == 0)
        {
            if (strcmp(tokens[1], "is") == 0)
            {
                // if in proper format and correct
                if (valid_answer(cur_category, cur_price, tokens[2]) == true)
                {
                    printf("%sCorrect! You are Awarded %d Dollars!%s\n", BYEL, cur_price, reset);
                    update_score(players, NUM_PLAYERS, cur_player, cur_price);
                    answer_question(cur_category, cur_price);
                }
                // if in proper format but incorrect
                else
                {
                    printf("%sWrong! No points awarded.%s\n", BYEL, reset);
                    answer_question(cur_category, cur_price);
                }
            }
        }
        // incorrect format
        else
        {
            printf("%sWrong! No points awarded.%s\n", BYEL, reset);
            answer_question(cur_category, cur_price);
        }

        // wait until enter is pressed to move to next iteration
        printf("\n%s%sPress Enter to Continue.%s", WHTB, BRED, reset);
    
        // wait for enter
        while(getchar() != '\n')
        {
            getchar();
        }

        system("clear");
    }

    // print points
    printf("%sGame Finished! Printing Scores.%s\n\n", BGRN, reset);
    print_score(players, NUM_PLAYERS);
    printf("\n\nProgram Execution Finished\n");

    return EXIT_SUCCESS;
}
