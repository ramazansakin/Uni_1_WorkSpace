/*##############################################################################
/*                      111044069--created by Ramazan SAKİN                    #
/******************************************************************************#
/*        This Program takes a celcius value and number of terms               #
/*     from user and calculates its sinus, takes error and calculates          #
/*             how much times should it be turned for min error                #
/*                                                                             #     
/*############################################################################*/


#include<stdio.h>
#include<math.h>

#define PI 22/7

    /*         Function prototypes                   */
    /* This function calculates sinus for any value */
    double getSinus(int n, double z ); 

    /* This calculates factorial for finding sinus */
    int getFactforSin( int a );
    
    /*This function calculates min 'n' number to be less than error that you entered*/
    int getMaxError( double realSin , double hata, double z );
      
int 
main(void)
{
    int n, a;
    double z, realSin, sinz, hata;   /* z : sinz  n:number of terms of sinz  */
    /* hata : error that user entered - realSin : the value of sinz in math.h library */

    printf("Please enter a value as celcius:");
    scanf("%lf",&z);
    
    printf("Please enter error:");
    scanf("%lf",&hata);
    
    /* how many times do I add the terms of sinus ?? */
    printf("Please enter number of terms for finding sinüs:");
    scanf("%d",&n);
     
    realSin=sin( (PI * z) / 180);
    
    /* to calculate sin of z */
    sinz=getSinus( n, z );
    
    printf("The value of sin%.2f is %.5f\n",z , sinz);    
    
    /* because of the error is generally little, it returns 0, 1 or 2 ! */
    getMaxError( realSin, hata, z );
    
    return 0;
}

/* This function calculates sinus for any value as celcius */

double getSinus( int n, double z  )
{
    int  a=0, i=0 ;
    double sum=0, sinx, fact=0;
    
    
    while (  i <= n  )
    {
         
        fact = getFactforSin( a );
        sinx = (pow( (-1),( a ) )) * ( pow(((z*PI)/180),(2*a+1)) ) / (fact);
        sum += sinx;
        a++;
        i++;
    }
    
    return sum;
    
}

/* I used this function to take factorial  for without mixing with other
 * equations and I used  (z*PI) / 180 to convert radyan...
 */  


int getFactforSin( int a )
{
    int product=1 , i ;
    for ( i=1 ; i <= 2*a + 1 ; i++ )
        product *= i;
        
    return product;
}


/*This function calculates min 'n' number to be less than error that you entered*/
int getMaxError( double realSin , double hata ,double z )
{
    int  i=0 , a=0, fact;
    double Minn=0, sinx2=0, sum2=0 ;
             
        while ( Minn < hata )
        {
        
            fact = getFactforSin( a );
            sinx2 = (pow( (-1),( a ) )) * ( pow(((z*PI)/180),(2*a+1)) ) / (fact);
            sum2 += sinx2; 
            a++;
            i++;
            Minn=fabs( realSin - sinx2 );
        }   
        
    printf("If you want to be less than error you've entered, ");
    printf("you should enter minimum %d for 'n' ! \n",i);
}


