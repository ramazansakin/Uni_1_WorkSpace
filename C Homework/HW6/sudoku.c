/*##############################################################################
/*                      111044069--created by Ramazan SAKİN                    #
/******************************************************************************#
/*  PART1: This program solves sudoku that it read a file and writes           # 
/*         the result to file and console                                      #
/*                                                                             # 
/*  INPUT:  sudokuIn.txt                                                       # 
/*  OUTPUT: sudokuOut.txt                                                      #
/******************************************************************************#         
/*  PART2: This program calculates heat simulation on a plate until spesific   #
/*         time and  writes the result to a file                               #
/*                                                                             #
/*  INPUT1: InitialTemperatures.txt: holds initial temperatures of the plate   #
/*  INPUT2: Constants.txt: indicates constant and non-constant elements. 0     #     
/*  indicates a non-constant element, 1 indicates a constant element.          #
/*  OUTPUT:Simulation.txt                                                      # 
/*                                                                             #         
/*                                                                             #
/*############################################################################*/

#include<stdio.h>

        /* Functions Prototypes */
void clear( int sudoku[][9] );

int readSudoku( FILE*inFile, int sudoku[][9] );

int writeSudoku( FILE*outFile, int sudoku[][9] );

int printSudoku( int sudoku[][9] );

int checkCanBePlaced( int sudoku[][9], int posX, int posY, int value  );

int checkIfConsistent( int sudoku[][9] );

int elementsCanBePlaced( int sudoku[][9], int validElement[], int posX, int posY);

int solveSudoku( int sudoku[][9] );

void showSudoku( int sudoku[][9] );
int readTemperature(FILE* inFile, double temp[], int capacity, int* rowCount, int* columnCount);

int readConstants(FILE* inFile2, int consts[], int capacity, int* rowCount, int*columnCount);

int writeTemperature(FILE* outFile, const double temp[], int rowCount, int colCount);

int printTemperature(const double temp[], int rowCount, int colCount);

int getIndex(int colCount, int posY, int posX);

int getNextTimeData(const double currentTemp[], double nextTemp[], const int consts[], int rowCount, int colCount);

double getMSEDifference(const double table1[], const double table2[], int rowCount, int colCount);

int simulate(const double initialTemps[], const int constants[], double resultTemps[], int rowCount, int colCount, double maxMse, int maxIteration);

int writeFinalTemperature(FILE* outFile, const double nextTemp[], int rowCount, int colCount);

int main(void)
{
    /*START_OF_MAIN*/
    /* variables for sudoku */
    int sudoku[9][9];
    int knownElm, knownElm2, status, validElm;
    int i, j, n , selection;
   
    /* variables for heat simulation */
    int  rowCount, columnCount;
	int rowCount2, columnCount2, consts[1000];
	double temp[1000];
    double tempNew[1000];
	int numOfTemp, numOfCon;
	
	FILE *inFile,
  	     *inFile2,
  	     *outFile;
         
    /*END_OF_VARIABLES*/
   
    printf("Please enter 1 for sudoku or enter 2 for Heat Simulation: ");
    scanf("%d",&selection);
  
    if ( selection == 1 ){
    
        inFile = fopen("sudokuIn.txt","r");
        outFile = fopen("sudokuOut.txt","a");

        clear( sudoku );
        status = readSudoku( inFile, sudoku );
    
      if ( status != 1 ){
    
        knownElm = writeSudoku( outFile, sudoku );
        fprintf(outFile,"\nThe number of known elements is %d\n",knownElm);

        knownElm2 = printSudoku( sudoku );
        printf("\nThe number of known elements is %d\n",knownElm2);
    
      if ( knownElm2 != 1 ){
            status = checkIfConsistent( sudoku );
      
      if ( status == 1 )
            printf("\nThe sudoku is consistent...\n");
      
        solveSudoku( sudoku );      
      }      
        /* Writes the result to console */       
        showSudoku( sudoku );
        /* Writes the result to outFile */
        fprintf(outFile,"\n****Result of the Sudoku****\n");
        writeSudoku( outFile, sudoku );
      }
  }  
    else if ( selection == 2 ){
    
        numOfTemp = readTemperature(inFile ,temp, 1000, &rowCount, &columnCount);

	    numOfCon = readConstants( inFile2, consts, 1000, &rowCount2, &columnCount2);
	    
	    if ( numOfCon != numOfTemp && numOfTemp != -1 ){
	    	printf("\nThe number of Temperatures and constants do not agree!!!\n ");
	    	return -1;
	    }
	    else {   
	    
	        writeTemperature( outFile, temp, rowCount, columnCount);
	        
	        printTemperature( temp, rowCount, columnCount);
            
            getNextTimeData(temp, tempNew, consts, rowCount, columnCount);
            
            writeFinalTemperature( outFile, tempNew, rowCount, columnCount);
    }      
  
  }  
    
    /*END_OF_MAIN*/

    return 0;
}

void clear( int sudoku[][9] )
{
    int i, j;
        
    for ( i=0 ; i < 9 ; ++i ){
    
            for( j=0 ; j < 9 ; ++j ){
            
                sudoku[i][j] = ' ';
            
            }
    
    }

}


       /* read the sudoku */
int readSudoku( FILE*inFile, int sudoku[][9] )
{

    int number, status ,row ,col ;
    int numOfElm=0;

  
    for ( row=0 ; row < 9 ; ++row ){
        for ( col=0; col < 9 ; ++col ){
        
            status = fscanf(inFile, "%d",&number);
            
            if ( status == EOF )   
                break;

        numOfElm++;
        sudoku[row][col] = number;
        }
     
    }
    

        if ( numOfElm < 81 ){
                printf("\n\nThere are not enough number in the File!\n\n");  
                return 1;
            }
            
        status = fscanf(inFile, "%d",&number);
        if ( status != EOF ){
            printf("\n\nThere are more elements in the file!\n\n");
            return 1;
        }
    
        fclose(inFile);
    
    return 0;
}
    /* write the sudoku to sudokuOut.txt file */
int writeSudoku( FILE*outFile, int sudoku[][9] )
{
    int row, col ,knownElm = 0;
    
        for ( row = 0; row < 9 ; ++row ){
            for ( col = 0; col < 9 ; ++col ){
                
                if ( sudoku[row][col] > 0 || sudoku[row][col] <= 9 ){
                    fprintf(outFile,"%d ",sudoku[row][col]  );
                
                }
                
                if ( sudoku[row][col] == 0 )
                    knownElm--;
            
            knownElm++;
            
            }
            fprintf(outFile,"\n");
                      
        }

    return knownElm;
}


    /*  Print the sudoku to the console  */
int printSudoku( int sudoku[][9] )
{
    int row, col, knownElm=0;
    
    for ( row=0 ; row < 9 ; ++row ){
        for ( col=0 ; col < 9; col++ ){
            
            if( sudoku[row][col] > 0 && sudoku[row][col] <= 9 ){
                printf("%d ",sudoku[row][col] );
                knownElm++;
            
            }
            
            if ( sudoku[row][col] < 0 || sudoku[row][col] > 9 ){
                printf("\n\nThere is an invalid number in the file!\n");
                return 1;
            
            }
            else if ( sudoku[row][col] == 0 )
                printf("  ");
            
                
        }
        printf("\n");
    
    }

    return knownElm;
}

int checkCanBePlaced( int sudoku[][9], int posX, int posY, int value  )
{
    int row=0, col=0, status, square;
    int i, j;
    
    /* is there a number a ( or more ) number in the same row with each other */
    for ( col = 0 ; col < 9 ; ++col ) {
    
        if ( value == 0 )
            break;
        
        if ( col != posY ){
            if ( sudoku[posX][col] == value ){
                printf("There are same numbers in the %d.row!!!\n",posX+1);
                return 0;
            }
        }
    
    }
    

    /* is there a number a ( or more ) number in the same column with each other */
    col=0;
    for ( row = 0 ; row < 9 ; ++row ) {
        
        if ( value == 0 )
            break;
            
        if ( row != posX ){
            if ( sudoku[row][posY] == value ){
                printf("There are same numbers in the %d.column!!!\n",posY+1);
                return 0;
            }
        }
    
    }


/* which small square (3*3)?? */
/* 13.square demek üstten ilk saga dogru 3.square yani üstten saga dayalı square 3-3 luk*/
/* 22.square demek 3. satırdan 6.satıra kadar olan rowdan ortadaki square 3-3 luk */
    
    if ( posX < 3 && posY < 3 )
        row=0, col=0,   square=11;
    else if ( posX < 3 && posY < 6 )
        row=0, col=3,   square=12;
    else if ( posX < 3 && posY < 9 )
        row=0, col=6,   square=13;
   else if ( posX < 6 && posY < 3 )
        row=3, col=0,   square=21;
   else if ( posX < 6 && posY < 6 )
        row=3, col=3,   square=22;         
   else if ( posX < 6 && posY < 9 )
        row=3, col=6,   square=23;   
    else if ( posX < 9 && posY < 3 )
        row=6, col=0,   square=31;
    else if ( posX < 9 && posY < 6 )
        row=6, col=3,   square=32;
    else if ( posX < 9 && posY < 9 )
        row=6, col=6,  square=33;

    
    if ( value != 0 ){
    for ( i=row ; i < row + 3 ; i++ ){
        for ( j=col ; j < col + 3 ; j++ ){
        
            if ( i != posX && j != posY ){
                
                if ( sudoku[i][j] == value ){
                    printf("There are same numbers in %d.square!!!\n",square);
                    return 0;
                
                }
            }
        }
    
    }   
    
    }
    return 1;
}

  /* Burda her row col ve small square icin  elemanları tek tek checkCanBePlaced 
   * gondererek aynı eleman olup olmadıgını kontrol ettım!!! 
   */

int checkIfConsistent( int sudoku[][9] )
{
    int row, col ,status, value;

    for ( row = 0 ; row < 9 ; ++row ){
        for ( col = 0 ; col < 9 ; col++ ){
            value = sudoku[row][col];
            status = checkCanBePlaced( sudoku, row, col, value  );
        
            if ( status == 0 ){
                printf("The sudoku is not consistent!!!Check your file.\n");
                return 0;
            }
        }
    
    }
    
    return 1;
}

int solveSudoku( int sudoku[][9] )
{
    int i , j, n ;
    int validnum=0;
    int validElements[25];
    
    /* Burda önce sudokunun elemenlarından sıfır olanı buldu ve elementsCnüanBePlaced e
     *  gonderdim orda ki kosullara gore olabılecek valid eleman sayısı eger 1 se yazdırdım
     * 1 den fazla ise gectim ve sudokuyu boyle 80 defa taradım bir daha ki donguye
     * bazı eleman lar dolacagı icin bos kalan yerlerde onlara gore deger alır.. 
     */


    for ( n = 0 ; n < 100 ; n++ ){
 
      for ( i = 0 ; i < 9 ; i++ ){
        
        for ( j=0 ; j < 9 ; j++ ){   
          
          if ( sudoku[i][j] == 0 ){
            validnum = elementsCanBePlaced( sudoku, validElements, i, j );
                
          if ( validnum == 0 ){
             printf("\nAn element of the sudoku cannot have any acceptable value\n");
             return -1;
           }
          if ( validnum == 1 ){
             sudoku[i][j]=validElements[0]; /* gets the valid value into the sudoku */
          
          }
                
        }
            
      } /*end for j */
    } /*end for i */
  } /*end for n */
    
    if ( validnum > 1 ){
        printf("The sudoku is very hard to solve according to me!! :(\n");
        return -2;
    }
        
    
    return 1; 
}

int elementsCanBePlaced( int sudoku[][9], int validElements[], int posX, int posY){

    int validnum=0, i, j, isThere;
    int invalidElm[80], invalidnum=0;
    int  row, col, square;  

        /* burda once invalid elemanları row col ve small square icin bulup
         *  bir array e attım invalidElm[] daha sonra bir dongu ıle invalid elemanların 
         * dısındaki valid elemanları buldum ordan da solveSudoku ya gonderdim 
         */
        
        /* invalid elements for same row */ 
        for ( i=0 ; i< 9 ; i++ ){
            invalidElm[invalidnum] = sudoku[i][posY];
            invalidnum++;
   
        }
     
       /* invalid elements for same column */
        for ( j=0 ; j < 9 ; j++ ){
            invalidElm[invalidnum]=sudoku[posX][j];
            invalidnum++;
            
        }
    
    
    
        /* which small square (3*3)?? */
    /* 13.square demek üstten ilk saga dogru 3.square yani üstten saga dayalı square  */
    /* 22.square demek 3. satırdan 6.satıra kadar olan rowdan ortadaki square */
    
    if ( posX < 3 && posY < 3 )
        row=0, col=0,   square=11;
    else if ( posX < 3 && posY < 6 )
        row=0, col=3,   square=12;
    else if ( posX < 3 && posY < 9 )
        row=0, col=6,   square=13;
   else if ( posX < 6 && posY < 3 )
        row=3, col=0,   square=21;
   else if ( posX < 6 && posY < 6 )
        row=3, col=3,   square=22;         
   else if ( posX < 6 && posY < 9 )
        row=3, col=6,   square=23;   
    else if ( posX < 9 && posY < 3 )
        row=6, col=0,   square=31;
    else if ( posX < 9 && posY < 6 )
        row=6, col=3,   square=32;
    else if ( posX < 9 && posY < 9 )
        row=6, col=6,  square=33;
    
    
    /* invalidElm de olmayan elemanları validElements e attım  */
    for ( i=row ; i < row + 3 ; i++ ){
        for ( j=col ; j < col + 3 ; j++ ){
            
            invalidElm[invalidnum] = sudoku[i][j];  
            invalidnum++;
                
        }
    }
    

    
    for ( i=0 ; i <= 9 ; i++ ){
         isThere=0;
        for ( j=0 ; j < invalidnum ; j++ ){
            
            if ( invalidElm[j] == i )
                    isThere=1;
                 
        }
        
        if ( isThere == 0 ){
                validElements[validnum]=i;
                validnum++;      
        
        }
               
    }
    
  
  
    return validnum;
}

/* show the sudoku if it can be solved */
void showSudoku( int sudoku[][9] )
{
    int i, j;
    
    printf("\n");
    for ( i=0; i<9 ; i++ ){
        for ( j=0 ; j<9 ; j++ ){
            printf("%d ",sudoku[i][j]);
        
        }
        printf("\n");
    
    }
    printf("\n");

}



/* Functions for Heat Simulation  */
int readTemperature(FILE* inFile, double temp[], int capacity, int* rowCount, int* columnCount)
{
	double tempr;
	int numOfTemp=0, status;
	inFile = fopen("InitialTemperatures.txt","r");
	
	fscanf( inFile,"%d",rowCount );
	fscanf( inFile,"%d",columnCount );
	
	status = fscanf(inFile, "%lf",&tempr);
	while ( numOfTemp < capacity ){
		if ( status == EOF ){
			break;
		}
				
		temp[numOfTemp]=tempr;								
		numOfTemp++;
		status = fscanf(inFile,"%lf",&tempr);
	
	}

	if ( numOfTemp != (*rowCount) * (*columnCount) ){
		printf("\nThe capacity of the input array is insufficient\n");
		printf("Please check the file!!!\n\n");
		return -1;
	}

	return numOfTemp;
}

int readConstants(FILE* inFile2, int consts[], int capacity, int* rowCount, int*columnCount)
{
	int cons;
	int numOfCon=0, status;
	inFile2 = fopen("Constants.txt","r");
	
	
	fscanf( inFile2,"%d",rowCount );
	fscanf( inFile2,"%d",columnCount );
	
	status = fscanf(inFile2, "%d",&cons);
	while ( numOfCon < capacity ){
		if ( status == EOF ){
			break;
		}
				
		consts[numOfCon]=cons;								
		numOfCon++;
		status = fscanf(inFile2,"%d",&cons);
	
	}

	if ( numOfCon != (*rowCount) * (*columnCount) ){
		printf("\nThe capacity of the input array is insufficient\n");
		printf("Please check the file!!!\n\n");
		return -1;
	}


return numOfCon;
}


int writeTemperature(FILE* outFile, const double temp[], int rowCount, int colCount)
{
    int i, j;
    outFile = fopen("Simulation.txt","w");
    
    fprintf(outFile,"Initial Temperatures:\n");
    for ( i=0 ; i < rowCount*colCount ; i++ ) {
        if ( temp[i] == 0.00 )
            fprintf(outFile," ");
        
        fprintf(outFile,"%.2f  ",temp[i]);
            
            
            if ( (i+1) % colCount == 0  )
			    fprintf(outFile,"\n");
    }

    fclose(outFile);
}

int printTemperature( const double temp[], int rowCount, int colCount )
{
    int i, j;
    
    fprintf(stdout,"Initial Temperatures:\n");
    for ( i=0 ; i < rowCount*colCount ; i++ ) {
        if ( temp[i] == 0.00 )
            fprintf(stdout," ");
        
        fprintf(stdout,"%.2f  ",temp[i] );
            
                
            if ( (i+1) % colCount == 0  )
			    fprintf(stdout,"\n");
    }

    fprintf(stdout,"\n");

}


int getIndex(int colCount, int posY, int posX)
{

/* returns the index of 1D array representing a table */

    return ( colCount * posY + posX );
}


int getNextTimeData(const double currentTemp[], double nextTemp[], const int consts[], int rowCount, int colCount)
{

    double sum=0, sumAvg;   
    int i, j, k, index, index2, count=0, num=0 ;
    int times , n;     /* times 1, ,2 ,3 ,4,...,9 */
    
         
    for ( k=0; k < colCount * rowCount ; k++ ){   
        
        if ( consts[k] != 1 ){
            
            for ( i=0; i < rowCount ; i++ ){
                
                for ( j=0 ; j < colCount ; j++ ){
                
                    index = k ;
                    index2 = index % colCount;
                    
                    
                    if ( k % colCount >= colCount*i + j -1 &&
                         k % colCount <= colCount*i + j +1 ){
                     
                        sum += currentTemp[ colCount*i + j];
                        
                        count++;
                    
                    }
                
                }     
            
            }
            
            sumAvg = sum / count;
            nextTemp[num] = sumAvg;
            num++;
        
            sum = 0;
            count = 0;
        
        }
        else {
            nextTemp[num] = currentTemp[ num ];
            num++;
            
        }
      
      /* MSE = getMSEDifference( currentTemp, nextTemp, rowCount, colCount); */
        
    }
    
}

double getMSEDifference(const double table1[], const double table2[], int rowCount, int colCount)
{
    double MSE,  maxMSE = table2[0] - table1[0];
    int i;

    for ( i=1 ; i< rowCount*colCount ; ++i ){
        
        MSE = table2[i] - table1[i];
        
        if ( maxMSE < MSE  ){
            MSE = maxMSE;                       
            break;
        }   
    /* turns until preious is greater than next value */
    maxMSE = MSE;
    }

return MSE;

}

int simulate(const double initialTemps[], const int constants[], double resultTemps[], int rowCount, int colCount, double maxMse, int maxIteration)
{
    int times ;

    for (times=0 ; times < 9 ; times++){
        getNextTimeData(initialTemps, resultTemps, constants, rowCount, colCount);    
        
    }
            
    return 1;
}

int writeFinalTemperature(FILE* outFile, const double nextTemp[], int rowCount, int colCount)
{

    int i, j;
    outFile = fopen("Simulation.txt","a");
    
    fprintf(outFile,"Final Temperatures:\n");
    for ( i=0 ; i < rowCount*colCount ; i++ ) {
        if ( nextTemp[i] == 0.00 )
            fprintf(outFile," ");
        
        fprintf(outFile,"%.2f  ",nextTemp[i]);
            
            
            if ( (i+1) % colCount == 0  )
			    fprintf(outFile,"\n");
    }

    fclose(outFile);

}
