/* 
 * File:   Sakin.h
 * Author: neo
 *
 * Created on June 1, 2013, 9:12 PM
 */

#ifndef SAKIN_H
#define	SAKIN_H

   
#define MAXPREF 8
#define MAX_UNI_NUM 100
#define MAX_DEP_NUM 100
#define MAX_STU_NUM 300

#define DEBUG
#define EMPTY -1


typedef struct{
    
    int day;
    int month;
    int year;

}birth_t;


typedef struct{

    int uniPref;
    int depPref;
    
}pref_t;


typedef struct{

    char IDnum[13];  /* There are 12 index numbers for, '\0' of 12.index */
    char name[20];
    char sirname[20];
    birth_t  birthday;
    char scrType;
    char uniName[30];
    char depName[30];
    int isDeleted;
    int isFirstPref;
    int prefNum;
    int isLocated;   /* If the student located to any uni, isLocated=1 , any number o/w */
    pref_t preferences[MAXPREF];
    
}stuInfo_t;

typedef struct{

    char IDnum[13];
    char phone[13];  /* There are 12 index numbers for, '\0' of 12.index */
    char mail[30];
    char address[50];

}stuAddress_t;


typedef struct{
    char IDnum[13];
    double Qscore;
    double Vscore;
    int uniqueID;

}score_t;


typedef struct{
    char depName[30];
    int depID;
    char scrType;
    int quota;
    int emptyQuota;
    double minScore;
    double maxScore;
    int maxScoreOK;     /* if there is max score for that department 1 */
    int isDeleted;
                        
}dep_t;


typedef struct{
    char uniName[30];
    int uniID;
    int numOfDepAUni;
    int isDeleted;
    dep_t departs[MAX_DEP_NUM];
    
}uni_t;



int readstuInfos( char stuInfoFile[], stuInfo_t stuInfo[] );

void printstuInfos( stuInfo_t stuInfo[], int number );

int readDepartments( char departsFile[] ,uni_t universities[MAX_UNI_NUM], int numberOfUni, int* numberOfDeps );

void printDepartments( uni_t universities[MAX_UNI_NUM], int number );

int readPreferences( char prefsFile[], stuInfo_t stuInfo[], int numOfStu  );


int readScores( char scoresFile[], score_t scores[], int numOfStu );


int readstuAddress( char stuAddressFile[], stuAddress_t stuAddress[], int numOfStu  );

void printStuAddress( stuInfo_t stuInfo[], stuAddress_t stuAddress[], int numOfStu );

int sortingScoresAccQuent( score_t scores[], stuInfo_t stuInfo[], int numOfStu );

int locateQuentStuToUni( score_t scores[], stuInfo_t stuInfo[], uni_t universities[],
int numOfStu, int numOfDep  );

int sortingScoresAccVerbal( score_t scores[], stuInfo_t stuInfo[], int numOfStu );

int locateVerbalStuToUni( score_t scores[], stuInfo_t stuInfo[], uni_t  universities[], int numOfStu,int numberOfDeps  );

void consAns1( stuInfo_t stuInfo[], score_t scores[], int numOfStu );

void consAns3( stuInfo_t stuInfo[], uni_t  universities[], int numOfStu, int numOfDep  );

void consAns2( uni_t universities[], int numOfDep  );

void consOut1( uni_t universities[], int numOfDep );

void consOut2( uni_t universities[], int numOfDep );

void csvOut1( uni_t universities[], stuInfo_t stuInfo[], int numOfstu, int numOfdep );

void csvOut2( stuInfo_t stuInfo[], int numOfstu );

void csvOut3(  stuInfo_t stuInfo[], uni_t universities[] , score_t scores[], int numOfstu, int numOfDep );

void csvOut4( uni_t universities[],  int numOfDep );

void createHtmlForPlacement( stuInfo_t stuInfo[], int numOfstu );

void createHtmlForStudents( stuInfo_t stuInfo[], stuAddress_t stuAddress[], int numOfstu );

void SortScoresAccUniq( score_t scores[], int numOfStu );

void DeletingOpr( stuInfo_t stuInfo[], uni_t universities[], int *numOfStu, int *numOfDep  );

void addingOpr( stuInfo_t stuInfo[], stuAddress_t stuAddress[], uni_t universities[],
                                     score_t scores[], int* numOfStu, int* numOfDep );


void createHtmlPlacement( stuInfo_t stuInfo[],score_t scores[],  int numOfStu );

void createHtmlStudents( stuInfo_t stuInfo[], stuAddress_t stuAddress[], int numOfStu );

void fillBinaryFile1( stuInfo_t stuInfo[], char* stuInfoFileBin, int numOfStu  );

void fillBinaryFile2( stuAddress_t stuAddress[], char* stuAddressFileBin, int numOfStu  );

void fillBinaryFile3( score_t scores[], char* scoresFileBin, int numOfStu  );

void fillBinaryFile4( uni_t  universities[], char* universitiesFileBin, int numOfStu  );

#endif	/* SAKIN_H */

