#ifndef RACE_H
#define RACE_H

#include<stdio.h>
#include<string.h>

typedef struct{
    char name[20];
    int birthYear;     
    double speed;

}horse_t;

typedef struct{
    char name[20];
    horse_t horses[20];
    int numberOfHorses;
    double lenghtOfRace;
    int isRaceHappenned;

}race_t;

race_t race;
horse_t horse[2];
FILE*binFile;



void printHorse( const horse_t* horse );

race_t getEmptyRace( char racename[], double raceLenght );

int addHorseToRace( race_t *race, FILE* binFile, const char horseName[] );

int printRaceInformation( const race_t* race );

#endif


