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
#include "questions.h"

// colors
#define BYEL "\e[1;93m"
#define BLUB "\e[44m"
#define reset "\e[0m"
#define BRED "\e[1;31m"

// Questions struct for each question
typedef struct {
    char category[MAX_LEN];
    char question[MAX_LEN];
    char answer[MAX_LEN];
    int value;
    bool answered;
} question;

// An array of 12 questions (4 for each category), initialized in initialize_game
// this may need to be a pointer if you want it set dynamically
question questions[NUM_QUESTIONS] = {
    {"Science", "Common Gas Represented by the Formula CO2", "carbondioxide", 100, false}, 
    {"Science", "In Magnetism, 'Like' (or same) Poles do This", "repel", 200, false}, 
    {"Science", "Measuring System Established in France in 1790, Called Originally Systeme Internationale", "metricsystem", 300, false}, 
    {"Science", "What Topic is This?", "science", 400, false}, 
    
    {"Military", "Members of all Nationalities Except French can Join This Fighting Force", "foreignlegion", 100, false}, 
    {"Military", "Name of the Air Arm of the German Military", "luftwaffe", 200, false}, 
    {"Military", "The U.S. Air Force was Part of the Army Until ...", "1946", 300, false}, 
    {"Military", "What Topic is This?", "military", 400, false}, 

    {"Mountains", "Mt. Logan was Thought the Highest on this Continent till Someone Measured Mt. McKinley", "northamerica", 100, false}, 
    {"Mountains", "Different Surveys have Reported its Height as 29,002, 29,141 and 29,028 feet", "mounteverest", 200, false}, 
    {"Mountains", "A Mountain Chain in the Sahara Bears the Name of this Mythical man who Bears the World", "atlas", 300, false}, 
    {"Mountains", "What Topic is This?", "mountains", 400, false},
};

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    printf("\n%s                                   %s\n", BLUB, reset);
    printf("%s %s %sCATEGORY\t\tVALUE    %s %s %s\n", BLUB, reset, BYEL, reset, BLUB, reset);
    printf("%s %s %s-------------------------------%s %s %s\n", BLUB, reset, BYEL, reset, BLUB, reset);

    // loop all over questions
    for (int i=0; i<NUM_QUESTIONS; i++)
    {
        // if question has not been answered
        if (questions[i].answered == false)
        {
            // output category and price
            printf("%s %s %s%s\t\t$ %d%s     %s %s\n", BLUB, reset, BYEL, questions[i].category, questions[i].value, reset, BLUB, reset);
        }
    }
    printf("%s                                   %s\n\n", BLUB, reset);
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    bool found = false;

    // loop all over questions
    for (int i=0; i<NUM_QUESTIONS; i++)
    {
        // if question was found
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            printf("\n");
            printf("%sQuestion:%s %s\n", BYEL, reset, questions[i].question);
            printf("\n");
            found = true;
            break;
        }
    }

    // if question wasnt found
    if (found == false)
    {
        printf("\n");
        printf("%sQuestion could not be found%s\n", BRED, reset);
        printf("\n");
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    bool found = false;

    // loop all over questions
    for (int i=0; i<NUM_QUESTIONS; i++)
    {
        // if question was found
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            // if answer was correct
            if (strcmp(questions[i].answer, answer) == 0)
            {
                return true;
            }
            // if answer was wrong
            else
            {
                return false;
            }

            found = true;
            break;
        }
    }

    // if question wasnt found
    if (found == false)
    {
        return false;
    }

    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
	for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (questions[i].value == value && strcmp(questions[i].category, category) == 0)
        {
            return questions[i].answered;
        }
    }

    return true;
}

// Returns true if all questions have been answered
bool finished()
{
    // go through each question
    for (int i=0; i<NUM_QUESTIONS; i++)
    {
        // if question has been not answered
        if (questions[i].answered == false)
        {
            return false;
        }
    }

    // if all questions have been answered
    return true;
}

// Displays the question for the category and dollar value
void answer_question(char *category, int value)
{
    // loop all over questions
    for (int i=0; i<NUM_QUESTIONS; i++)
    {
        // if question was found
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            questions[i].answered=true;
            break;
        }
    }
}