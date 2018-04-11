/*##############################################################################
/*                      111044069--created by Ramazan SAKİN                    #
/******************************************************************************#
/*     PART1-1:Bu fonksiyon kullanıcının girdigi sayıyı alıp tek ise düzden    #
/*              cift ise tersten yazdırır                                      #
/*     PART1-2:Bu fonksiyon kullanıcıdan yukseklık hkarakter ve sayı alarak    #
/*              kullanıcının istedigi sekilde arrow yazdırır..                 #
/*                                                                             #
/*     PART2:Bu fonksiyon iki dosyadan aldıgı iki matrisin carpımın            #
/*           sonucunu dosyaya yazdırır..                                       #
/*           inputs:input1.txt , input2.txt                                    #
/*           outputs: output.txt                                               #     
/*                                                                             #     
/*############################################################################*/


#include<stdio.h>

    int drawNumericPattern( int n );
    
    int drawArrowLikePattern( int height, int count, char ch );    
    /* hocam 3 u gec yaptıgımdan pek yorum yazamadım */
    void MatrixMultiplier( FILE*mat1, FILE*mat2 , FILE*result );
    
int main( void )
{
    int select, numOfInt, numOfInt2;
    int count, height , n;
    
    /* which one?? */
    printf("Please enter 1 to draw numeric pattern\n");
    printf("Or enter 2 to draw arrow like pattern:\n ");
    printf("Or enter 3 to calculate multiplying  of two matris: ");
    
    scanf("%d",&select);
    if ( select == 1 ){

        printf("Please enter a number:");
        scanf("%d",&n);
        /* writes the all character number */
        numOfInt2=drawNumericPattern( n );
        printf("Summation of all integers is %d\n",numOfInt2);

    }
    else if ( select == 2 ){
        char ch , ignore;    /* ignore takes unimportant value */
        
        printf("Please enter height for figure:");
        scanf("%d",&height);
        
        scanf("%c",&ignore);
        
        printf("Please enter a character for figure 'O' or 'X':");
        scanf("%c",&ch);
        
        printf("Please enter number of figure:");
        scanf("%d",&count);
        
        numOfInt=drawArrowLikePattern(height, count, ch );
        /* writes the all character number */
        printf("Summation of all characters is %d\n",numOfInt);
    }
    else if ( select == 3 ){
    
        /* Files */
        FILE*mat1,
            *mat2,
            *result;
    
        /* Open Files to take the datas from the
         file or write the datas to file  */    
        mat1=fopen("input1.txt","r");
        mat2=fopen("input2.txt","r");
        result=fopen("output.txt","w");


    MatrixMultiplier( mat1, mat2, result );
    
    }
    else
        printf("Please enter valid characters and numbers\n");    
    
        
        

    return 0;
}

int drawNumericPattern( int n ){
    int i, j, l ,k, numOfInt2;  
    
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
    
    numOfInt2=(n*(n+1))/2;
    /* drawArrow daki gibi de yapılabilir ama farklı olsun diye 
     * bu sekilde formulden yaptım..
     */  
    return numOfInt2;
}


int drawArrowLikePattern( int height, int count, char ch ){

    int i, j, k, l, m, n, temp, temp2, number, numOfInt=0;    
    /* her dongu de bir arttırarak bosluk sayısını arttırdım  
     * aynı zamanda diger dongu ile ch sayısını arttırıp azalttım
     * iki for la yaptım bir qrrow un ust tarafını artan sekilde yaptım
     * alt atarafını ayrı dongu ıle azalacak sakılde yaptım...
     */ 
    temp=height;
    for ( i=1 ; i <= height/2+1 ; i++ ){
        
        for ( j=1 ; j <= count ; j++ ){
        
            for ( k=1 ; k <= i ; k++ ){
                number=printf("%c",ch);
                
                numOfInt+=number;
            }
            for( l=1 ; l <= temp/2 +j ; l++ )    
                printf(" ");
                
            
        
        }
        printf("\n");
        if ( i != height/2+1 ){
        for ( m=1 ; m <= i ; m++ )
            printf(" ");
            temp-=2;
        }   
    }    

    temp2=height;
    
    for ( i=1 ; i<= height/2 ; i++ ){
        
        for ( j =1 ; j<= height/2 -i ; j++ ){        
            printf(" ");
        
        }
        
        for ( k=1 ; k <= count ; k++ ){
        
            for ( l=1 ; l <= temp2/2 +1 -i ; l++ ){
                number=printf("%c",ch);
            
                numOfInt+=number;
            }
            for ( m=1 ; m <= k+i ; m++ )
                printf(" ");    
        
        }
        printf("\n");
           
    }    
    
    return numOfInt;
}
void MatrixMultiplier( FILE*mat1, FILE*mat2 , FILE*result ){

    int col1=0, col2=0, row1, row2, int1, int2 ;
    int  count=0, count1=0, count2=0 ;
    char char1, char2;
    double num1, num2, num12, total=0, double1, double2;
    int i, j, f, n, t, status=0;
    
    
    while ( char1 != '\n' ){
                fscanf(mat1,"%lf",&double1);
            
                fscanf(mat1,"%c",&char1);
            
                col1++;       
            }

    while ( char2 != '\n' ){
                fscanf(mat2,"%lf",&double2);
            
                fscanf(mat2,"%c",&char2);
            
                col2++;
            }

            rewind(mat1);
            rewind(mat2);
    
            while ( (status = fscanf(mat1,"%lf",&double1 )) != EOF ){
                    count1++;
            }
            row1= count1 / col1;
    
            
            while ( (status = fscanf(mat2,"%lf",&double2 )) != EOF ){
                    count2++;
            }
            
            row2= count2 / col2;
            
          
            if ( col1 != row2 ){
                 
                printf("The matrixes' dimensions do not agree!!!\n");
                printf("Please check your matrixes!!!\n");
                    
                }
            if ( col1 == row2 ) {
        
        rewind(mat1);         
        rewind(mat2);        
              
        
        for ( t=1 ; t <= row1 ; t++ ){
          
            for ( i=1 ; i <= col2 ; i++ ){
                
                for ( j=1 ; j <= col1 ; j++ ){
                    
                           
                    for ( f=1 ; f <= (i-1)*col1 ; f++ ){
                        fscanf(mat1,"%lf",&num1);
                    
            
                    }
                
                    for ( n=1 ; n <= j ; n++ ){
                        fscanf(mat1,"%lf",&num1);      
                    
                    }
                  
                 if ( j==1 ){
                 fscanf(mat2,"%lf",&num2);
                    count++;
                 }
                 else {
                 for( n=0 ; n <=col2; n++ ){
                 count++;
                 fscanf(mat2,"%lf",&num2);
                  if ( count % col2 == i )
                    break;
                    
                }
            }
                printf("%d\n",count);
                num12 = num1 * num2;
                total += num12;
                
                rewind(mat1);
                }
                
                fprintf(result,"%.2f ",total);
            
                rewind(mat2);
                total=0;
            if ( i == col2 )
                fprintf(result,"\n");
                
            count=0;  
            }
        
        }
        
        } /* if 2 */
               
}



