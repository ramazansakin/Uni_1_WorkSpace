#include<stdio.h>
#include<stdlib.h>

#define NR 23
#define NC 80

int drawLine( int x1, int x2, int y1, int y2, char buf[][NC] );
    
void clear( char buf[][NC] );
    
void showPattern( char buf[][NC] );

int main(void) 
{

	int x1, x2 ,y1,y2;
	char buf[NR][NC];

    clear( buf );
    
    x1 = 2; 
    y1 = 0;
    x2 = 6; 
    y2 = 0;
    
    drawLine( x1, x2, y1, y2, buf );
    x1 = 2; 
    y1 = 1;
    x2 = 2; 
    y2 = 7;
    
    drawLine( x1, x2, y1, y2, buf );
    
    x1 = 0; 
    y1 = 8;
    x2 = 1; 
    y2 = 8;
    
    drawLine( x1, x2, y1, y2, buf );
    
    x1 = 1; 
    y1 = 9;
    x2 = 3; 
    y2 = 11;
    
    drawLine( x1, x2, y1, y2, buf );
    
    x1 = 4; 
    y1 = 12;
    x2 = 7; 
    y2 = 9;
    
    drawLine( x1, x2, y1, y2, buf );
    
    x1 = 7; 
    y1 = 8;
    x2 = 8; 
    y2 = 8;
    
    drawLine( x1, x2, y1, y2, buf );
    
    x1 = 6; 
    y1 = 0;
    x2 = 6; 
    y2 = 7;
    
    drawLine( x1, x2, y1, y2, buf );


    showPattern( buf );
    printf("\n");

    return 0;
}   

void clear( char buf[][NC] )
{
    int i, j;
    for ( i=0; i<NR ; i++ ){
        for ( j=0; j<NC ; j++ )
            buf[i][j]=' ';
        
    }

}
int drawLine( int x1, int x2, int y1, int y2, char buf[][NC] )
{
    int i, j, k;
  
    if ( x1 == x2 && y1 != y2 ){
        for ( i =y1 ; i <= y2 ; ++i )
            buf[x1][i] = '*';
        
    }
    
        
    
   if ( y1 == y2 && x1 != x2 ) {
        
        for ( i = x1 ; i <=x2 ; ++i )
            buf[i][y1] = '*';
      
    }      
   

    if ( abs( x1-x2 ) == abs( y1-y2 ) && y2 > y1 && x1 != y1 ){
        for ( i=0 ; i <= abs( x1 -x2 ) ; ++i )
            buf[x1+i][y1+i] = '*';   
  
        
    }
    

     if ( abs( x1-x2 ) == abs( y1-y2 ) && y1 > y2 && x1 != y1 ){
        for ( i=0 ; i <= abs( x1 -x2 ) ; ++i )
            buf[x1+i][y1-i] = '*';    
    
    
    }
   
    
    
    /* draw Square */
    if ( x1 == y1 && x2 == y2  ){
        for ( k=1; k < 3; k++ ){
            for ( i =0 ; i < abs(x1-x2); i++ ) 
                for ( j=0 ;j < abs(y1-y2); j++ ) 
                    buf[x1+i][y1+j] = '*';
    
            for ( i =0 ; i < abs (x1-x2)-1 ; i++ ) 
                for ( j=0 ;j < abs(y1-y2)-1 ; j++ ) 
                    buf[x2+i][y2+j] = '*';
            
            y1+=2*abs(y1-y2);
            y2+=2*abs(y1-y2);
            
            for ( i =0 ; i < abs(x1-x2); i++ ) 
                for ( j=0 ;j < abs(y1-y2); j++ ) 
                    buf[x1+i][y1+j] = '*';         
        
    }
    
    }
}

void showPattern( char buf[][NC] )
{
    int i, j;
        for (i=0; i< NR ; ++i  )
            for ( j=0; j<NC ; ++j )
                printf("%c",buf[i][j]);
                
}


    
