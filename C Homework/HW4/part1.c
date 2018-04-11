#include<stdio.h>

    int drawNumericPattern( int n );
    
    int drawArrowLikePattern( int height, int count, char ch );

int main( void )
{
    int select;
    int count, height , n;
    

    printf("Please enter 1 to draw numeric pattern\n");
    printf("Or enter 2 to draw arrow like pattern: ");
    scanf("%d",&select);
    if ( select == 1 ){

        printf("Please enter a number:");
        scanf("%d",&n);

        drawNumericPattern( n );

    }
    else if ( select == 2 ){
        char ch , ignore;    
        
        printf("Please enter height for figure:");
        scanf("%d",&height);
        
        scanf("%c",&ignore);
        
        printf("Please enter a character for figure 'O' or 'X':");
        scanf("%c",&ch);
        
        printf("Please enter number of figure:");
        scanf("%d",&count);
    
        drawArrowLikePattern(height, count, ch );    
        
    }
    else
        printf("Please enter valid characters and numbers\n");    
    

    return 0;
}

int drawNumericPattern( int n ){
    int i, j, l ,k;  
    
    for ( i=1; i <= n ; i++ ){  
        
        if ( i % 2 == 1 ){
            for ( j=1 ; j<=i ; j++ )
                printf( "%d",j );
        }
        else {
            for ( l=i ; l>0 ; l-- )
                printf("%d",l);
        }             
   

        k=n-i;   
        while ( k > 0  ){
            printf(" ");
            k--;
        }
       
    }
    printf("\n");
}


int drawArrowLikePattern( int height, int count, char ch ){
    int i, j, k, space, l, m;    

    for ( k=1; k <= count ; k++ ){

        for ( i=1; i<= height/2 + 1; i++ ){
            for ( j=1 ; j <= i ; j++ ){
                printf("%c",ch);
                }
                printf("\n");
                
            for ( l=1 ; l <= i ; l++ ){    
                    if ( i != height/2 + 1 ){
                    printf(" ");
                    }
                }
        }
       
         
         
               
        for ( i = height/2 ; i > 0 ; i-- ){
            for ( l=i-1 ; l > 0 ; l-- )    
                printf(" ");
            
        for ( j = i ; j > 0 ; j-- )
                printf("%c",ch);
                
            if  ( i >= 1 ){
                
                printf("\n");    
            }        
        }           

    for ( space=1 ; space <= k; space++ )
        printf(" ");
        
        
    }
}



