#include <stdio.h>
#include "sakin.h"


int main( void )
{
    
    /* CSV Files  */
    char stuInfoFile[] = "StudentsNames.csv";
    char departsFile[] = "Departments.csv";
    char prefsFile[] = "Preferences.csv";
    char scoresFile[] = "Scores.csv";
    char stuAddressFile[] = "StudentsAddressInfo.csv";
    
    /* Binary Files */
    char stuInfoFileBin[] = "StudentsNamesBin.bin";
    char universitiesFileBin[] = "universitiesBin.bin";
    char scoresFileBin[] = "ScoresBin.bin";
    char stuAddressFileBin[] = "StudentsAddressInfoBin.bin";
    
    int numOfStu;
    int numberOfUni;
    int numberOfDeps=0;
    stuInfo_t stuInfo[MAX_STU_NUM];
    uni_t universities[MAX_UNI_NUM];
    score_t scores[MAX_STU_NUM];
    stuAddress_t stuAddress[MAX_STU_NUM]; 
    int i,  choice;
    int selection, selection2, selection3;
    char ignore;
    
    
    numOfStu = readstuInfos(stuInfoFile, stuInfo );

    #if defined (DEBUG)
      printf("\n***  The number of the students who have joined the exam is: %d  ***\n",numOfStu);
    #endif


    numberOfUni = readDepartments( departsFile , universities, numberOfUni, &numberOfDeps );
    
    #if defined (DEBUG)
      printf("***  The number of Universities:%d and Departments: %d  *** \n",numberOfUni, numberOfDeps);
    #endif
    
    
    readPreferences( prefsFile, stuInfo,numOfStu  );
    
    readScores( scoresFile, scores, numOfStu );
    
    readstuAddress( stuAddressFile, stuAddress, numOfStu );
    
    sortingScoresAccQuent( scores, stuInfo, numOfStu );
    
    
    #if defined (DEBUG)
      printf("\n************************************************************************\n");
      printf("***  The Student who has the highest Quentitative score is %s %s ***\n",stuInfo[scores[0].uniqueID].name,
                                                                                      stuInfo[scores[0].uniqueID].sirname );
      printf("***  His/Her score is %.3f                                        ***\n",scores[0].Qscore);
      printf("************************************************************************\n\n");
    #endif
   
    
    locateQuentStuToUni( scores, stuInfo, universities, numOfStu,numberOfDeps  );
     
    
    sortingScoresAccVerbal( scores, stuInfo, numOfStu );
    
    
    #if defined (DEBUG)
      printf("************************************************************************\n");
      printf("***  The Student who has the highest Verbal score is %s %s     ***\n",stuInfo[scores[0].uniqueID].name,
                                                                                stuInfo[scores[0].uniqueID].sirname );
      printf("***  His/Her score is %.3f                                        ***\n",scores[0].Vscore);
      printf("************************************************************************\n\n");
    #endif
    
    
                                         
    locateVerbalStuToUni( scores, stuInfo, universities, numOfStu,numberOfDeps  );
    
    while( selection != 6 ){
               
        printf("***********************************************************************\n");
        printf("Please enter a selection:\n");
        printf("[1] Show Files Contents \n");
        printf("[2] Adding and deleting operations \n");
        printf("[3] Concole outputs: \n");
        printf("[4] Create csv files\n");
        printf("[5] Create html files \n");
        printf("[6] Quit\n");
        printf("***********************************************************************\n\n");
        printf("Your selection: ");
        scanf("%d",&selection);
        
        if( selection == 1 ){
            
            printf("[1] show the informations of students:\n");  
            printf("[2] show the all university departments' informations:\n");
            printf("[3] show address informations of the students:\n");
            printf("Your selection: ");
            scanf("%d",&selection2);
            if( selection2 == 1 ){
                printstuInfos( stuInfo, numOfStu );
            
            }
            else if( selection2 == 2 ){
                printDepartments( universities, numberOfDeps );
                
            }
            else if( selection2 == 3 ){
                printStuAddress( stuInfo, stuAddress, numOfStu );
            
            /*printstuInfos( stuInfo, numOfStu );*/
            /* printDepartments( universities, numberOfDeps );
            /*printStuAddress( stuAddress, numOfStu );*/     
            
            }        
        }
        else if( selection == 2 ){
        
            SortScoresAccUniq( scores, numOfStu );
  
            printf("Please enter a choice :\n");
            printf("Enter 1 for adding operation,\n");
            printf("Enter 2 for deleting operation\n");
            printf(">> ");
    
            scanf("%d",&choice);
    
        if ( choice == 1 )
            addingOpr( stuInfo, stuAddress, universities,scores, &numOfStu, &numberOfDeps );
        else if ( choice == 2 )
            DeletingOpr( stuInfo, universities, &numOfStu, &numberOfDeps );
        else
            printf("Invalid Choice!!!\n");
        
        
        }
        else if( selection == 3 ){
            printf("Please enter a selection: \n");
            printf("[1] Placement information of a student\n");
            printf("[2] Placement information of a university\n");
            printf("[3] Placement information of a department\n");
            printf("[4] Some informations about the exam\n");
            printf("[5] Informations about all universities\n");
            printf("Your selection: ");
            scanf("%d",&selection3);
            scanf("%c",&ignore);
            
            if( selection3 == 1 )
                consAns1(  stuInfo, scores, numOfStu  );
            else if( selection3 == 2 )      
                consAns2( universities, numberOfDeps );
            else if( selection3 == 3 )
                consOut2( universities, numberOfDeps );  
            else if( selection3 == 4 )
                consAns3( stuInfo, universities, numOfStu, numberOfDeps  );
            else if( selection3 == 5 )
                consOut1( universities, numberOfDeps );
        }
        else if ( selection == 4 ){
            csvOut1( universities, stuInfo, numOfStu ,numberOfDeps );
    
            csvOut2( stuInfo, numOfStu );
   
            csvOut3( stuInfo, universities , scores, numOfStu, numberOfDeps );
      
            csvOut4( universities, numberOfDeps );
        
        }
        else if( selection == 5 ){
            
            /* Creates The HTML Files */
            createHtmlPlacement(  stuInfo, scores, numOfStu );
    
            createHtmlStudents( stuInfo, stuAddress, numOfStu );
        
        }
        else if( selection == 6 ){
              return 0;
         
        }
        else {
            
            printf("\nPlease enter valid choice!Enter again:\n");
        
        }
    
    }       
             
    return 0;
    
}


