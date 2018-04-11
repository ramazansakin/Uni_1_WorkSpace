#include<stdio.h>
#include<string.h>

char sortStrings( char strArr[][20] , int sizeR );

int main( void )
{
    char strArr[][20]={ "ramazan","sakin","gyte","CompEng", "smdbasnsdfads", "sadsadfsdf", "asdasd" };     
    int size =7, i;    
    char temp[20];
    
    sortStrings( strArr , size );
    
    for ( i=0 ; i < size ; i++ )
        printf("%s\n", strArr[i]);
    
    return 0;

}


char sortStrings( char strArr[][20] , int sizeR )
{

    int i, j=0;
    char temp[20];
    
    for ( j=0 ; j< sizeR ; j++ )
    for ( i=0 ; i< sizeR -1 ; ++i ){
      
        
        
        if ( strlen( strArr[i+1] ) > strlen( strArr[i] ) ){
            
            strcpy( temp, strArr[i] );
            strcpy( strArr[i], strArr[i+1] );        
            strcpy( strArr[i+1], temp );
        }
    }

}



