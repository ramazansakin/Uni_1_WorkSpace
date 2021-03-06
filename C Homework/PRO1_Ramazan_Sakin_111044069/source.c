#include <stdio.h>
#include <time.h>
#include <string.h>
#include "sakin.h"

int readstuInfos( char stuInfoFile[], stuInfo_t stuInfo[] )
{

    int size=0;
    int status, i, j, n;
    char ch, dot;
    FILE* inp;
    inp = fopen( stuInfoFile ,"r");
    
    
    /* reads empty for first row */   
    for ( n=0; ch != '\n' ; ++n )
        fscanf(inp,"%c",&ch);
   
    
    for ( i=0 ; status != EOF ; ++i ){  
        
        j=0;
        status = fscanf(inp,"%c",&ch);
        
        if ( ch == '\n' || status == EOF )
            break;
        
        while ( ch != ';' ){ 
        
            stuInfo[i].IDnum[j] = ch;
            ++j;
            fscanf( inp,"%c",&ch );
                   
        }
        
        stuInfo[i].IDnum[j] = '\0';
        
        j=0;
        fscanf(inp,"%c",&ch);
        
        while ( ch != ';' ){ 
            stuInfo[i].name[j] = ch;
            ++j;
            fscanf( inp,"%c",&ch );
            
        }
        stuInfo[i].name[j] = '\0';
       
            
        j=0;
        fscanf(inp,"%c",&ch);
        while ( ch != ';' ){
            stuInfo[i].sirname[j] = ch;
            ++j;
            fscanf( inp,"%c",&ch ); 
            
        }
        stuInfo[i].sirname[j] = '\0';    
        
        
                
        fscanf(inp,"%d", &stuInfo[i].birthday.day );
        fscanf(inp,"%c", &dot);
        fscanf(inp,"%d", &stuInfo[i].birthday.month );
        fscanf(inp,"%c", &dot);
        fscanf(inp,"%d", &stuInfo[i].birthday.year );
        fscanf( inp,"%c",&ch );

        fscanf( inp,"%c",&ch );
        stuInfo[i].scrType = ch;
        
        if ( status != EOF )
            ++size;

        while ( ch != '\n' || ch == EOF )
            status = fscanf( inp,"%c",&ch );
                        
        if ( status == EOF )
            break;

        
    }
    
    fclose(inp);
    return size;
    
}


void printstuInfos( stuInfo_t stuInfo[], int number )
{

    int i; 

    printf("%-15s  %-12s  %-10s  %-12s  %-5s\n","ID number","Name","Sirname","Birthday","ScoreType");

    for ( i=0 ; i<number ; ++i ){
      
      if( stuInfo[i].isDeleted != 1 ){  
      
        printf("%d)%-13s  ",i+1 ,stuInfo[i].IDnum );
        printf("%-12s  ",stuInfo[i].name);
        printf("%-10s  ", stuInfo[i].sirname);
        printf("%-2d.%-2d.%-4d  ", stuInfo[i].birthday.day,
        stuInfo[i].birthday.month,stuInfo[i].birthday.year );
        printf("%6c\n", stuInfo[i].scrType);
        
      }
        
    }
    
    printf("\n\n");
}


int readDepartments( char departsFile[] ,uni_t universities[MAX_UNI_NUM], int numberOfUni, int* numberOfDeps )
{

    int i, j, n, k;
    char ch=0, dot;
    int status = EOF+1;   /* not equal to EOF in first */
    int num;
    numberOfUni = 1;
    FILE* inp;
    inp = fopen( departsFile ,"r");
    
    
    /* reads empty for first row */   
     while( ch != '\n' ){
        fscanf(inp,"%c",&ch);
 
    }
   
  
    n = 0;
    for ( i=0 ; status != EOF ; ++i ){  
    

        j=0;
        status = fscanf(inp,"%c",&ch);
        
        if ( status == EOF )
            break;
        
        while ( ch != ';' ){ 
        
            universities[i].uniName[j] = ch;
            ++j;
            fscanf( inp,"%c",&ch );
            
        }
        
        universities[i].uniName[j] = '\0';       
        
        fscanf(inp,"%d",&universities[i].uniID);     
        
        if ( i > 1 )
            if ( universities[i-1].uniID != universities[i].uniID  ){
                
                n=0;    /* For second universities' departments */
                numberOfUni++;
            }       
        
        
        fscanf(inp,"%c",&ch); /* for semicolon */
        
        
        j=0;
        fscanf(inp,"%c",&ch);
        while ( ch != ';' ){
            universities[i].departs[n].depName[j] = ch;
            ++j;
            fscanf(inp,"%c",&ch  );
            
        
        }
        
        fscanf(inp,"%d",&universities[i].departs[n].depID);
        
        fscanf(inp,"%c",&ch);  /* for semicolon */
        
        fscanf(inp,"%c",&ch);
        universities[i].departs[n].scrType = ch;
        
        fscanf(inp,"%c",&ch); /*for semicolon*/
        
        fscanf(inp,"%d",&universities[i].departs[n].quota);   
        universities[i].departs[n].emptyQuota = universities[i].departs[n].quota;
        
        ++(*numberOfDeps);  /* Increases Departments number */ 
        ++n;
        
        status = fscanf(inp,"%c",&ch);   /* for NewLine */
        if ( status == EOF  )  /* if the EndOfFile, go out of loop */      
            break;
        
        /*if( i = 50 )
            break;
        */
        
        while ( ch != '\n' ){
           status = fscanf(inp,"%c",&ch);
        }
        /* segmentation for i > 25 */
        if( i == 25 )
            break;
        
        if ( status == EOF )  /* if the EndOfFile, go out of loop */      
            break;
              
    } 
    
    num=1;
    k=0;
    for ( i=0; i<numberOfUni ; ++i ){
        for( j=0 ; j< *numberOfDeps ; ++j ){
            if( universities[j].uniID == universities[j+1].uniID ){
                ++num;  
            }
            else {
                for( n=0 ;n<num ;++n){
                    universities[k].numOfDepAUni=num;
                    k++;
                }
            num=1;
            }
        
        }
    }    
    
    
    universities[i].departs[n].depID = EMPTY;   /* For last unıversty */

    fclose(inp);
    return numberOfUni;

}


void printDepartments( uni_t universities[MAX_UNI_NUM], int number )
{
    int i, n=0;


    printf("%-12s %-5s  %-20s  %-5s  %-10s  %-5s\n","Universities", "UniID",
                                    "Departments","DepID",
                                    "score Type","Quota");
    for ( i=0 ; i<number ; ++i ){
        
        if( universities[i].isDeleted != 1 && universities[i].departs[n].isDeleted != 1 ){
        
        
        printf("%-11s  ", universities[i].uniName );
        printf("%-5d  ", universities[i].uniID );
        
        if ( strcmp( universities[i].uniName, universities[i-1].uniName ) != 0 ){
            n=0;
        }
        
        printf("%-20s  ", universities[i].departs[n].depName );
        printf("%-5d  ", universities[i].departs[n].depID );
        printf("%-10c  ", universities[i].departs[n].scrType);
        printf("%-5d  \n",universities[i].departs[n].quota );
        ++n;      
      }   
    }
    printf("\n\n");
    
}


int readPreferences( char prefsFile[], stuInfo_t stuInfo[20], int numOfStu  )
{

    int i, j, n;
    char ch;
    int status = EOF+1, num;   /* not equal to EOF in first */
    FILE* inp;
    inp = fopen( prefsFile ,"r");
    
    
    status = fscanf(inp,"%c",&ch);
    /* reads empty for first row */   
    for ( n=0; ch != '\n' ; ++n ){
        fscanf(inp,"%c",&ch);
        if ( status == EOF )
            break;
    }
   
    for ( i=0 ; i<numOfStu ; ++i ){  
         
        stuInfo[i].prefNum = 0;
        status = fscanf(inp,"%c",&ch);
        
        if ( status == EOF )
            break;
        
        /* ID */
        while ( ch != ';' ){
            
            fscanf( inp,"%c",&ch );
           
        }
        
        
        
        for ( j=0 ; j<MAXPREF ; ++j ){
            
            status = fscanf(inp,"%d",&num);
            if( status == 0 )
                break;
            stuInfo[i].preferences[j].uniPref=num;          
            ++stuInfo[i].prefNum;
            fscanf(inp,"%c",&ch);   /* semicolon */
            fscanf(inp,"%d",&stuInfo[i].preferences[j].depPref);
            fscanf(inp,"%c",&ch);   /* semicolon */
            
        }
        
        if ( j != MAXPREF ){
            while ( ch != '\n' || ch == ';' )
                status = fscanf(inp,"%c",&ch);
        }
        
        
            if ( status == EOF )    
                break;
    }
        
    fclose(inp);

}


int readScores( char scoresFile[], score_t scores[], int numOfStu )
{
       
    int i, j, n, s;
    char ch;
    int status = EOF+1;   /* not equal to EOF in first */
    FILE* inp;
    inp = fopen( scoresFile ,"r");
    
    status = fscanf(inp,"%c",&ch);
    if ( status == EOF )
        return 0;   /* The File is empty */
    
    /* reads empty for first row */   
    for ( n=0; ch != '\n' ; ++n ){
        fscanf(inp,"%c",&ch);
 
    }
    
    for ( i=0 ; i<numOfStu ; ++i ){  
        
        status = fscanf(inp,"%c",&ch);
        
        if ( status == EOF )
            break;
        s=0;
        while ( ch != ';' ){
            scores[i].IDnum[s]=ch;
            ++s;
            fscanf( inp,"%c",&ch );   
        }
        
        fscanf( inp,"%lf",&scores[i].Qscore);
        fscanf( inp,"%c",&ch ); /* semicolon */
        fscanf( inp,"%lf",&scores[i].Vscore);
        scores[i].uniqueID = i;
        fscanf( inp,"%c",&ch ); /* newLine */
        
        
    }
        
    fclose(inp);
    
}



int readstuAddress( char stuAddressFile[], stuAddress_t stuAddress[], int numOfStu )
{

    int status, i, j, n;
    char ch ;
    FILE* inp;
    inp = fopen( stuAddressFile ,"r");
    
    
    fscanf(inp,"%c",&ch);
    /* reads empty for first row */   
    for ( n=0; ch != '\n' ; ++n ){
        status = fscanf(inp,"%c",&ch);
 
    }
   
    
    for ( i=0 ; i<numOfStu ; ++i ){
        
        fscanf(inp,"%c",&ch);
        
        j=0;
        while ( ch != ';' ){ 
        
            stuAddress[i].IDnum[j] = ch;
            ++j;
            fscanf( inp,"%c",&ch );
            
        }
        
        stuAddress[i].IDnum[j] = '\0';
        
        j=0;
        fscanf(inp,"%c",&ch);
        
        while ( ch != ';' ){ 
            stuAddress[i].phone[j] = ch;
            ++j;
            fscanf( inp,"%c",&ch );
            
        }
        stuAddress[i].phone[j] = '\0';    
            
        j=0;
        fscanf(inp,"%c",&ch);
        
        
        while ( ch != ';' ){ 
            stuAddress[i].mail[j] = ch;
            ++j;
            fscanf( inp,"%c",&ch ); 
            
        }
        stuAddress[i].mail[j] = '\0';
        
        
        j=0;
        fscanf(inp,"%c",&ch);
        
         /* Tek dongude yaptıgımda segmentation error hatası
         * oldugu icin iki donguye ayırdım..
        */
        
            while ( ch != '\n'  ){ 
                stuAddress[i].address[j] = ch;
                ++j;
                fscanf( inp,"%c",&ch ); 
                
            }
            stuAddress[i].address[j] = '\0';
            
        
    }
    
    fclose(inp);

}


void printStuAddress( stuInfo_t stuInfo[], stuAddress_t stuAddress[], int numOfStu )
{

    int i, n=0;

    printf("%-11s  %-11s  %-15s  %-25s\n","ID number","Phone","Mail","Address");

    for ( i=0 ; i<numOfStu ; ++i ){
      
      if( stuInfo[i].isDeleted != 1 ){
        
        printf("%-11s  %-11s  %-15s  %-25s\n", stuAddress[i].IDnum,
        stuAddress[i].phone, stuAddress[i].mail
        , stuAddress[i].address );     
        
      }
        
    }


}


int sortingScoresAccQuent( score_t scores[], stuInfo_t stuInfo[], int numOfStu )
{

    int i, n; 
    score_t temp;
    srand(time(NULL));
    int xrandom;
    xrandom = rand()%2;   /* xrandom is either 0 or 1 ( random ) */
    
    
        /*  Sorting according to Quantitative */ 
    for ( n=0; n<numOfStu ; ++n ){
    
        for ( i=0 ; i<numOfStu-1 ; ++i ){
        
            if ( scores[i].Qscore < scores[i+1].Qscore ){
            
                temp = scores[i];
                scores[i] = scores[i+1];
                scores[i+1] = temp;          
                
            }
            else if( scores[i].Qscore == scores[i+1].Qscore ){
                  
                  if (stuInfo[scores[i].uniqueID].birthday.year < 
                      stuInfo[scores[i+1].uniqueID].birthday.year  ){
                        temp = scores[i];
                        scores[i] = scores[i+1];
                        scores[i+1] = temp; 
                    
                 }     
                else if ( stuInfo[scores[i].uniqueID].birthday.year 
                == stuInfo[scores[i+1].uniqueID].birthday.year ){
                    if ( stuInfo[scores[i].uniqueID].birthday.month 
                < stuInfo[scores[i+1].uniqueID].birthday.month ){
                        temp = scores[i];
                        scores[i] = scores[i+1];
                        scores[i+1] = temp;
                    
                    }
                    else if( stuInfo[scores[i].uniqueID].birthday.month 
                    == stuInfo[scores[i+1].uniqueID].birthday.month ){
                        if( stuInfo[scores[i].uniqueID].birthday.day 
                           < stuInfo[scores[i+1].uniqueID].birthday.day ){
                            
                            temp = scores[i];
                            scores[i] = scores[i+1];
                            scores[i+1] = temp;
                        
                        }
                        else if( stuInfo[scores[i].uniqueID].birthday.day 
                                 == stuInfo[scores[i+1].uniqueID].birthday.day ){
                                 /* selects randomly */
                                 /* if x is not 2 or 2*x, changes them( xrandom is not constant ) */ 
                                    if( xrandom == 1 ){
                                        temp = scores[i];
                                        scores[i] = scores[i+1];
                                        scores[i+1] = temp;
                                    
                                    }   
                                 
                        }
                    
                    }
                   
        
              }

          }   
  
      }

   }


}


int locateQuentStuToUni( score_t scores[], stuInfo_t stuInfo[], uni_t universities[],
                     int numOfStu, int numOfDep  ){

    int i, j, k, n;
    
    
    for ( i=0 ; i<numOfStu ; ++i ){
           
        for( j=0 ; j<stuInfo[scores[i].uniqueID].prefNum ; ++j ){
            
            if ( stuInfo[scores[i].uniqueID].isLocated != 1 &&
                 stuInfo[scores[i].uniqueID].scrType == 'Q'){
                
                
                for ( k=0 ; k<numOfDep; ++k ){
                    if ( stuInfo[scores[i].uniqueID].preferences[j].uniPref ==
                     universities[k].uniID ){
                        
                        
                    for( n=0; n<universities[k].numOfDepAUni ; ++n){
                           
                    if( stuInfo[scores[i].uniqueID].preferences[j].depPref 
                         ==  universities[k].departs[n].depID       &&
                         universities[k].departs[n].emptyQuota > 0  &&
                         universities[k].departs[n].scrType == 'Q'  &&
                         stuInfo[scores[i].uniqueID].isDeleted != 1 &&
                         universities[k].isDeleted != 1             &&
                         universities[k].departs[n].isDeleted != 1     ){
                                
                                /* saves informations to stuInfos */
                                strcpy( stuInfo[scores[i].uniqueID].depName,
                                        universities[k].departs[n].depName );
                               stuInfo[scores[i].uniqueID].depName[strlen(universities[k].departs[n].depName)] = '\0';         
                               
                               strcpy( stuInfo[scores[i].uniqueID].uniName,universities[k].uniName );
                               stuInfo[scores[i].uniqueID].uniName[strlen(universities[k].uniName)] = '\0'; 
                               
                               stuInfo[scores[i].uniqueID].isLocated = 1;
                               --universities[k].departs[n].emptyQuota;
                               universities[k].departs[n].minScore = scores[i].Qscore;
                               
                               if( j == 0 )
                                    stuInfo[scores[i].uniqueID].isFirstPref = 1;
                               
                               if( universities[k].departs[n].maxScoreOK != 1 ){
                                    universities[k].departs[n].maxScore = scores[i].Qscore;
                                    universities[k].departs[n].maxScoreOK = 1;
                                    
                               }
                                
                           }                   
                            
                        
                        }
                     
                   }   
                       
                       
                
                }           
          
                  
            }      
        
    
        }
    
    }


}


int sortingScoresAccVerbal( score_t scores[], stuInfo_t stuInfo[], int numOfStu )
{

    int i, n; 
    score_t temp;
    srand(time(NULL));
    int randomValue;
    randomValue = rand()%2;   /* randomValue is either 0 or 1 ( random ) */
    
    
        /*  Sorting according to Verbal scores */ 
    for ( n=0; n<numOfStu ; ++n ){
    
        for ( i=0 ; i<numOfStu-1 ; ++i ){
                 
            
            if ( scores[i].Vscore < scores[i+1].Vscore ){

                temp = scores[i];
                scores[i] = scores[i+1];
                scores[i+1] = temp;
                
            }
            else if( scores[i].Vscore == scores[i+1].Vscore ){
                  
                  if (stuInfo[scores[i].uniqueID].birthday.year < 
                      stuInfo[scores[i+1].uniqueID].birthday.year  ){
                        temp = scores[i];
                        scores[i] = scores[i+1];
                        scores[i+1] = temp; 
                    
                 }     
                else if ( stuInfo[scores[i].uniqueID].birthday.year 
                == stuInfo[scores[i+1].uniqueID].birthday.year ){
                    if ( stuInfo[scores[i].uniqueID].birthday.month 
                < stuInfo[scores[i+1].uniqueID].birthday.month      ){
                        
                        temp = scores[i];
                        scores[i] = scores[i+1];
                        scores[i+1] = temp;
                    
                    }
                    else if( stuInfo[scores[i].uniqueID].birthday.month 
                    == stuInfo[scores[i+1].uniqueID].birthday.month ){
                        if( stuInfo[scores[i].uniqueID].birthday.day 
                           < stuInfo[scores[i+1].uniqueID].birthday.day ){
                            
                            temp = scores[i];
                            scores[i] = scores[i+1];
                            scores[i+1] = temp;
                        
                        }
                        else if( stuInfo[scores[i].uniqueID].birthday.day 
                                 == stuInfo[scores[i+1].uniqueID].birthday.day ){
                                 /* selects randomly */
                                 /* if randomValue is not 2 or 2x, changes them
                                 *  ( randomValue is not constant )
                                */ 
                                    
                                    if( randomValue == 1 ){
                                        temp = scores[i];
                                        scores[i] = scores[i+1];
                                        scores[i+1] = temp;
                                    
                                    }   
                                 
                        }
                    
                    }
                   
        
              }

          }   
  
      }
    
   }
   
}


int locateVerbalStuToUni( score_t scores[], stuInfo_t stuInfo[], uni_t  universities[], int numOfStu,int numOfDep  )
{

    int i, j, k, n;
    char cast;    
    
    
    for ( i=0 ; i<numOfStu ; ++i ){
           
        for( j=0 ; j<stuInfo[scores[i].uniqueID].prefNum ; ++j ){
            
            if ( stuInfo[scores[i].uniqueID].isLocated != 1 &&
                 stuInfo[scores[i].uniqueID].scrType == 'V'){
                
                
                for ( k=0 ; k<numOfDep; ++k ){
                    if ( stuInfo[scores[i].uniqueID].preferences[j].uniPref ==
                     universities[k].uniID ){
                        
                        for( n=0; n<universities[k].numOfDepAUni ; ++n){
                           
                            if( stuInfo[scores[i].uniqueID].preferences[j].depPref 
                                == universities[k].departs[n].depID         &&
                                universities[k].departs[n].emptyQuota > 0   &&
                                universities[k].departs[n].scrType == 'V'   &&
                                stuInfo[scores[i].uniqueID].isDeleted != 1  &&
                                universities[k].isDeleted != 1              &&
                                universities[k].departs[n].isDeleted != 1      ){
                                
                                /* saves informations to stuInfos */
                                strcpy( stuInfo[scores[i].uniqueID].depName,
                                        universities[k].departs[n].depName );
                               stuInfo[scores[i].uniqueID].depName[strlen(universities[k].departs[n].depName)] = '\0';         
                               
                               strcpy( stuInfo[scores[i].uniqueID].uniName,universities[k].uniName );
                               stuInfo[scores[i].uniqueID].uniName[strlen(universities[k].uniName)] = '\0'; 
                               
                               stuInfo[scores[i].uniqueID].isLocated = 1;
                               --universities[k].departs[n].emptyQuota;
                               universities[k].departs[n].minScore = scores[i].Vscore;
                               
                               if(  universities[k].departs[n].maxScoreOK != 1 ){
                                    universities[k].departs[n].maxScore = scores[i].Vscore;
                                    universities[k].departs[n].maxScoreOK = 1;
                                    
                               }
                                
                           }                   
                        
                        }
                     
                   }   
                       
                       
                
                }           
                
                  
            }      
            else if ( stuInfo[scores[i].uniqueID].isLocated != 1 &&
                 stuInfo[scores[i].uniqueID].scrType == 'Q'   ) {  
                   /* If he/she is a quantitative student, if he/she didn't locate anywhere
                   * and if his/her last choice is Verbal Department, and
                  *  emptyQuota of University that he/she wants is empty ,
                 *   locate him/her to universty...  
                */
                
                    
                for ( k=0 ; k<numOfDep; ++k ){
                    if ( stuInfo[scores[i].uniqueID].preferences[j].uniPref ==
                     universities[k].uniID ){
                        
                        for( n=0; n<universities[k].numOfDepAUni ; ++n){
                           
                            if( stuInfo[scores[i].uniqueID].preferences[j].depPref 
                       == universities[k].departs[n].depID              &&    
                       universities[k].departs[n].emptyQuota > 0        &&
                       universities[k].departs[n].scrType == 'V'        &&
                       stuInfo[scores[i].uniqueID].isDeleted != 1       &&
                       universities[k].isDeleted != 1                   &&
                       universities[k].departs[n].isDeleted != 1             ){ 
                                
                                /* saves informations to stuInfos */
                               strcpy( stuInfo[scores[i].uniqueID].depName,
                                        universities[k].departs[n].depName );
                               stuInfo[scores[i].uniqueID].depName[strlen(universities[k].departs[n].depName)] = '\0';         
                               
                               strcpy( stuInfo[scores[i].uniqueID].uniName,universities[k].uniName );
                               stuInfo[scores[i].uniqueID].uniName[strlen(universities[k].uniName)] = '\0'; 
                               
                               stuInfo[scores[i].uniqueID].isLocated = 1;
                               --universities[k].departs[n].emptyQuota;
                               universities[k].departs[n].minScore = scores[i].Vscore;
                               
                               if( universities[k].departs[n].maxScoreOK != 1 ){
                                    universities[k].departs[n].maxScore = scores[i].Vscore;
                                    universities[k].departs[n].maxScoreOK = 1;
                                    
                               }
                                
                             
                           }                   
                        
                        }
                     
                   }   
                       
                       
                
                }
                    
         
          }
            
            
        }
    
    }
    
}




void consAns1( stuInfo_t stuInfo[], score_t scores[], int numOfStu )
{

    char name[15], sirname[15], IDnumber[12];
    int i, found=0, notLocated=0;
    
    printf("Please enter the student name ,sirname and ID number\n");
    printf("to learn his/her placement result:  \n");
    printf("ID number: ");
    scanf("%s",IDnumber);
    printf("Name: ");
    scanf("%s",name);
    printf("Sirname: ");
    scanf("%s",sirname);
    
    
    for( i=0 ; i<numOfStu ; ++i ){
        if( strcmp(stuInfo[scores[i].uniqueID].IDnum, IDnumber) == 0  ){
            
             if ( stuInfo[scores[i].uniqueID].isLocated == 1 ){   
                if( stuInfo[scores[i].uniqueID].uniName != '\0' ){
                    
                    printf("\n**************************  Congratilations  ***************************\n");
                    printf("Quantitative score: %.3f\nVerbal score: %.3f\n",
                                                                    scores[i].Qscore,
                                                                    scores[i].Vscore);
                    printf("University: %s\n",stuInfo[scores[i].uniqueID].uniName);
                    printf("Department: %s\n",stuInfo[scores[i].uniqueID].depName);
                    printf("************************************************************************\n\n");                    
                    found=1;         
                }
               
               }
               else if( stuInfo[scores[i].uniqueID].isLocated !=1 )
                    found=1;
                    notLocated=1;
            }
            
            
     }
        
        
             
        if ( found == 1 && notLocated == 1  )
            printf("\nThe student could not locate a university!!!\n");
        
        if( found != 1 ){
            printf("\n!!The Enterance was not found.Check the informations!!\n");  
     
     }
            

}
     

void consAns2( uni_t universities[], int numOfDep  ){
    
    char uniName[20];
    int i, j, found=0;
    char ignore;
    
    printf("Please enter a university name to learn about Placement Informations:");
    gets(uniName);
    
    for( i=0 ; i<numOfDep ; ++i ){
        
        if( found == 1 )
            break;
        
        if( strcmp( universities[i].uniName ,uniName ) == 0 ){
            printf("University: %s\n",universities[i].uniName);
            printf("%-16s  %-5s  %-5s  %-11s   %-20s\n","Departments",  "DepID","Quota", "Empty Quota","Number Of Located Student");
            for( j=0; j<universities[i].numOfDepAUni ; ++j ){
                printf("%-16s  %-5d  %-5d  %-11d   %-5d\n",universities[i+j].departs[j].depName,
                                                       universities[i+j].departs[j].depID,
                                                       universities[i+j].departs[j].quota,
                                                       universities[i+j].departs[j].emptyQuota,
                                                       universities[i+j].departs[j].quota - 
                                                       universities[i+j].departs[j].emptyQuota);
            
            
            found=1;
            }
        }
        

    }
    printf("\n\n");


}


void consOut1( uni_t universities[], int numOfDep ){

    int i, n=0;


    printf("%-12s  %-5s  %-20s  %-5s  %-6s  %-5s  %-7s\n","Universities", "UniID",
                                    "Departments","DepID",
                                    "sType","Quota","E.Quota" );
    for ( i=0 ; i<numOfDep ; ++i ){
        
        printf("%-12s  ", universities[i].uniName );
        printf("%-5d  ", universities[i].uniID );
        if ( strcmp( universities[i].uniName, universities[i-1].uniName ) != 0 ){
            n=0;
            
        }
        
        printf("%-20s  ", universities[i].departs[n].depName );
        printf("%-5d  ", universities[i].departs[n].depID );
        printf("%-6c  ", universities[i].departs[n].scrType);
        printf("%-5d  ",universities[i].departs[n].quota );
        printf("%-7d  \n",universities[i].departs[n].emptyQuota );
        
        ++n;      
        
    }
    printf("\n");
    
    printf("%-15s  %-20s  %-9s   %-9s\n","Universities",
                                    "Departments","MinScore","MaxScore" );
    for ( i=0 ; i<numOfDep ; ++i ){
        
        printf("%-15s  ", universities[i].uniName );
        if ( strcmp( universities[i].uniName, universities[i-1].uniName ) != 0 ){
            n=0;
            
        }
        
        printf("%-20s  ", universities[i].departs[n].depName );
        printf("%8.3f   ",universities[i].departs[n].minScore );
        printf("%8.3f  \n",universities[i].departs[n].maxScore );
        
        ++n;      
        
    }
    
    
    printf("\n\n");
        
}


void consOut2( uni_t universities[], int numOfDep )
{

    char depName[20], uniName[20];
    int i, n, j;
    int found =0, selection;
    char ignore;

    printf("Please enter the university name and department name to learn\nabout Placement Informations: \n");
    printf("University name: ");
   
    gets(uniName);
    printf("Department name: ");
    gets(depName);
    printf("%s--%s",uniName,depName);
   
    
    for ( i=0 ; i<numOfDep ; ++i ){
        
        
        if ( strcmp( uniName, universities[i].uniName ) == 0  ){
            
            for( j=0 ; j< numOfDep ; ++j ){
             
             if ( strcmp( universities[i].uniName, universities[i-1].uniName ) != 0 ){
                    n=0;
                }
            
             if ( strcmp( depName, universities[i].departs[j].depName  ) == 0 ){
                
                printf("%-20s  %-5s  %-5s  %-10s  %-8s  %-8s\n","Department",
                                    "DepID","Quota","EmptyQuota","MinScore","MaxScore" );
                printf("%-20s  ", universities[i].departs[j].depName );
                printf("%-5d  ", universities[i].departs[j].depID );
                printf("%-5d  ", universities[i].departs[j].quota);
                printf("%-10d  ",universities[i].departs[j].emptyQuota );      
                printf("%-8.3f  ",universities[i].departs[j].minScore );
                printf("%-8.3f  \n",universities[i].departs[j].maxScore );
            
                found=1;
                
             }        
         ++n;
         if( found == 1 )
            break;
         }
        
      }
   
    if( found == 1 )
        break;
    }  
    if( found != 1 ){
        printf("The Department was not found!!\n\n");
        
    }

}



void consAns3( stuInfo_t stuInfo[], uni_t  universities[], int numOfStu, int numOfDep  )
{

    int i, n;
    int totEmpQuota=0;
    int numOfStuPlaced=0;
    int numFirstPref=0;    
    int totQuota=0;

    for ( i=0 ; i<numOfDep ; ++i ){
        
        if ( strcmp( universities[i].uniName, universities[i-1].uniName ) != 0 ){
                n=0;
            }
                
            totEmpQuota += universities[i].departs[n].emptyQuota;                       
            totQuota += universities[i].departs[n].quota;
            
        ++n;
    }    
    
    
    
    for ( i=0 ; i<numOfStu ; ++i ){
        
        if( stuInfo[i].isLocated == 1 )
            numOfStuPlaced += stuInfo[i].isLocated;
        
        if( stuInfo[i].isFirstPref == 1 )
            numFirstPref += stuInfo[i].isFirstPref;   
            
    }
    
    printf("******************* Some Placement Informations ************************\n");
    printf("Number Of Student in the exam: %d\n",numOfStu );
    printf("Number of student placed to a uniersity: %d\n", numOfStuPlaced );
    printf("Number of student placed into his/her first preference: %d\n",numFirstPref);
    printf("Number of total quota of all Universities' Departments: %d\n", totQuota);
    printf("Number of total empty quota of all Universities' Departments: %d\n", totEmpQuota );
    printf("****************************************************************************\n");
    
    printf("\n\n");

}


void csvOut1( uni_t universities[], stuInfo_t stuInfo[] , int numOfStu, int numOfDep )
{

    int i, j, n=0;
    int times=0, times2=0;
    FILE* outp;
    outp = fopen("PlacementToDepartments.csv","w");
    
    
    for ( i=0 ; i < numOfDep ; ++i ){
        
        if ( strcmp( universities[i].uniName, universities[i-1].uniName ) != 0 ){
                n=0;
            }
        for( n=0 ; n<universities[i].numOfDepAUni ; ++n ){    
            
            for( j=0 ; j<numOfStu ; ++j ){           
                if( strcmp( universities[i].uniName, stuInfo[j].uniName ) == 0 &&
                    strcmp( universities[i].departs[n].depName, stuInfo[j].depName ) == 0    ){
                        
                        if( times == 0 ){
                            fprintf(outp,"%-15s;%-20s;\n","University","Department");
                            fprintf(outp,"%-15s;%-20s;\n",universities[i].uniName,universities[i].departs[n].depName );
                            fprintf(outp,"%-12s;%-12s;%-12s;\n","ID","Name","SirName");
                            ++times;
                           
                        }
                        
                        fprintf(outp,"%-12s;%-12s;%-12s;\n",stuInfo[j].IDnum, stuInfo[j].name , 
                                                                       stuInfo[j].sirname );
                       times2=0;    /*  Space for between two universities */
                    }
                            
            }
        
        times = 0;
        }
      if( times2 == 0 ){    
          fprintf(outp,"\n\n");        
          ++times2; 
      }
    
    }
    
    printf("The files were prepared succesfully...\n");
    fclose(outp);

}


void csvOut2( stuInfo_t stuInfo[], int numOfstu )
{

    int i;
    FILE* outp;    
    outp = fopen("PlacementOfStudents.csv","w");    
            
    for( i=0 ; i<numOfstu ; ++i ){
        
        if ( stuInfo[i].isLocated == 1 ){
            fprintf(outp,"%-12s;%-12s;\n","Name","Sirname");
            fprintf(outp,"%-12s;%-12s;\n",stuInfo[i].name,stuInfo[i].sirname);
            fprintf(outp,"%-15s;%-15s;\n","University","Department");
            fprintf(outp,"%-15s;%-15s;\n\n",stuInfo[i].uniName, stuInfo[i].depName );
        }
        
    }

    fclose(outp);

}


void SortScoresAccUniq( score_t scores[], int numOfStu )
{

    int i, j;
    score_t temp;
    
    
    for( i=0 ; i<numOfStu ; ++i ){
        
        for( j=0 ; j<numOfStu ; ++j ){    
        
            if( scores[j].uniqueID == i ){
                temp = scores[j];
                scores[j] = scores[i];
                scores[i] = temp;
            
            }
                
        }  

    }


}


void csvOut3(  stuInfo_t stuInfo[], uni_t universities[] , score_t scores[], int numOfStu, int numOfDep )
{
    
    int i, j, n=0;
    int times=0, times2=0;
    char uniName[20];
    char ignore;
    FILE* outp;
    outp = fopen("PlacementToUni.csv","w");
    
    printf("Please enter a university name for writing to csv file about Placement Information> ");
    scanf("%c",&ignore);
    gets(uniName);
    
    
    for( i=0 ; i<numOfStu ; ++i ){           
                     
                
        if( strcmp( uniName , stuInfo[i].uniName  ) == 0 ){
                        
            if( times == 0 ){      
                
                fprintf(outp,"%-15s;\n","University");
                fprintf(outp,"%-15s;\n",stuInfo[i].uniName );
                fprintf( outp,"%-12s;%-12s;%-12s;%-15s;%-8s;%-8s;\n","IDnumber","Name",
                                                              "Sirname","Department","Vscore","Qscore");
                ++times;
                       
            }     
        
            
            fprintf( outp,"%-12s;%-12s;%-12s;%-15s;%-8.3f;%-8.3f;\n",stuInfo[i].IDnum, stuInfo[i].name , 
                                                               stuInfo[i].sirname, stuInfo[i].depName,
                                                                scores[i].Vscore, scores[i].Qscore );
        }
      
    }
    
    printf("The file was prepared succesfully...\n");
    fclose(outp);
   
}


void csvOut4( uni_t universities[],  int numOfDep )
{

    int i, n=0;
    FILE* outp;
    outp = fopen("LastStatusOfDepartment.csv","w");

    fprintf(outp,"%-15s;%-20s;%-5s;%-8s;%-8s;%-8s;\n","Universities",
                                    "Departments", "Quota","E.Quota","MaxScore","MinScore");
    
    for ( i=0 ; i<numOfDep ; ++i ){
        
        fprintf(outp,"%-15s;", universities[i].uniName );
        
        if ( strcmp( universities[i].uniName, universities[i-1].uniName ) != 0 ){
            n=0;
        }
        
        fprintf(outp,"%-20s;", universities[i].departs[n].depName );
        fprintf(outp,"%-5d;",universities[i].departs[n].quota );
        fprintf(outp,"%-8d;",universities[i].departs[n].emptyQuota );
        fprintf(outp,"%-8.3f;",universities[i].departs[n].maxScore );
        fprintf(outp,"%-8.3f;\n",universities[i].departs[n].minScore );
        ++n;      
        
    }
    
    printf("The file was prepared succesfully...\n");
    fclose(outp);
    


}


void DeletingOpr( stuInfo_t stuInfo[], uni_t universities[], int *numOfStu, int *numOfDep  )
{

    int i, j;
    char choice, ignore;
    char ID[15];
    char DeletedUni[15];
    char deletedDep[15];
    int found=0, selection;
    
    
    
    printf("Please enter a choice: \n");
    printf("[S] for deleting a student \n");
    printf("[U] for deleting a university \n");
    printf("[D] for deleting a department> ");
    
    scanf("%c",&ignore);
    scanf("%c",&choice);

    switch( choice ){
        case 'S':
        case 's':
                printf("Please enter the student's ID you want to delete: ");
                scanf("%s",ID);    
                for( i=0 ; i< (*numOfStu) ; ++i ){
        
                    if( strcmp(stuInfo[i].IDnum, ID) == 0  ){
                        stuInfo[i].isDeleted = 1;
                        found = 1;
                        
                    }
                            
                }
                if( found != 1 ){
                        printf("The Student was not found!\n");
                        
                    }
                    else if( found == 1 ){
                        printf("The student was deleted succesfully!\n");
                    }
                    
                break;
        case 'U':
        case 'u':
                printf("Please enter the university's name you want to delete: ");
                scanf("%c",&ignore);
                gets(DeletedUni);
                
                for ( i=0 ; i< (*numOfDep) ; ++i ){
                    
                    if( strcmp( DeletedUni, universities[i].uniName  ) == 0  ){
                        universities[i].isDeleted = 1;
                        found = 1;
                        
                    }
                
                }
                if( found != 1 ){
                        printf("The University name was not found!!!\n");     
                
                }
                else if( found == 1 ){
                        printf("The University name was deleted succesfully!\n");
                }
                break;
                    
        case 'D':
        case 'd':
                printf("Please enter the department's name and its University's name  you want to delete: \n");
                scanf("%c",&ignore);
                printf("University name: ");
                gets(DeletedUni);
                printf("Departments name: ");
                gets(deletedDep);
                
                for ( i=0 ; i< (*numOfDep) ; ++i ){
                   
                    if( strcmp(DeletedUni, universities[i].uniName ) == 0  ){
                        
                        for ( j=0 ; j<universities[i].numOfDepAUni ; ++j )
                        
                            if ( strcmp( deletedDep, universities[i].departs[j].depName ) == 0 ){
                                universities[i].departs[j].isDeleted = 1;
                                found = 1;
                                
                            }                       
                        }                    
                    
                    }
                    if( found != 1 ){
                        printf("The department's name or its University's name was not found!!!\n");    
                        
                    }
                    else if( found == 1 ){
                        printf("The department name was deleted succesfully!\n");
                    }
                
                    break;
                    
        default:
            printf("Please enter a valid choice!\n"); 
        
        }


}



void addingOpr( stuInfo_t stuInfo[], stuAddress_t stuAddress[], uni_t universities[],
                                     score_t scores[], int* numOfStu, int* numOfDep )
{

    int i, temp, j, selection;    
    char choice;
    char dot, ignore;
    int index, index2, found=0, number;
    char newUni[25];
    int numberOfDeps, num;
    
    numberOfDeps = *numOfDep;
    
    
    printf("Please enter a choice:\n");
    printf("[S] for add a student\n");
    printf("[U] for add a new university and add departments\n");
    printf("[D] for add departments into a spesific university> ");
    
    scanf("%c",&ignore);    /* For '\n' character */
    scanf("%c",&choice);


    switch( choice ){
        case 'S':
        case 's':   
                index = ++(*numOfStu);
                printf("Please enter the student informations:\n");
                printf("Name: ");          
                scanf("%c",&ignore);
                gets(stuInfo[index-1].name);
                printf("Sirname: ");
                scanf("%s",stuInfo[index-1].sirname );
                printf("ID: ");
                scanf("%s",stuInfo[index-1].IDnum );
                
                strcpy(stuAddress[index-1].IDnum,stuInfo[index-1].IDnum );
                stuAddress[index-1].IDnum[12] = '\0';
                strcpy(scores[index-1].IDnum,stuInfo[index-1].IDnum );
                scores[index-1].IDnum[12] = '\0';
                
                printf("Birhday ( as 12.05.1993 ): ");
                scanf("%d%c%d%c%d",&stuInfo[index-1].birthday.day, &dot, &stuInfo[index-1].birthday.month,
                                                                      &dot, &stuInfo[index-1].birthday.year );
                scanf("%c",&ignore);    /* For '\n' character */
                printf("Score type: ");
                scanf("%c",&stuInfo[index-1].scrType);
                printf("Address Information:\n");
                printf("Phone: ");
                scanf("%s",stuAddress[index-1].phone);
                printf("Mail: ");
                scanf("%s",stuAddress[index-1].mail);
                printf("Adress :\n");
                scanf("%c",&ignore);
                gets(stuAddress[index-1].address);
                printf("Please enter scores:\n");
                printf("Quentitative score: ");
                scanf("%lf",&scores[index-1].Qscore );
                printf("Verbal score: ");
                scanf("%lf",&scores[index-1].Vscore);
                printf("Please enter preferences: \n");
                printf("preferences number: ");
                scanf("%d",&stuInfo[index-1].prefNum );
                scores[index-1].uniqueID = index-1;
                
                printf("Preferences\n");
                
                j=0;
                for ( i=0 ; i<stuInfo[index-1].prefNum ;++i ){
                    printf("%d. Preference:\n",i+1);
                    scanf("%c",&ignore);    /* For '\n' character */
                    printf("University ID: ");
                    scanf("%d",&stuInfo[index-1].preferences[j].uniPref);
                    printf("Department ID: ");
                    scanf("%d",&stuInfo[index-1].preferences[j].depPref);
                    scanf("%c",&ignore);    /* For '\n' character */
                    ++j;
                }
                printf("The Student's informations was saved to files succesfully...\n");
                
                break;
        
        case 'U':
        case 'u':
                
                index = ++numberOfDeps;
                printf("Please enter the University information: \n");
                printf("University name: ");
                scanf("%c",&ignore);
                gets(universities[index-1].uniName);
                /*scanf("%c",&ignore); /* For '\n' character */
                printf("Please enter the university ID: ");
                scanf("%d",&universities[index-1].uniID);
                printf("How many department do you want to add into the new university: ");
                scanf("%d",&num );
                universities[index-1].numOfDepAUni = num;
                
                printf("Please enter department(s) informations: \n");
                for ( i=0 ; i<num ; ++i ){
                    
                    if ( i>0 )
                      index = ++(*numOfDep);
                      
                    printf("For %d.university:\n",i+1);
                    printf("Department name: ");
                    scanf("%c",&ignore);
                    gets(universities[index-1].departs[i].depName);
                    printf("Department ID: ");
                    scanf("%d",&universities[index-1].departs[i].depID );
                    scanf("%c",&ignore); /* For '\n' character */ 
                    printf("Score Type: ");
                    scanf("%c",&universities[index-1].departs[i].scrType);   
                    printf("Quota: ");
                    scanf("%d",&universities[index-1].departs[i].quota);
                    /* First status */
                    universities[index-1].departs[i].emptyQuota = universities[index-1].departs[i].quota; 
                  
                  }  
                    
                    printf("The university and departments were added succesfully...\n");
                
                
                break;
        case 'D':
        case 'd':
                printf("Which university do you want to add a department: \n");
                printf("University name: ");
                scanf("%c",&ignore);
                
                gets(newUni);
                
                index = ++(*numOfDep);
                
                for ( j=0 ; j < (*numOfDep) ; ++j ){    
                 
                 if( strcmp( newUni, universities[j].uniName ) == 0 ){   
                    
                    printf("How many department do you want to add into %s: \n",universities[j].uniName);
                    scanf("%d",&number);
                    break;
                    }
                }
                 
                    universities[index-1].numOfDepAUni=number;
                    universities[index-1].numOfDepAUni += number;
                    
                    printf("Please enter department informations: \n");
                    for ( i=0 ; i<number ; ++i ){
                    
                    if ( i>0 )
                      index = ++(*numOfDep);
                    
                    printf("For %d.university:\n",i+1);
                    printf("Department name: ");
                    scanf("%c",&ignore);
                    gets(universities[index-1].departs[number].depName);
                    /*scanf("%c",&ignore); /* For '\n' character */ 
                    printf("Department ID: ");
                    scanf("%d",&universities[index-1].departs[number].depID );
                    scanf("%c",&ignore); /* For '\n' character */  
                    printf("Score Type: ");
                    scanf("%c",&universities[index-1].departs[number].scrType);   
                    printf("Quota: ");
                    scanf("%d",&universities[index-1].departs[number].quota);
                    /* First status */
                    universities[index-1].departs[number].emptyQuota = universities[index-1].departs[number].quota;     
                    found=1;
                  
                  }
                  if( found == 1 )
                    break;
               
              if( found != 1 ){
                    printf("The university was not found!!!\n");
            
              }
              if ( selection != 2 )
                 printf("The informations were saved succesfully...\n");  
            
            break;
            default:
                printf("Invalid choice!!!\n");
 
    }                          
        (*numOfDep)=numberOfDeps;
        
                    
}


void createHtmlPlacement( stuInfo_t stuInfo[],score_t scores[],  int numOfStu )
{

    int i;
    FILE* outp;    
    outp = fopen("Placements.html","w");    
    
   fprintf(outp,"<center><p><u><h2>RESULTS OF THE AUTOMATION</h2></u></p></center>");   
   
    for( i=0 ; i<numOfStu ; ++i ){
        
        if ( stuInfo[i].isLocated == 1 ){
            fprintf(outp,"<center><table border ='1'><tr><td><b><u>%s</u></b></td><td><b><u>%s</u></b></td></tr></center>","Name","Sirname");
            fprintf(outp,"<center><tr><td><A HREF='Students.html#person%d'>%s</A></td><td>%s</td></tr></center></table>",i,stuInfo[i].name,stuInfo[i].sirname);
            fprintf(outp,"<table border ='1'><center><tr><td><u><b>%s</b></u></td><td><u><b>%s</b></u></td><td><u><b>%s</b></u></td><td><u><b>%-15s</b></u></td><td><u><b>%s</b></u></td></tr></center>","University","Department",
                                                            "ScoreType","Quentitative Score","Verbal Score");
            fprintf( outp, "<center><tr><td>%s</td><td>%s</td><td>%c</td><td>%.3f</td><td>%.3f</td></tr></center></table><br>",stuInfo[i].uniName, stuInfo[i].depName, stuInfo[i].scrType, scores[i].Qscore, scores[i].Vscore );
            
        
        }
        
    }

    printf("The Html files were prepared succesfully...\n");
    fclose(outp);


}

void createHtmlStudents( stuInfo_t stuInfo[], stuAddress_t stuAddress[], int numOfStu )
{

    int i, n=0;
    FILE* outp ;
    outp = fopen("Students.html","w");


    fprintf(outp,"<center><table border ='1'><tr><td><b><u>%s</u></b></td><td><b><u>%s</u></b></td><td><b><u>%s</u></b></td><td><b><u>%s</u></b></td><td><b><u>%s</u></b></td><td><b><u>%s</u></b></td></tr></center>",
                                                "Name","Sirname","ID number","Phone","Mail","Address");

    for ( i=0 ; i<numOfStu ; ++i ){
        
        fprintf( outp,"<center><tr><td><A NAME = '#person%d'>%s</A></td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr></center>",
                             i,stuAddress[i].IDnum,stuInfo[i].name, stuInfo[i].sirname, 
                               stuAddress[i].phone, stuAddress[i].mail, stuAddress[i].address );     
        
    }
    

}


void fillBinaryFile1( stuInfo_t stuInfo[], char* stuInfoFileBin, int numOfStu  )
{

    FILE* outp;
        
    outp = fopen( stuInfoFileBin,"wb");
    
    fwrite(&numOfStu,sizeof(int),1,outp);
    
    fwrite(stuInfo,sizeof(stuInfo_t),numOfStu,outp );    
    
    fclose(outp);

}


void fillBinaryFile2( stuAddress_t stuAddress[], char* stuAddressFileBin, int numOfStu  )
{

    FILE* outp;
    
    outp = fopen( stuAddressFileBin,"wb");
    
    fwrite( stuAddress,sizeof(stuAddress_t),numOfStu,outp );    
         
    fclose(outp);        

}



void fillBinaryFile3( score_t scores[], char* scoresFileBin, int numOfStu  )
{

    FILE* outp;
    
    outp = fopen( scoresFileBin,"wb");
    
    fwrite( scores,sizeof(score_t),numOfStu,outp );    
        
    fclose(outp);
    

}


void fillBinaryFile4( uni_t  universities[], char* universitiesFileBin, int numOfDep  )
{

    FILE* outp;
    
    outp = fopen( universitiesFileBin,"wb");
    
    fwrite( &numOfDep,sizeof(int),1,outp );
    
    fwrite( universities,sizeof(uni_t),numOfDep,outp );    
    
    fclose(outp);

}
