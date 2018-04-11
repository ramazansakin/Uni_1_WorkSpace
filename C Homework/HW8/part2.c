#include<stdio.h>
#include<string.h>

char* strChr( char* str, char target);

char* strRChr( char* str, char target );

int main( void )
{
    
    char* strArr;
    char ch;
    int status;
    char* found;
    
    strArr = "Ramazan Sakin Computer Engineering Gebze Institue of Technology";
    
     printf("******************** The string ********************\n");
     printf("%s\n",strArr);
    
    printf("Please enter a character for searching:");
    fscanf(stdin,"%c",&ch);
    
    found = strChr( strArr, ch );
           
    if ( found == NULL )  
        printf("The character was not found!!!\n");
    else
        printf("%s\n", found);    
    
    found = strRChr( strArr, ch );
       
    if ( found == NULL )  
        printf("The character was not found!!!\n");
    else
        printf("%s\n", found);
    
    
    return 0;
}
 
char* strChr( char *str, char target)
{
    /* Finds the first target character and return its address */
    if ( str == NULL )
        return NULL;
    else if ( *str == '\0' )
        return NULL;
    if ( *str == target ) {
        return str;
    }
    else {
        strChr( ++str, target );
    } 
        
}

/* Finds the latest target character and return its address */         
char* strRChr( char* str, char target )
{
    char* address;
    
    if ( str == NULL  )
        return NULL;
        
    if ( *str == target ){
            
        address = str;  /* temps the addresses */
        printf("%s--",address);
    }
        
    if ( *str != '\0' )
        strRChr( ++str, target );    
        
    return address;  
}



