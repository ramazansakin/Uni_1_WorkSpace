/*A Sample Solution for Midterm*/
/*Bil108 Spring, 2013*/


#include<stdio.h>
#include<string.h>

#define MAX_LEN 100
#define FILE_NAME "integers.txt"
#define STR_FILE_NAME "names.txt"
#define NUMBER_OF_MONTHS 12

int* read_array(FILE* file, int arr[], int* size);
int find_stats(int arr[], int size, int* max, int* min, int* mean);
void sorter(char str[][MAX_LEN], int rowCount);
void printStrArr(char str[][MAX_LEN], int rowCount);
int read_string_array(char fileName[], char strArr[][MAX_LEN]);
int getNumber(char str[], int* digitCount);
char* un_tag(char sentence[], char names[][MAX_LEN], int rowCount, const char* months[]);

int main()
{
	
    int max, min, mean;
    int arr[MAX_LEN];
	int size;
	int errorStatus;
	
	FILE* intFile;
	FILE* strFile;
	
	char strArr[][MAX_LEN] =  {"***", "*",  
	"****", "**"};
	char sentence[800];
	char names[MAX_LEN][MAX_LEN];
	/*Because each pointer shows a constant string, there no need
	to allocate memory*/
	const char* MONTHS[] = {"January",
							"February",
							"March",
							"April",
							"May",
							"June",
							"July",
							"August",
							"September",
							"October",
							"November",
							"December"};
	char* unTagged;
	

	intFile = fopen(FILE_NAME, "r");
	if(intFile == NULL)
		printf("Error: File %s could not be opened!!!\n", FILE_NAME);
    else{
    	read_array(intFile, arr, &size);
    	errorStatus = find_stats(arr, size, &max, &min, &mean);
    	if(errorStatus)
    		printf("Error: Invalid Size\n");
    	else
    		printf("max:%d, min:%d, mean:%d \n",max,min,mean);
   	}
   	
   	/*Part 2*/
   	sorter(strArr, 4);
  	printStrArr(strArr, 4);
  	
  	/*Part 3*/
  	size = read_string_array(STR_FILE_NAME, names);
  	if(size == -1)
  		printf("I/O Error: File could not be opened!!!\n");
  	else{
  		printf("Enter the sentence:\n");
  		gets(sentence);
  		unTagged=un_tag(sentence, names, size, MONTHS);
  		if(unTagged)
  			printf("%s\n", sentence);
  		else
  			printf("Error: Illegal Tag\n");
   	}
	return 0;
}

int* read_array(FILE* file, int arr[], int* size)
{
	int s = -1; /*size*/
	int status = 0; 

	
	while(status != EOF){
		++s;
		/*1 more read will be done, however fscanf will not record 
		the junk value into the array. */
		status = fscanf(file, "%d", &arr[s]);	
	}	

	*size = s;
	return arr;
}

int find_stats(int arr[], int size, int* max, int* min, int* mean){
	int i;
	int sum;
	
	if(size<1)
		return -1;
		
	sum = *max = *min = *mean = arr[0];
	
	for(i=1; i<size; ++i) {
		sum += arr[i];
 		if(arr[i] < *min)
 			*min = arr[i];
 		else if(arr[i] > *max)
 			*max = arr[i];
	}
	
	*mean = sum / size;
	
	return 0;
}

void sorter(char str[][MAX_LEN], int rowCount){
	int i, j;
	char tempStr[MAX_LEN];
	
	
	for(i = 0; i < rowCount; ++i){
		for(j=i+1; j < rowCount; ++j){
			if(strlen(str[j]) < strlen(str[i])){
				/*swap*/
				strcpy(tempStr, str[i]);
				strcpy(str[i], str[j]);
				strcpy(str[j], tempStr);
			}
		}
	}	
}
				

void printStrArr(char str[][MAX_LEN], int rowCount){

	int i;
	
	for(i=0; i<rowCount; ++i)
		printf("%s\n", str[i]);

}


int read_string_array(char fileName[], char strArr[][MAX_LEN]){
	
	int i = 0, j;
	char* status;
	FILE* file = fopen(fileName, "r");
	
	if(file == NULL)
		return -1; /*File I/O error*/
		
	while(status != NULL){
		/*record the name*/
		status = fgets(strArr[i], MAX_LEN, file);
		
		/*Delete the newline character at the end*/
		j = 0;
		while((strArr[i][j] != '\n') && (strArr[i][j] != '\0'))
			++j;
		strArr[i][j] = '\0';	
		
		++i;
	}
	
	return i;
}

char* un_tag(char sentence[], char names[][MAX_LEN], int rowCount, const char* months[]){

	int i = 0, iNew = 0; 
	int tagInd, digitC;
	char tagIdentifier;
	char tempStr[1000];
	const char* strToInsert; /*shows the string to be inserted*/
	
	
	do{
		if(sentence[i] == '*'){
			tagIdentifier = sentence[i+1];
			tagInd = getNumber(&sentence[i+2], &digitC); 
			if(digitC == 0)
					return NULL; /*Illegal tag index*/
					
			if(tagIdentifier == 'n'){
				strToInsert = names[tagInd];/*sellect the corresponding name*/
				if(tagInd > rowCount)
					return NULL; /*Illegal tag index*/
			}
			else if(tagIdentifier == 'm'){
				strToInsert = months[tagInd];/*sellect the corrresponding month*/
				
				if(tagInd > NUMBER_OF_MONTHS)
					return NULL; /*Illegal tag index*/
			}
			else
				return NULL;/*Illegal tag identifier*/
			
			/*replace the tag with the sellected string*/	
			strcpy(&tempStr[iNew], strToInsert);
			iNew += strlen(strToInsert);
			i += (2+digitC);
		}
		else{
			tempStr[iNew] = sentence[i];
			++i;
			++iNew;	
		}
	}while(sentence[i] != '\0');
	
	for(i=0; i<iNew; ++i)
		sentence[i] = tempStr[i];
	sentence[iNew] = '\0'; 
}

int getNumber(char str[], int* digitCount){
	int digit = str[0] - '0';
	int number = 0;
	
	*digitCount = 0;
	/*while the character refers a number*/
	while((digit >= 0) && (digit <= 9)){ 
		number = number*10 + digit;
		++(*digitCount);
		digit = str[*digitCount] - '0';
	}
	
	return number;
}

