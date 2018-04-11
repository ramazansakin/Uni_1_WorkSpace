/*
 *
 * Programmer : Sabri Mevis
 * Student ID : 101044009
 * Email : sabrimev@gmail.com
 * Date : 26 April 2013
 *
 * Description of Part1 : Reads number from a file ,
 *                        find max, min and mean
 *
 * Description of Part2 : Sorts array of strings by length
 *
 *
 *
*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define FILE_NAME "integers.txt"

/*function prototypes*/
int read_arrays(int *arr, FILE *inp);
void find_stats(int *max,int *min,int *mean,int *arr,int length);
int findTheLength(char str[100][100], int len );

int main()
{
    int max,min,mean,i,length ;
    int arr[MAX_LEN],len;
    char str[MAX_LEN][MAX_LEN];
    
    /*PART1******************************/
    FILE *inp;
    inp = fopen(FILE_NAME,"r");
    
    length = read_arrays(arr,inp);
    printf("length : %d\n",length);
    find_stats(&max,&min,&mean,arr,length);
    printf("max: %d , min: %d , mean: %d \n",max,min,mean);
    /*ENDPART1******************************/
    
    
    /*PART2******************************/
    printf("How many strings do you want to enter? : ");
    scanf("%d",&len);
    for(i = 0 ; i<len; i++)
    {
        printf("%d.Write the string : ",i+1);
        scanf("%s",str[i]);
    }
    findTheLength(str,len);
    
    for(i= 0 ; i<len ; i++)
        printf("%s\n",str[i]);   
    /*ENDPART2******************************/ 
    close(inp);
}

/*get the array*/
int read_arrays(int *arr, FILE *inp)
{  
    int status,i,length = 1;

    status = fscanf( inp,"%d", &arr[0] );
    
    for(i = 1 ; status != EOF ; i++)
    {
        length++;
        status = fscanf(inp,"%d",&arr[i]);

        printf("%d ",arr[i-1]);
        
    }
    printf("\n");
    
    return length-1;
}

/*find the max, min and mean*/
void find_stats(int *max,int *min,int *mean,int *arr,int length)
{
    int temp = arr[0],temp1 = arr[0],i = 0;
    int average=0 ; 
   
    while( i < length )
    {   
        /*find max value*/
        if(arr[i] >= temp)
        {
            *max = arr[i];
            temp = arr[i];
        }
        /*find min value*/
        if(arr[i] <= temp1)
        {
            *min = arr[i] ;
            temp1 = arr[i];       
        }
        
        average += arr[i]; 
        i++;
    }
    /*Sum of values*/
    printf("sum : %d\n",average);
    *mean = average / length ; /*get mean*/

}

/*Sort the array of strings*/
int findTheLength(char str[100][100], int len )
{
    int temp,temp1,i,j=0;
    char tempStr[MAX_LEN]; 
    
    while(j<len)
    {
        temp = strlen(str[j]);
        for(i = 0 ; i<len ; i++)
        {
            temp1 = strlen(str[i]);
            
            if(temp1 > temp)
            {
                strcpy(tempStr,str[j]);
                strcpy(str[j],str[i]);
                strcpy(str[i],tempStr);       
            }
        }
        j++;
   }
}

