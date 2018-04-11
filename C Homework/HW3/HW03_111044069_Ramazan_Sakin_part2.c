/*################################################################################
/*                     111044069-created by Ramazan SAKİN                        # 
/********************************************************************************# 
/*  This program takes matrixes from two input file and checks their dimensions  #
/*               of matrixes and caculates their summation                       #
/*                                                                               #
/*##############################################################################*/


#include<stdio.h>

                   /* Function prototypes */
    int FirstCondition( FILE*inp1, FILE*inp2, FILE*outp );
  
    int SecondCondition( FILE*inp1 , FILE*inp2 , FILE*outp, int count1 );
    
    int SumOfMatrixes( FILE*inp1 , FILE*inp2, FILE*outp, int temp, int count );


int
main(void)
{
    /* Files */
    FILE*inp1,
        *inp2,
        *outp;
    
    /* Open Files to take the datas from the file or write the datas to files  */    
    inp1=fopen("input1.txt","r");
    inp2=fopen("input2.txt","r");
    outp=fopen("output.txt","w");
    
    
    /* Bu fonksiyonla(FirstCondition) ilk sartımı yani ikimatrisinde ilk satırdaki 
     * eleman sayılarını kontrol ettim. Eger aynı ise 2. sarta gönderdm 2. sartta tum 
     * eleman sayılarını check ettim ve yine eger aynı ise eleman sayıları; elemanları  
     * tekrar okuyup outfile ye yazdırmak icin de 3. fonsiyonu kullandım(SumOfMatrixes) 
     */
     
         /* Start to calculate! */
    FirstCondition( inp1, inp2, outp );



    return 0;
}


    int FirstCondition( FILE*inp1 , FILE*inp2 , FILE*outp){
            
            int int1 ,int2, count1=0 , count2=0; /* int'ler sayıları tutuyor */
            char char1, char2 ;           /* char'lar spaceleri ve ya '\n' tutuyor*/
    
            /* I found the numbers of int in first line in files and compared what do their 
             * numbers of int are equal to each other. if it is true ,it goes second 
             * condition if it is not true "The matrixes' dimensions do not agree" ..
             */
            while ( char1 != '\n' ){
                fscanf(inp1,"%d",&int1);
                fscanf(inp1,"%c",char1);
                
                count1++;
                
            }
               

                inp2=fopen("input2.txt","r");

            while ( char2 != '\n' ){
                fscanf(inp2,"%d",&int2);
                fscanf(inp2,"%c",char2);
            
                count2++;
            }
            
            printf("counter1 = %d, counter2 = %d", counter1 ,counter2);
                
            if ( count1 == count2 ){
                
                fclose(inp1);
                fclose(inp2);
        
            SecondCondition( inp1 , inp2 , outp, count1 );          
    
            }
            else {
                printf("The matrixes' dimensions do not agree!!!\n");   
                printf("Please check your matrixes!!!\n");
            }
    }
    
    /* I found all numbers of int and compared again.
     * if it is true , I wrote the summation of matrixes to outFile one by one
     * no true ,"The matrixes' dimensions do not agree!"
     */
    int SecondCondition( FILE*inp1 , FILE*inp2 ,FILE*outp, int count ){
            int int1, int2, count1, count2, temp, status=0; 
                inp1=fopen("input1.txt","r");
                inp2=fopen("input2.txt","r");
            
            
            count1 =0;
            while ( (status = fscanf(inp1,"%d",&int1 )) != EOF ){
                    count1++;
            }
            temp= count1 / count;
    
            count2=0;
            while ( (status = fscanf(inp2,"%d",&int2 )) != EOF ){
                    count2++;
            }
                if ( count1 == count2 ){
                    
                    fclose(inp1);
                    fclose(inp2);
  
                SumOfMatrixes( inp1 , inp2, outp, temp, count );
                
                }
                else {
                    printf("The matrixes' dimensions do not agree!!!\n");
                    printf("Please check your matrixes!!!\n");
                }
    }

    /* This function takes integers from the files one by one 
     * And calculates sum of them and writes to outputFile..    
     */
    int SumOfMatrixes( FILE*inp1 , FILE*inp2, FILE*outp, int temp, int count ){
            int i , j, sum=0, int1, int2 ;
                inp1=fopen("input1.txt","r");
                inp2=fopen("input2.txt","r");            
            
            
            for ( i=1 ; i<= temp; i++ ) {
                for ( j=1 ;j <= count ; j++ ){
                fscanf(inp1,"%d",&int1);
                            
                fscanf(inp2,"%d",&int2);
                sum=int1 + int2;
                fprintf(outp,"%d ",sum );
                }    
             fprintf(outp,"\n");
            }
}



