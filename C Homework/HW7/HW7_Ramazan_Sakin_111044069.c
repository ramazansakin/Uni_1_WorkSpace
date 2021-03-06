/*##############################################################################
/*                      111044069--created by Ramazan SAKİN                    #
/******************************************************************************#
/*  This program gets addresses from a file.And it makes some operations       #
/*  such that findind address of a given person, changing Email                # 
/*  INPUT: input.txt                                                           #
/*  OUTPUT:Addresses.txt                                                       # 
/*                                                                             #         
/*                                                                             #
/*############################################################################*/

#include<stdio.h>
#include<string.h>

#define FILE_NAME "input.txt"
#define  RowCap  50
#define  ColCap  100


int readRecords( FILE* inp, char records[][100], int* numOfRecords, int rowCap, int colCap);

int writeStrArr(FILE* outFile, const char* strArr, int numOfRecords );

int writePtrArr(FILE* outFile, char* ptrArr[], int size);


char* getName(char records[][100], const char name[], const char sirName[], int numOfRecords );

int changeEmailAddress(char records[][100], char* addres, const char newEmail[], int rowC );

int getNamesInCity(char strArr[][100], const char city[], char names[][15], int rowC );

void getPtrArray(char* ptrArr[], char strArr[][100], int rowC);

int getAddressInTown(char strArr[][100], const char town[], char* addresses[], int rowC );

int isGreaterByName(const char record1[], const char record2[]);

int isGreaterByEmail(const char record1[], const char record2[]);

int isGreaterByCity(const char record1[], const char record2[]);

void sortRecords(char* records[], int size,int isGreater(const char rec1[], const char rec2[]));

void sortByEmail(char* records[]);


int main(void)
{
    /* START_OF_MAIN */
    int numOfRecords, size , i;
    char records[RowCap][ColCap], names[10][15], city[10];
    char *strArr, *ptrArr[RowCap];
    char name[20], sirName[20], newEmail[30];
    char* address;
    int selection;
    FILE* inp,
        * outp;    
    /* END_OF_VARIABLES */
    
    
    readRecords( inp, records, &numOfRecords, RowCap, ColCap );
    
    writeStrArr( outp, records, numOfRecords );
    
    for ( i=0 ; i < numOfRecords ; ++i ){
            ptrArr[i] = records[i];     /* Copies ONLY adresses! */
    }
    
    size = numOfRecords;        
    writePtrArr( outp, ptrArr , size);
    
    printf("Please enter a selection:\n");
    printf("enter 1 for searching address and changing e-mail\n");
    printf("enter 2 for finding people who are in the given town\n");
    scanf("%d",&selection);    
       
    if ( selection == 1 ){
        address = getName( records, name, sirName , numOfRecords);
        printf("Owner of the address:\n");
        printf("%s\n",address);

        changeEmailAddress( records, address, newEmail, numOfRecords );
       } 
       else if ( selection == 2 ){
        getNamesInCity( records, city, names, numOfRecords );
       
       
       } 
    
    
    /* END_OF_MAIN */

    return 0;
}

int readRecords( FILE* inp , char records[][100], int* numOfRecords, int rowCap, int colCap)
{
    int i, status;
    char ch;
    int num=0, index, j ;
    
    inp = fopen( FILE_NAME, "r" ); 
    
    
    /* Gets address from the file */
    for ( i=0; i < ColCap ; i++ ){    
        for ( j=0 ; j < ColCap ; j++ ){
            status = fscanf(inp, "%c", &ch);             
            if ( status == 0 || ch == '\n' || status == EOF)         
                    break;

            records[i][j] = ch;
             
        } 
        records[i][j] = '\0';  
        
        if ( status == EOF )
            break;
        
        if ( status == 0 ){
            printf("The file is not found!\n");      
            return -1;
        }
                
        num++;
    }
    
    if ( num > RowCap ){
        printf("The row capacity of the array is not enough!\n");
        return -2;
    }

    *numOfRecords = num;

    return 0;
}

int writeStrArr(FILE* outFile, const char* strArr, int numOfRecords )
{
    int i;
    const char* row = strArr; /*starting address of the row to be printed*/
    outFile = fopen("addresses.txt","w");
         
        for(i=0; i < numOfRecords ; ++i){
            /*write a row to the stream*/
            fprintf(outFile,"%s\n", row);
            /*update the address of the row*/
            row += ColCap;
            
        }

    return 0;
}

int writePtrArr(FILE* outFile, char* ptrArr[], int size)
{
    
    int i;
        
        printf("\n***************The adresses***************\n");
        for ( i=0 ; i < size ; ++i ){
            fprintf( stdout,"%s\n", ptrArr[i] );
        
        }

    return 0;
}


char* getName(char records[][100], const char name[], const char sirName[], int numOfRecords )
{
    
    /* Bu fonksiyonda kullanıcın girmis oldugu ismi addres lerde token larina ayırarak
     * aynı name ve sirname e sahip kisinin adres bilgilerini veriyor...
     *
     */
    int i=0, j;
    char* token;
    char reserver[] = " ";
    char name2[10];
    int numName;
    char recordsCopy[20][100];
       
    
    for ( i=0 ; i<numOfRecords ; i++ ){
    strcpy(recordsCopy[i], records[i]);
    
    }
    
    printf("If there is second name(optional) , enter 2, if it is not ,enter 1 :\n");
    
    scanf("%d", &numName );   
    printf("Please enter the name and sirname to search: \n");
    
    if ( numName == 1 ){
        fscanf(stdin, "%s", name);     
        fscanf(stdin,"%s",sirName);
    }
    
    if ( numName == 2 ){
        fscanf(stdin, "%s", name );     
        fscanf(stdin, "%s", name2 );
        fscanf(stdin,"%s",sirName);
    }
    
    if ( numName == 1 ){
        
    for ( i=0 ; i < numOfRecords ; ++i ){
        token = strtok( recordsCopy[i], reserver );
            printf("%s\n",token);
            if ( strcmp( token, name ) == 0 ){
                   token = strtok( NULL, reserver );
                        strcat(sirName,";");
                        if ( strcmp( token, sirName ) == 0 ){
                            return  &records[i];
                            
                        }             
            }
        }
      
      }
    

    if ( numName == 2 ){
        
        for ( i=0 ; i < numOfRecords ; ++i ){
            token = strtok( recordsCopy[i], reserver );
                if ( strcmp( token, name ) == 0 ){
                       token = strtok( NULL, reserver );
                          if ( strcmp( token, name2 ) == 0 ){
                              token = strtok( NULL, reserver );  
                                strcat(sirName, ";" );
                                
                                if( strcmp( token, sirName ) == 0 ){
                                    
                                    return  &records[i];
                                }                
                    }
                
                }
    
            }
        
    }


    printf("The name and sirname is not found!\n");
    return 0;  /* The person is not found!!! */
}


int changeEmailAddress(char records[][100], char* addres, const char newEmail[], int rowC )
{

    /* Bu foksıyonda kullanıcıdan aldıgımız kisinin adresini stringlere ayırarak '@' 
     * karakterinin gectigi tokenin yerine kullanıcının girmis oldugu mail adresi ile
     * degistiriyor...
     */    
    char* token;
    char reserver[] = " ";
    int num=0, i;
    int leng1, leng2;
    char A[20];
    char AddressC[100];
    char temp[20];
    
    strcpy(AddressC, addres);
    
    printf("Please enter new Email for the person:");    
    scanf("%s",newEmail);
    
    token = strtok( addres, reserver );
    
    while ( token != NULL ){
    
        for ( i=0 ; i < strlen(token)+1 ; i++  ){
            num++;
            strcpy(A,token);
            if ( A[i] != '@' ){
                
            }     
            else if ( A[i] == '@' ){    
                
                while( A[i+1] != '\0' ){
                    num++;
                    i++;
                }
             
                leng1 = strlen( AddressC );
                strncpy( temp, &AddressC[num],leng1-num );        
                temp[leng1-num-1] = '\0';
                leng2 = strlen( token );
                AddressC[num-leng2]= '\0';
                strcat(AddressC, newEmail);
                if ( num != leng1 )
                    strcat( AddressC, temp );/*if The email address is not at the end*/
            }
            if ( A[i] == '\0' )
                break;
        }
        token = strtok( NULL, reserver );         
    }
    
    printf("The email was changed.\n");    
    printf("%s\n",AddressC);
    return 0;

}


int getNamesInCity(char strArr[][100], const char city[], char names[][15], int rowC )
{

    int numOfNames=0, i, j=0, num=0;
    char* token; 
    char reserver[] = " ", A[20],  ch;
     
    /* gets the names and sirnames */ 
    for ( i=0 ; i < rowC ; ++i ){
        ch = strArr[i][j];
        while ( ch != ';' ){
      
            names[i][j] = ch;
            ch = strArr[i][j];
            j++;
        }
    j=0;
    }
 
    /* Gets the city for searching */
    printf("Please enter a city for searching people:");    
    fscanf(stdin,"%s", city);
    /* Her bir rowdaki adres bilgilerini stringlere ayırarak
     * '/' karakterini gordugu yer ile karsılastıtırır ve 
     * eger esitse karsılastırdıgı adresteki name ve sirname i yazdırır 
     * " Sonsuz donguye giriyor nedenini bulamadm hocam" ??
     */
    
    for ( j=0 ; j < rowC ; ++j ){

    token = strtok( strArr[num], reserver );
    num++;
    while ( token != NULL ){
    
        for ( i=0 ; i < strlen(token)+1 ; i++  ){
            strcpy(A,token);
            if ( A[i] != '/' ){
            /* do nothing */ 
            }     
            else if ( A[i] == '/' ){    
                
                if (strcmp( city,A ) == 0 )
                    printf("%s\n",names[j]);    
                    
                    numOfNames++;
                }
             
            }
            if ( A[i] == '\0' )
                break;
        }
        token = strtok( NULL, reserver );         
    }   


    return numOfNames;
}


