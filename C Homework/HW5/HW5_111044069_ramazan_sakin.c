/*##############################################################################
/*                      111044069--created by Ramazan SAKİN                    #
/******************************************************************************#
/*  This program reads values from console and calculates addition             # 
/*  subtraction, division, multiplication or read from txt file and calculates #
/*  them or calculates pi and writes results to console as S_I_F               # 
/*  takes S_I_F  from console and writes to console as real number             # 
/*                                                                             #
/*############################################################################*/

#include <stdio.h>
#include<math.h>        /* to use pow function */
#include<stdlib.h>      /* to use abs function */
#define PI   22/7


                        /***   Function Prototypes   ***/
    char convertToInt( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2  );
    
    void convertToDouble( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 );
    
    void additionFunc( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 );
    
    void subtractionFunc( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 );
    
    void divisionFunc( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 );

    void multiplicationFunc( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 );

    void selectEquationforOp( char operator, int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 );
    
    void calculatePI( int number );
    
    void readOpFromFile( char operator, int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 );
    
    void readConasSIFwriteReal( void );
    
    
    
    /* determining the new type */
    
    typedef enum
    { addition ,subtraction ,division , multiplication }
    op_t;


int main(void)
{

int ip1, ip2, sp1, sp2, fp1, fp2 ;  /* pointers for outputs */
int selection1, selection2 ;
char operator;                      /* takes the operator */
int number;                         /* for calculating pi */
op_t op;                            /* new type */


    printf("Please enter a number for selection\n");
    printf("1.Converting doubles or integers and Calculate\n");
    printf("2.getOperator and Calculate\n");
    printf("3.Calculating PI\n");
    printf("4.Read from file and Calculate\n");
    printf("5.Read Console as SIF and write as Real number\n");
    printf("Your Selection: ");    
    
    scanf("%d",&selection1);

    if ( selection1 == 1 ){
    
    convertToInt( &ip1, &ip2, &sp1, &sp2, &fp1, &fp2 );

    printf("Please enter a number for selection to calculate the result that you want \n");
    printf("1.Addition\n");
    printf("2.Subtraction\n");
    printf("3.Division\n");
    printf("4.Multiplication\n");
    printf("Your selection: ");
    
    scanf("%d",&selection2);


    if ( selection2 == 1 )
        additionFunc( &ip1, &ip2, &sp1, &sp2, &fp1, &fp2 );
    else if ( selection2 == 2 )   
        subtractionFunc( &ip1, &ip2, &sp1, &sp2, &fp1, &fp2 );
    else if ( selection2 == 3 )    
        divisionFunc( &ip1, &ip2, &sp1, &sp2, &fp1, &fp2 );
    else if ( selection2 == 4 )
        multiplicationFunc( &ip1, &ip2, &sp1, &sp2, &fp1, &fp2 );
    
    }
    else if ( selection1 == 2 ){
   
    operator=convertToInt( &ip1, &ip2, &sp1, &sp2, &fp1, &fp2 );
    
    selectEquationforOp( operator, &ip1, &ip2, &sp1, &sp2, &fp1, &fp2 );
    
    }
    else if ( selection1 == 3 ){
        
        printf("Enter a number to calculate pi : ");
        scanf("%d",&number);
        
        calculatePI( number );
        
    
    }
    else if( selection1 == 4 ){
        
        readOpFromFile( operator, &ip1, &ip2, &sp1, &sp2, &fp1, &fp2 );
    
    }
    else if( selection1 == 5 ){
        
        readConasSIFwriteReal(  );
    
    }
    else
        printf("Please enter valid number for selection!!!\n");
    
    
    return 0;

}


char convertToInt( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2  )
{
    char comma, ch, operator;
    int  frac1=0, integer1, sign1;
    int  frac2=0, integer2, sign2;
    int i, j, n, status, chr, frac;
    


    printf("Please enter two doubles:\n");
    printf("It should have most 8 digits as 4d,4d with comma:");

    for ( n=1 ; n <= 2 ; n++ ){
        
        
        if ( n == 1 )
            scanf("%d",&integer1);
        else
            scanf("%d",&integer2);
    
        if ( n == 1 ){
            if ( integer1 < 0 )
                sign1=-1;
            else
                sign1=1;
            
        }
        else if ( n == 2 )  {
        
        if ( integer2 < 0 )
                sign2=-1;
            else
                sign2=1;
        
        }
      
        scanf("%c",&comma);
        
        if ( comma != ',' )
            printf("Please enter valid doubles!!\n");
        
            
            
        for ( i=4 ; i >= 1 ; i-- ){
                    
            status= scanf("%c",&ch);
             
            if ( status == EOF || ch == '\n' || ch == ' ' )
                break;
            
            if ( n == 1 ){
            
                operator='-';
                
                if ( ch == '+' || ch == '*' || ch == '/' ){
                
                    operator = ch;
                    break;
                }
            }
            
            j=pow(10,( i-1 ));  
            
            chr = ch - '0' ;
            
            frac = chr * j;
            
            if ( n <= 1 ){
               
                frac1+=frac;
                
            }
            else if ( n >= 2 ) {
                
                frac2+=frac;
            
            }
                
        }
    
    }
    
    printf("First number s=%d  i=%d  f=%d\n",sign1, abs(integer1), frac1);
    
    printf("Second number s=%d  i=%d  f=%d\n",sign2, abs(integer2), frac2);
    
    /* degerleri pointerlere atama */
    
    *ip1 = abs(integer1);
    *ip2 = abs(integer2);
    
    *sp1 = sign1;
    *sp2 = sign2;
    
    *fp1 = frac1;
    *fp2 = frac2;
        
    return operator;     
}

void convertToDouble( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 ){

    int double1 , double2 ,frac1, frac2;
   
    double1 = (*sp1) * (*ip1);
    double2 = (*sp2) * (*ip2);
    
    frac1 = *fp1;
    frac2 = *fp2;
    
    /* Print results */
    printf("First double %d,%d\n",double1,frac1);
    printf("Second double %d,%d\n",double2,frac2);
    
}

void additionFunc( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 )
{
    int totalint, totalfrac, double1, double2 , frac1, frac2;
    int sign, overflow;
    
    double1 = (*ip1) * ( *sp1 );
    double2 = ( *ip2 ) * ( *sp2 );

    
    frac1 = ( *fp1 ) * ( *sp1 );
    frac2 = ( *fp2 ) * ( *sp2 );
    
    totalint = double1 + double2; 
    totalfrac = abs(frac1 + frac2);
    
    /* determining the sign of total */
    sign=1;
    if ( totalint < 0 ){
        sign=-1;
    } 
    
    /* check the overflow  */
    overflow=0;
    if ( totalfrac > 9999 ){
        overflow=1;
    
    
    /* Print results */
    printf("Total of the numbers is %d,%d\n",totalint,totalfrac);
    printf(" s=%d,  i=%d,  f=%d \n",sign, totalint, totalfrac);
    printf("overflow: %d\n",overflow);
    
    }
}

void subtractionFunc( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 )
{
    int totalint, totalfrac, double1, double2 , frac1, frac2;
    int sign, overflow;
    
    double1 = (*ip1) * ( *sp1 );
    double2 = ( *ip2 ) * ( *sp2 );
    
    
    frac1 = ( *fp1 ) * ( *sp1 );
    frac2 = ( *fp2 ) * ( *sp2 );
    
    totalint = double1 - double2; 
    totalfrac = abs(frac1 - frac2);
    
    /* if the frac 2 greater than frac1 , reduce totalint with 1 */
    
    if ( frac2 > frac1 )
        totalint-=1;
        
    /* determining the sign */
    
    sign=1;
    if ( totalint < 0 ){
        sign=-1;
    } 
    
    /* check the overflow  */
    overflow=0;
    if ( totalfrac > 9999 ){
        overflow=1; 
    
    /* Print results */    
    printf("Result of the subtraction is %d,%d\n",totalint,totalfrac);
    printf(" s=%d,  i=%d,  f=%d \n",sign, abs(totalint), totalfrac);
    printf("overflow: %d\n",overflow);
    
    }
}

void divisionFunc( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 )
{
    int totalint, totalfrac, double1, double2 , frac1, frac2;
    int sign, overflow;
    
    double1 = (*ip1) * ( *sp1 );
    double2 = ( *ip2 ) * ( *sp2 );
    
    
    frac1 = ( *fp1 ) / ( *sp1 );
    frac2 = ( *fp2 ) / ( *sp2 );
    
    totalint = double1 / double2; 
    totalfrac = abs(frac1 / frac2);
    
    /* if the frac 2 greater than frac1 , reduce totalint with 1 */
    
    if ( frac2 > frac1 )
        totalint-=1;
    
    
        
    /* determining the sign */
    sign=1;
    if ( totalint < 0 ){
        sign=-1;
    } 
    /* Print results */
    printf("Result of the division is %d,%d\n",totalint,totalfrac);
    printf(" s=%d,  i=%d,  f=%d \n",sign, abs(totalint), totalfrac);
    
}

void multiplicationFunc( int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 )
{
    int totalint, totalfrac, double1, double2 , frac1, frac2;
    int sign, overflow;
    
    double1 = (*ip1) * ( *sp1 );
    double2 = ( *ip2 ) * ( *sp2 );

    
    frac1 = ( *fp1 ) * ( *sp1 );
    frac2 = ( *fp2 ) * ( *sp2 );
    
    totalint = double1 * double2; 
    totalfrac = abs(frac1 * frac2);
    
    /* if the frac 2 greater than frac1 , reduce totalint with 1 */
    
    if ( frac2 > frac1 )
        totalint-=1;
                
    /* determining the sign */
    sign=1;
    if ( totalint < 0 ){
        sign=-1;
    } 
    
    /* check the overflow  */
    overflow=0;
    if ( totalfrac > 9999 ){
        overflow=1;
    
    /* Print results */
    printf("Result of the multiplication is %d,%d\n",totalint,totalfrac);
    printf(" s=%d,  i=%d,  f=%d \n",sign, abs(totalint), totalfrac);
    printf("overflow: %d\n",overflow);
       
    }
}


void selectEquationforOp( char operator, int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 ){
    op_t op;
    
    /* Operatore almıs oldugum char degeri op_t tipine  
     * cevirdim.Daha sonra switch condition ile hangi islemi  
     * yapması gerektigini yaptım....
     */
     
     /* casting from int to op_t */
    if ( operator == '+' )
        op = (op_t)0;
    else if ( operator == '-' )
        op = (op_t)1;
    else if ( operator == '/' )
        op = (op_t)2;
    else if ( operator == '*' )
        op = (op_t)3;
    
    
    switch( op ){
        case addition:
            additionFunc( ip1, ip2, sp1, sp2, fp1, fp2 );   
            break;
        case subtraction:
            subtractionFunc( ip1, ip2, sp1, sp2, fp1, fp2 );
            break;
        case division:
            divisionFunc( ip1, ip2, sp1, sp2, fp1, fp2 );
            break;
        case multiplication:
            multiplicationFunc( ip1, ip2, sp1, sp2, fp1, fp2 );
            break;
        default:
            printf("Please enter valid operators!!!\n");
    
        
    }

    
}

/* Calculates the Pi and finds the error that is difference between
 * real Pi and mine ...
 */
void calculatePI( int number ){

int sumPi=0, i;

    for ( i = 1 ; i <= number ; i++ ){
    
    sumPi += ( pow((-1),( i+1 )) * 4 );/* / (( 2*i )*( 2*i+1 )*( 2*i +2 )  ); */  

    printf("Number of Pi = %d\n",sumPi);
    }
    
    /* 3 is first value in the formula */
    sumPi +=3;    

    printf("Number of Pi = %d\n",sumPi);

}
void readOpFromFile( char operator, int *ip1, int *ip2, int *sp1, int *sp2, int *fp1, int *fp2 ){

    char comma, ch;
    int  frac1=0, integer1, sign1;
    int  frac2=0, integer2, sign2;
    int i, j, n, status, chr, frac;

    FILE*inp;
    
    inp=fopen("input.txt","r");
    
    for ( n=1 ; n <= 2 ; n++ ){
        
        
        if ( n == 1 ){
            fscanf(inp,"%d",&integer1);
           
        }
        else
            fscanf(inp,"%d",&integer2);
    
        if ( n == 1 ){
            if ( integer1 < 0 )
                sign1=-1;
            else
                sign1=1;
            
        }
        else if ( n == 2 )  {
        
        if ( integer2 < 0 )
                sign2=-1;
            else
                sign2=1;
        
        }
      
        fscanf(inp,"%c",&comma);
        
        if ( comma != ',' )
            printf("Please enter valid doubles!!\n");
        
        for ( i=4 ; i >= 1 ; i-- ){
                    
            status= fscanf(inp,"%c",&ch);
             
            if ( status == EOF || ch == '\n' || ch == ' ' )
                break;
            
            if ( n == 1 ){
            
                operator='-';
                
                if ( ch == '+' || ch == '*' || ch == '/' ){
                
                    operator = ch;
                    break;
                }
            }
            
            j=pow(10,( i-1 ));  
            
            chr = ch - '0' ;
            
            frac = chr * j;
            
            if ( n <= 1 ){
               
                frac1+=frac;
                
            }
            else if ( n >= 2 ) {
                
                frac2+=frac;
            
            }
                
        }
    
    }
    
    fclose( inp );
    
    printf("First number s=%d  i=%d  f=%d\n",sign1, abs(integer1), frac1);
    
    printf("Second number s=%d  i=%d  f=%d\n",sign2, abs(integer2), frac2);
    
    selectEquationforOp( operator ,ip1, ip2, sp1, sp2, fp1, fp2 );

}

void readConasSIFwriteReal( void ){

    int  frac, integer, sign, fractot=0;
    char ch;
    int i=4, j, chr;

    printf("Please enter the values for real number as SIF\n");
    printf("For Ex:   -1  34  56:\n");
    scanf("%d%d",&sign,&integer);

    scanf("%c",&ch);
    
    while ( ch != '\n' ) {
                    
            
            if ( ch == ' ' ) {       /* aradaki boslukları alır */
            /*empty*/
            }                
            else {    
           
            j=pow(10,( i-1 ));  
            
            chr = ch - '0' ;
            
            frac = chr * j;
            fractot+=frac;   
            i--;
            }
            scanf("%c",&ch);
            
        }    
    
    
    
    integer = sign*integer;
    
    printf("The real number is : %d,%d\n",integer,fractot);


}

