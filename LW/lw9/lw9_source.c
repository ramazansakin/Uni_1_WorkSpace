#include "source.h"


void printHorse( const horse_t* horse )
{
    
    printf("name:%s birthyear:%d speed:%.2f\n", horse[0].name, horse[0].birthYear, horse[0].speed);                 

}


race_t getEmptyRace( char racename[], double raceLenght )
{

    race_t racee;
    
    printf("Please enter a race name >>");
    scanf("%s", racee.name);    
    racee.lenghtOfRace = raceLenght;
    
    
    return racee;

}

int addHorseToRace( race_t *race, const char nameOfHorseDB[], const char horseName[] )
{
    
    binFile = fopen( "horses.bin","rb" );
    race_t racee;

    fread( racee , sizeof(race_t), 1, inFile );
    
    if ( strcmp( racee.name, horseName ) == 0  )
        return 1;
    else 
        return 0;

}

