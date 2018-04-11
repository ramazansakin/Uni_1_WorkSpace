/*###############################################################
**          111044069--RamazanSAKİN
**    
**  Bu program input file dan en fazla 5 ve 3 basamaklı integer     
**   (karakter karakter okuduktan sonra integer a cevirir)   
**  alarak islem onceligine dikkat etmeden hesaplar...
**
**###############################################################*/

#include<stdio.h>
	
	/*Defining the functions to use*/
	int convertToInt1d(char ch1);
	
	int convertToInt2d(char ch1,char ch2);

	int convertToInt3d(char ch1, char ch2,char ch3);
	
	int isDigit(char ch);

	int isPlusSign(char ch);

	int isMinusSign(char ch);

	int isMultiplicationSign(char ch);

	int isDivisionSign(char ch);

	int isSign(char ch);

int
main (void)
{
	char ch1, ch2 ,ch3, Space, Space2;	/* variables for characters */
	char opr1, opr2 ,opr3, opr4;  /* variables for operands 
					* "it is the most 4" because there are 5 numbers the most.*/
					
	
	/* int1-2-3-4-5 her ilk 1 veya 2 veya 3 basamaklı sayıyı 
	 *  tutuyor ve işlem yapılırken kullanılıyor resultlar 
	 * sonucu tutarak out file yazmamızı sagliyor...
	 */
	int NumberOfInt,  int1, int2, int3, int4 ,int5;	
	int Result1, Result2, Result3, Result4;
	
	/* Opens files for taking character and output file to print the results..*/

	FILE*inp,
	    *outp;	
	
	inp=fopen("input.txt","r");	
	outp=fopen("output.txt","w");
	
	/* Takes first value(number of integers) */
	fscanf(inp,"%d",&NumberOfInt );
	
	/* İlk bosluğu kullanmayacagımız icin bos bir degere atadım */ 
	fscanf(inp,"%c",&Space);
	
	/* degerleri bastan tek tek char olarak aldım ve sayı olup olmadıgına baktım..
	 * sayı ise bu sefer tekrar okuya okuya kac basamak oldugunu bulmaya calıstım
	 * rakam degilsede diger fonksyonlara gonderip ne oldugunu bulmaya calıstım
	 */
	
	  /*To find first value in inputFile as integer */
	
	fscanf(inp,"%c",&ch1 );
	
	fscanf(inp,"%c",&ch2);
        if (isDigit(ch2) == 1){
            fscanf(inp,"%c",&ch3);
                if ( isDigit(ch3) == 1){
                    int1=convertToInt3d(ch1, ch2, ch3);
                    fscanf(inp,"%c",&opr1);
                }
                else if (isSign(ch3) == 1){
                    opr1=ch3;
                    int1=convertToInt2d(ch1, ch2);
                }
                else {
                    int1=convertToInt2d(ch1, ch2);
                 }
                }      
         else if (isSign(ch2) == 1){
                opr1=ch2;
                int1=convertToInt1d(ch1);
          }     
         else  {
                int1=convertToInt1d(ch1);
          }
         
         
      /*To find second value in inputFile as integer */
    	              
	if ( NumberOfInt >= 2 ){  
	              
    fscanf(inp,"%c",&ch1 );
	
	fscanf(inp,"%c",&ch2);
        if (isDigit(ch2) == 1){
            fscanf(inp,"%c",&ch3);
            
                if ( isDigit(ch3) == 1){
                    int2=convertToInt3d(ch1, ch2, ch3);
                    fscanf(inp,"%c",&opr2);
                }
                else if (isSign(ch3) == 1){
                    opr2=ch3;
                    int2=convertToInt2d(ch1, ch2);
                }
                else {
                    int2=convertToInt2d(ch1, ch2);
                 }
                }      
         else if (isSign(ch2) == 1){
                opr2=ch2;
                int2=convertToInt1d(ch1);
          }
                
         else  {
                int2=convertToInt1d(ch1);
          }   
	   }
	   
	   
	   /*To find third value in inputFile as integer */ 
	 if ( NumberOfInt >= 3){    
	    
	 fscanf(inp,"%c",&ch1 );
	
	fscanf(inp,"%c",&ch2);
        if (isDigit(ch2) == 1){
            fscanf(inp,"%c",&ch3);
            
                if ( isDigit(ch3) == 1){
                    int3=convertToInt3d(ch1, ch2, ch3);
                    fscanf(inp,"%c",&opr3);
                }
                else if (isSign(ch3) == 1){
                    opr3=ch3;
                    int3=convertToInt2d(ch1, ch2);
                }
                else {
                    int3=convertToInt2d(ch1, ch2);
                 }
                }      
         else if (isSign(ch2) == 1){
                opr3=ch2;
                int3=convertToInt1d(ch1);
          }
                
         else  {
                int3=convertToInt1d(ch1);
          }   
	    }
	    
	    
	    /*To find fourth value in inputFile as integer */
	 if ( NumberOfInt >= 4){    
	    
	 fscanf(inp,"%c",&ch1 );
	
	fscanf(inp,"%c",&ch2);
        if (isDigit(ch2) == 1){
            fscanf(inp,"%c",&ch3);
            
                if ( isDigit(ch3) == 1){
                    int4=convertToInt3d(ch1, ch2, ch3);
                    fscanf(inp,"%c",&opr3);
                }
                else if (isSign(ch3) == 1){
                    opr4=ch3;
                    int4=convertToInt2d(ch1, ch2);
                }
                else {
                    int4=convertToInt2d(ch1, ch2);
                 }
                }      
         else if (isSign(ch2) == 1){
                opr4=ch2;
                int4=convertToInt1d(ch1);
          }
                
         else  {
                int4=convertToInt1d(ch1);
          }   
	    }
	    
	    
	    /*To find fifth value in inputFile as integer */
	if ( NumberOfInt >= 5 ){    
	    
	fscanf(inp,"%c",&ch1 );
	
	fscanf(inp,"%c",&ch2);
        if (isDigit(ch2) == 1){
            fscanf(inp,"%c",&ch3);
            
                if ( isDigit(ch3) == 1){
                    int5=convertToInt3d(ch1, ch2, ch3);
                    fscanf(inp,"%c",&Space2);
                }
                else if (isSign(ch3) == 1){
                    Space2=ch3;
                    int5=convertToInt2d(ch1, ch2);
                }
                else {
                    int5=convertToInt2d(ch1, ch2);
                 }
                }      
         else if (isSign(ch2) == 1){
                Space2=ch2;
                int5=convertToInt1d(ch1);
          }
                
         else  {
                int5=convertToInt1d(ch1);
          }   	              
	   }           
	    
	              
    /* operatorlerin ne oldugunu bulmak icin tek tek esıtleriz */

        if ( NumberOfInt >= 2 ){
            if (isPlusSign(opr1) == 1 )
                Result1=int1+int2;
            else if ( isMinusSign(opr1) == 1 )     
                Result1=int1-int2;
            else if ( isMultiplicationSign(opr1) == 1 )     
                Result1=int1*int2;
            else if ( isDivisionSign(opr1) == 1 )     
                Result1=int1/int2;    
        }
        
        if ( NumberOfInt >= 3 ){
            if (isPlusSign(opr2) == 1 )
                Result2=Result1+int3;
            else if ( isMinusSign(opr2) == 1 )     
                Result2=Result1-int3;
            else if ( isMultiplicationSign(opr2) == 1 )     
                Result2=Result1*int3;
            else if ( isDivisionSign(opr2) == 1 )     
                Result2=Result1/int3;    
        }

        if ( NumberOfInt >= 4 ){
            if (isPlusSign(opr3) == 1 )
                Result3=Result2+int4;
            else if ( isMinusSign(opr3) == 1 )     
                Result3=Result2-int4;
            else if ( isMultiplicationSign(opr3) == 1 )     
                Result3=Result2*int4;
            else if ( isDivisionSign(opr3) == 1 )     
                Result3=Result2/int4;    
        }

        if ( NumberOfInt >= 5 ){
            if (isPlusSign(opr4) == 1 )
                Result4=Result3+int5;
            else if ( isMinusSign(opr4) == 1 )     
                Result4=Result3-int5;
            else if ( isMultiplicationSign(opr4) == 1 )     
                Result4=Result3*int5;
            else if ( isDivisionSign(opr4) == 1 )     
                Result4=Result3/int5;    
        }

        if ( NumberOfInt == 2)
            fprintf(outp,"The Result is %d",Result1);
        else if ( NumberOfInt == 3)
            fprintf(outp,"The Result is %d",Result2);
        else if ( NumberOfInt == 4)
            fprintf(outp,"The Result is %d",Result3);
        else if ( NumberOfInt == 5)
            fprintf(outp,"The Result is %d",Result4);    
        else
            fprintf(outp,"The Result is %d",int1);
        

	return 0;
}
	/* FUNCTIONS */
	int convertToInt1d(char ch1)
		{
		int integer1;
		integer1=(ch1 - 48 );	
		return integer1;
		}

	int convertToInt2d(char ch1,char ch2)
		{
		int integer1 ,integer2, sum;
		integer1=(ch1 - 48 );
		integer2=(ch2 - 48 );
		sum=(integer1*10 + integer2);
		return sum;
		}

	int convertToInt3d(char ch1, char ch2,char ch3)
		{
		int integer1, integer2, integer3, sum;
		integer1=(ch1 - 48 );
		integer2=(ch2 - 48 );
		integer3=(ch3 - 48 );
		sum=(integer1*100 + integer2*10 + integer3);
		return sum;
		}

	int isDigit(char ch)
		{
		/* If the character which we take less equal than 9 so, that is a number */
			if ( ch >= '0' && ch <= '9' )
				return 1;
			else 
				return 0;
		}

	int isPlusSign(char ch)
		{
			if ( ch == '+')
				return 1;
			else 
				return 0;
		}

	int isMinusSign(char ch)
		{
			if ( ch == '-' )
				return 1;
			else 
				return 0;	
		}

	int isMultiplicationSign(char ch)
		{
            if ( ch == '*')    
                return 1;
			else 
				return 0;
		}

	int isDivisionSign(char ch)
		{
            if ( ch == '/')    
                return 1;
			else 
				return 0;
		}

	int isSign(char ch)
		{
            if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' )
                        return 1;
            else 
                        return 0;                   
		}
