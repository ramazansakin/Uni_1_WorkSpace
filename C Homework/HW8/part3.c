#include<stdio.h>

int calcCombinationRec( int n, int k );

int calcCombinationIter( int n, int k );

int main( void )
{

    int n, k;
    int result;
    
    
    printf("Please enter two number to calculate their combination as C( n,k ) : ");
    fscanf(stdin,"%d%d",&n, &k);
    
    result = calcCombinationRec( n, k );
    printf("\nThe result is %d as recursively\n",result );
    
    result = calcCombinationIter( n, k );
    printf("\nThe result is %d as iteratively\n",result );

    return 0;
}

int calcCombinationRec( int n, int k )
{

    if ( k == 0 || k == n )   
        return 1;        
    
    return calcCombinationRec( n-1, k-1 ) + calcCombinationRec(n-1, k );
    
}

int calcCombinationIter( int n, int k )
{
    
    int i, limit = k;
    int numerator = 1, denominator = 1;
    if ( n == 0 )
            return 0;
    else if ( k == 0 )    
            return n;
    else{
        for ( i=0 ; i < limit; ++i  ){   
            
            numerator *= n;
            denominator *= k;
            n--;
            k--;
        
        }
    }   
    return numerator/denominator;

}


