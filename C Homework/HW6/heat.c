#include<stdio.h>

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
	int  rowCount, columnCount;
	int rowCount2, columnCount2, consts[1000];
	double temp[1000];
    double tempNew[1000];
	int numOfTemp, i, numOfCon;
	
	FILE *inFile,
  	     *inFile2,
  	     *outFile;
    /* END_OF_VARIABLES */


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

    /*END_OF_MAIN*/
    return 0;
}

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


