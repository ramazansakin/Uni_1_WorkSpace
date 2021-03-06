#include<stdio.h>

    void MatrixMultiplier( FILE*mat1, FILE*mat2 , FILE*result );

int main( void )
{

    /* Files */
    FILE*mat1,
        *mat2,
        *result;
    
    /* Open Files to take the datas from the file or write the datas to file  */    
    mat1=fopen("input1.txt","r");
    mat2=fopen("input2.txt","r");
    result=fopen("output.txt","w");


    MatrixMultiplier( mat1, mat2, result );



    return 0;
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
            
           printf("******%d****",row1);
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
                  if ( (count+col2) % col2 == i )
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
                
