#include<stdio.h>


                 int drawLine( int Lenght );
                 int drawSquare( int Lenght );
                 int drawTriangle( int Lenght );
                 int Exit( int Lenght );   
int
main(void)
{
    int  Lenght;
    char Wone, ignore; 
          
    printf("Please enter a Lenght:");
    scanf("%c%d%c",&Wone,&Lenght,&ignore );
  
        if ( Wone == 'L' || Wone == 'l' || Wone == 'S' || Wone == 's' || Wone == 'T' || Wone == 't' ){
                
                while ( Wone == 'L' || Wone == 'l' || Wone == 'S' || Wone == 's' || Wone == 'T' || Wone == 't'  ){
                if ( Wone == 'L' || Wone == 'l' )        
                    drawLine( Lenght ); printf("\n");
                    
                if ( Wone == 'S' || Wone == 's' )
                    drawSquare( Lenght );
                if ( Wone == 'T' || Wone == 't' )
                    drawTriangle ( Lenght );
                    
                    printf("Please enter a Lenght again:");
                    scanf("%c%d%c",&Wone,&Lenght,&ignore );
                    }
            }      
        else if ( Wone == 'Q' || Wone == 'q' ){
            printf("So sorry...");
            
            }
        else 
            printf("You have entered a wrong value!!!\n");
        
               
              
    return 0;
}

           int drawLine( int Lenght ){
               int i;
               for (i=1 ; i <= Lenght ; i++ )
                   printf("*");
               
               }
               
           int drawSquare( int Lenght ){
                  int i,j;
                  for (i=1 ; i <= Lenght ; i++){      
                      for (j=1 ; j <= Lenght ; j++){ 
                          printf("*");
                      }
                      printf("\n");
                          }                   
               }
           int drawTriangle( int Lenght ){
               int i, j;
               for (i=1 ; i <= Lenght ; i++ ){
                   for ( j=1 ; j <=i ; j++ ){
                         printf("*");
                         }
                         printf("\n");               
                    }
                }
            int Exit( int Lenght ){
            
            return 0;
            
            }       
                
                
