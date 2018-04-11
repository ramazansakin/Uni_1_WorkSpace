#include "source.h"

int main(){


printf("please enter a name for a horse");
scanf( "%s",horse[0].name );

horse[0].birthYear = 2007;
horse[0].speed = 70.95;

char raceName[10] ="FinalRace";
int status;
double raceLenght = 250.50;

printHorse( horse );

race = getEmptyRace( raceName, raceLenght );

status = addHorseToRace( race, binFile, "Koptagel" );

if ( status == 1 )
    printf("The horse is in the race\n");
else 
    printf("The horse is not in the race\n");    
status = addHorseToRace( race, binFile, "Ada" );
if ( status == 1 )
    printf("The horse is in the race\n");
else 
    printf("The horse is not in the race\n");
status = addHorseToRace( race, binFile, "Yatar" );
if ( status == 1 )
    printf("The horse is in the race\n");
else 
    printf("The horse is not in the race\n");

      return 0;
} 
