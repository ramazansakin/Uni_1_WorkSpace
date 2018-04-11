#include<stdio.h>

int readSudoku(const char fileName[], int sudoku[][4]);

int solveRec(int sudoku[][4],int* value, int posX, int posY);

int solve(int sudoku[][4]);

void printSudoku(FILE* stream, int sudoku[][4]);

void clear( int sudoku[][4] );

int main(void)
{
    int sudoku[4][4];
    char fileName[100] = "sudokuIn.txt";
    
    FILE* outFile;
    
    clear(sudoku);
    readSudoku(fileName, sudoku );

    solve( sudoku );
    printSudoku(outFile ,sudoku);

    return 0;
}

void clear( int sudoku[][4] )
{
    int i, j;
        
    for ( i=0 ; i < 4 ; ++i ){
            for( j=0 ; j < 4 ; ++j ){
                sudoku[i][j]= ' ';
            
            }
    
    }

}
    /* read the sudoku */
    
int readSudoku( const char fileName[], int sudoku[][4] )
{

    int number, status ,row ,col ;
    int numOfElm=0;
    FILE* inFile;

    inFile = fopen( fileName,"r" );
    
    if ( fileName == NULL ){
        printf("The file is not found!\n");
        return -1;/* The file was not found!!! */
    
    }
    for ( row=0 ; row < 4 ; ++row ){
        for ( col=0; col < 4 ; ++col ){
        
            status = fscanf(inFile, "%d",&number);
            
            if ( status == EOF )   
                break;

        numOfElm++;
        sudoku[row][col] = number;
        }
     
    }
    

        if ( numOfElm < 16 ){
                printf("\n\nThe File is bad format!!\n\n");  
                return -2;
            }
            
        status = fscanf(inFile, "%d",&number);
        if ( status != EOF ){
            printf("\n\nThe file is bad format\n");
            return -2;
        }
    
        fclose(inFile);
    
    return 0;
}
    /* write the sudoku to sudokuOut.txt file */
void printSudoku( FILE*outFile, int sudoku[][4] )
{
    int row, col ,knownElm = 0;
    outFile = fopen("sudokuOut.txt","w");
    
        for ( row = 0; row < 4 ; ++row ){
            for ( col = 0; col < 4 ; ++col ){
                
                if ( sudoku[row][col] > 0 || sudoku[row][col] <= 4 ){
                    fprintf(outFile,"%d ",sudoku[row][col]  );
                
                }
            
            }
            fprintf(outFile,"\n");
                      
        }


}


int solve( int sudoku[][4] )
{
    
    char* sudo;
    sudo = &sudoku[0][0];    
    int i, j,n;
    int* value, status;
    
    for ( n=0 ; n<50 ; ++n ){
      for ( i=0 ; i<4 ; ++i  ){   
        
        for ( j=0; j<4 ; ++j){
            value = 1;
            if ( sudoku[j] == 0  ){
                status = solveRec( sudoku, &value, i ,j );
                    
                if ( status == 1 )
                    sudoku[i][j] = status;
            }
        }
                
    }

  }
  
}


int solveRec(int sudoku[][4], int* value, int posX, int posY )
{
  
    
    int row=0, col=0, status, square;
    int i, j;
    int flag1=0, flag2=0, flag3=0;
    
    /* is there a number a ( or more ) number in the same row with each other */
    for ( col = 0 ; col < 4 ; ++col ) {
    
        if ( *value == 0 )
            break;
        
        if ( col != posY ){
            if ( sudoku[posX][col] == *value ){
                printf("There are same numbers in the %d.row!!!\n",posX+1);
                flag1=1;
            }
        }
    
    }
    

    /* is there a number a ( or more ) number in the same column with each other */
    col=0;
    for ( row = 0 ; row < 4 ; ++row ) {
        
        if ( *value == 0 )
            break;
            
        if ( row != posX ){
            if ( sudoku[row][posY] == *value ){
                printf("There are same numbers in the %d.column!!!\n",posY+1);
                flag2=1;
            }
        }
    
    }


/* which small square (3*3)?? */
/* 13.square demek üstten ilk saga dogru 3.square yani üstten saga dayalı square 3-3 luk*/
/* 22.square demek 3. satırdan 6.satıra kadar olan rowdan ortadaki square 3-3 luk */
    
    if ( posX < 2 && posY < 2 )
        row=0, col=0,   square=11;
    else if ( posX < 2 && posY < 4 )
        row=0, col=2,   square=12;
    else if ( posX < 4 && posY < 2 )
        row=2, col=0,   square=21;
    else if ( posX < 4 && posY < 4 )
        row=2, col=2,   square=22;         
   
    
    if ( *value != 0 ){
    for ( i=row ; i < row + 2 ; i++ ){
        for ( j=col ; j < col + 2 ; j++ ){
        
            if ( i != posX && j != posY ){
                
                if ( sudoku[i][j] == *value ){
                    printf("There are same numbers in %d.square!!!\n",square);
                    flag3 = 1;    
                    
                }
                if ( flag1 != 0 && flag2 != 0 && flag3 != 0 )
                    return value;                
                else if ( *value <= 4 ){
                    *value+=1;
                    solveRec( sudoku,value,posX,posY   );
                                    
                    }
                    else 
                        return 0;
            
            }
        }
    
      }   
    
    }         
        
        
    
    return 1;
}



