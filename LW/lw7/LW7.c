#include<stdio.h>

#define STR_CAP 1000
#define MAX_COL 100
#define MAX_ROW STR_CAP/MAX_COL
#define FILE_NAME "input.txt"

int isLetter(char ch);
int read(const char fName[], char str[], int strCap);
char* myStrChr(char str[], char ch);
int getWordCount(char str[]);
int print(char* strArr[], int rowC);
int readByRows(const char fName[], char* strArr[]);


int main(){
	char str1[STR_CAP];
	char str2[STR_CAP];
	char* ptr1;
	char* ptrArr[MAX_ROW];
	int numOfLetters;
	int i;
	int numOfRows;
	
	numOfLetters = read(FILE_NAME, str1, STR_CAP);
	if(numOfLetters == -1)
		printf("File not Found!!\n");
	else
		printf("%d letters read.\n", numOfLetters);
		
	ptr1 = myStrChr(str1, 't');
	if(ptr1 == 0)
		printf("Character not Found!!\n");
	else
		printf("After first t: %s\n", ptr1);
		
	printf("%d words found.\n", getWordCount(str1));
	
	/*use str2 as a storage for the ptr array*/
	for(i=0; i<MAX_ROW; ++i)
		ptrArr[i] = &str2[MAX_COL*i];
		
	numOfRows = readByRows(FILE_NAME, ptrArr);
	printf("%d senteces read.\n", numOfRows);
	print(ptrArr, numOfRows);
	
	return 0;
}

int isLetter(char ch){
	return (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')));
}

int read(const char fName[], char str[], int strCap){
	FILE* inFile;
	char* status;
	int i = 0, count = 0;
	
	inFile = fopen(fName, "r");
	status=fgets(str, strCap,inFile);
	if(status == 0)
		return -1;
	
	while(str[i] != '\0'){
		if(isLetter(str[i]))
			++count;
		++i;
	}
	
	fclose(inFile);
	return count;
}

char* myStrChr(char str[], char ch){
	int i = 0;
	
	while(str[i] != '\0'){
		if(str[i] == ch)
			return &str[i];
		++i;
	}
	
	return 0; /*not found, return null pointer*/
}

int getWordCount(char str[]){
	int count = 1;
	char* newStr = str;
	
	newStr = myStrChr(newStr, ' '); /*pozition of the first space character*/
	while(newStr){ /*while newStr is not a null ptr*/
		/*a new word is found*/
		++count;
		/*proceed 1 element, so show the beginning of the next word*/
		newStr = &newStr[1];
		/*pozition of the next space character*/	
		newStr = myStrChr(newStr, ' '); 
	}
	
	return count;
}

int print(char* strArr[], int rowC){
	int i;
	int printedChars = 0;
	
	for(i=0; i<rowC; ++i)
		printedChars += printf("%s\n", strArr[i]);
		
	return printedChars;
}

int readByRows(const char fName[], char* strArr[]){
	char str[STR_CAP];
	int status;
	int i = 0, rowC = 0, colC=0;
	char tempCh;
	char* row, * rowNext;
	
	/*get the content of the file in a string*/
	status = read(fName, str, STR_CAP);
	if(status == -1) /*file not found*/
		return -1;
	
	tempCh = str[i];
	while(tempCh != '\0'){
		strArr[rowC][colC] = tempCh;
		if(tempCh == '.'){
			strArr[rowC][colC+1]='\0'; /*end the row*/
			++rowC;
			colC = 0;
		}
		else
			++colC;
		++i;
		tempCh = str[i];
	}
	
	return rowC;
}
	
	


