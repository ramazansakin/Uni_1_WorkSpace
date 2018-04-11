#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SETSIZ 65 /* 52 uppercase and lowercase letters, 10 digits,
{, }, and '\0'*/
#define TRUE 1
#define FALSE 0

int is_empty(const char *set);
int is_element(char ele, const char *set);
int is_set(const char *set);
int is_subset(const char *sub, const char *set);
char *set_union(char *result, const char *set1, const char *set2);
void print_with_commas(const char *str);
void print_set(const char *set);
char *get_set(char *set);

char* strChr( char* str, char target);
char* strRChr( char* str, char target );

int calcCombinationRec( int n, int k );
int calcCombinationIter( int n, int k );

int readSudoku(const char fileName[], int sudoku[][4]);
int solveRec(int sudoku[][4],int* value, int posX, int posY);
int solve(int sudoku[][4]);
void printSudoku(FILE* stream, int sudoku[][4]);
void clear( int sudoku[][4] );

int main(void)
{
    
    char ele, set_one[SETSIZ], set_two[SETSIZ], set_three[SETSIZ];
    char* strArr;
    char ch, ignore;
    int status;
    char* found;
    int n, k;
    int result;
    int sudoku[4][4];
    char fileName[100] = "sudokuIn.txt";
    FILE*outFile;
    
    int selection;
    
    
    printf("Please enter a number for selection:\n");
    printf("Enter 1 for set test,\n");
    printf("Enter 2 for finding first and last address the character that you want,\n");
    printf("Enter 3 for calculating Combination,\n");
    printf("Enter 4 for solving sudoku: ");
    
    scanf("%d",&selection);
    
    if ( selection == 1 ){
        printf("A set is entered as a string of up to %d letters\n",
SETSIZ - 3);
        printf("and digits enclosed in {} ");
        printf("(no duplicate characters)\n");
        printf("For example, {a, b, c} is entered as {abc}\n");
        printf("Enter a set to test validation function> ");

        get_set(set_one);
        putchar('\n');
        print_set(set_one);
        if (is_set(set_one))
            printf(" is a valid set\n");
        else
            printf(" is invalid\n");
        printf("Enter a single character, a space, and a set> ");
        
        while(isspace(ele = getchar())); /* gets first character after
    whitespace*/
        get_set(set_one);
        printf("\n%c ", ele);
        if (is_element(ele, set_one))
            printf("is an element of ");
        else
            printf("is not an element of ");
        
        print_set(set_one);

        printf("\nEnter two sets to test set_union> ");
        
        get_set(set_one);
        get_set(set_two);
        printf("\nThe union of ");
        print_set(set_one);
        printf(" and ");
        print_set(set_two);
        printf(" is ");
        print_set(set_union(set_three, set_one, set_two));
        putchar('\n');
        
    }
    else if ( selection == 2 ){
        strArr = "Ramazan Sakin Computer Engineering Gebze Institue of Technology";
    
        printf("******************** The string ********************\n");
        printf("%s\n",strArr);
        
        
        printf("Please enter a character for searching:");
        fscanf(stdin,"%c%c",&ignore,&ch);
        
        found = strChr( strArr, ch );
               
        if ( found == NULL )  
            printf("The character was not found!!!\n");
        else
            printf("%s\n", found);    
    
        found = strRChr( strArr, ch );
           
        if ( found == NULL )  
            printf("The character was not found!!!\n");
        else
            printf("%s\n", found);
            
    }
    else if ( selection == 3 ){
        printf("Please enter two number to calculate their combination as C( n,k ) : ");
        fscanf(stdin,"%d%d",&n, &k);
        
        result = calcCombinationRec( n, k );
        printf("\nThe result is %d as recursively\n",result );
        
        result = calcCombinationIter( n, k );
        printf("\nThe result is %d as iteratively\n",result );
       
    }
    else if ( selection == 4 ){
        
        clear(sudoku);
        readSudoku(fileName, sudoku );

        solve( sudoku );
        printSudoku(outFile ,sudoku);
    }


    return 0;
}

/*
* Determines if set is empty. If so, returns 1; if not, returns 0.
*/
int
is_empty(const char *set)
{
return (set[0] == '\0');
}
/*
* Determines if ele is an element of set.
*/
int
is_element(char
ele,
/* input - element to look for in set */
const char *set)
/* input - set in which to look for ele */
{
    int ans, i;

    ans = FALSE;

    if (is_empty(set))
        ans = FALSE;
    else {
        for ( i=0; i<strlen(set)-1; ++i )
            if ( set[i] == ele )
                ans = TRUE;     
    }

    return (ans);
}

/*
* Determines if string value of set represents a valid set (no duplicate
 * elements)
 */

int
is_set (const char *set)
{
    int ans, i, j;

    /*if (is_empty(set))
        ans = TRUE;
    else if (is_element(set[0], &set[1]))
        ans = FALSE;
    else
        ans = is_set(&set[1]);*/
        
    
    
    ans = TRUE;
    
    if ( is_empty(set) )
        ans = TRUE;
    else {
        for ( i=0; i<strlen(set); ++i ){
            for ( j=i+1; j < strlen(set); ++j ){                
                if ( set[i] == set[j] )
                    return FALSE;
                   
            }
        }     
    }    
 
    return (ans);
}

/*
 * Determines if value of sub is a subset of value of set.
 */

int
is_subset(const char *sub, const char *set)
{
    int ans ,i, j, status=0;
    
    ans = TRUE;
    
    if (is_empty(sub))
        ans = TRUE;
    else{
        for ( i=0 ; i<strlen(set); ++i ){
            for ( j=0 ; j<strlen(sub) ; ++j )
                
                if ( sub[i] == set[j] )           
                    status = 1;
                   
        }
        if ( status != 1 )
            return FALSE;
        status = 0;
    } 
        

    return (ans);
}

/*
 * Finds the union of set1 and set2.
 */

/* Pre: size of result array is at least SETSIZ;
 *set1 and set2 are valid sets of characters and digits
 */

char *set_union(char
*result,
/* output - space in which to store string result*/
const char *set1, /* input - sets whose */
const char *set2) /* union is being formed */
{

    char temp[SETSIZ];
    int i, j, num=0, status=0;
    
    if ( is_empty(set1) ){
        strcpy(result, set2);
    }
    else {
        for ( i=0; i<strlen(set1) ; ++i ){
            for ( j=0; j<strlen(set2) ; ++j ){
                if ( set1[i] == set2[j] ){
                    status = 1;
                }   
    
            }
            if ( status != 1 ){
                result[num] = set1[i];
                ++num;
            }
            status = 0;
        }
    }
    result[num]='\0';
    strcat(result, set2);
    /* local variable to hold result of call
    to set_union embedded in sprintf call */
    /*if (is_empty(set1))
        strcpy(result, set2);
    else if (is_element(set1[0], set2))
        set_union(result, &set1[1], set2);
    else
        sprintf(result, "%c%s", set1[0],

    set_union(temp, &set1[1], set2));*/
    
    return (result);
}
/*
* Displays a string so that each pair of characters is separated by a
* comma and a space.
*/

void
print_with_commas(const char *str)
{
    int i;
    
    if (strlen(str) == 1) {
        putchar(str[0]);
    } else {
        for ( i=0; i<strlen(str); ++i ) 
            if ( i == strlen(str)-1 )
                printf("%c", str[i]);
            else
                printf("%c, ", str[i]);
    }                   

}

/*
 * Displays a string in standard set notation.
 * e.g. print_set("abc") outputs {a, b, c}
 */

void
print_set(const char *set)
{
    
    putchar('{');
    if (!is_empty(set))
        print_with_commas(set);
    putchar('}');

}

/*
 * Gets a set input as a string with brackets (e.g., {abc})
 * and strips off the brackets.
 */

char *
get_set(char *set)
/* output - set string without brackets {} */
{

    char inset[SETSIZ];
    
    scanf("%s", inset);
    strncpy(set, &inset[1], strlen(inset) - 2);
    set[strlen(inset) - 2] = '\0';
    
    return (set);
}


char* strChr( char *str, char target)
{
    /* Finds the first target character and return its address */
    if ( str == NULL )
        return NULL;
    else if ( *str == '\0' )
        return NULL;
    if ( *str == target ) {
        return str;
    }
    else {
        strChr( ++str, target );
    } 
        
}

/* Finds the latest target character and return its address */         
char* strRChr( char* str, char target )
{
    char* address;
    
    if ( str == NULL  )
        return NULL;
        
    if ( *str == target ){
            
        address = str;  /* temps the addresses */
        /* Hocam burda son larakteri tutması lazım ama farklı bir karakter basyo?? */
    }
        
    if ( *str != '\0' )
        strRChr( ++str, target );    
        
    return address;  
}


int calcCombinationRec( int n, int k )
{

    if ( k == 0 || k == n )   
        return 1;        
    
    return calcCombinationRec( n-1, k-1 ) + calcCombinationRec(n-1, k );
    
}

int calcCombinationIter( int n, int k )
{
    
    int i, limit = k;
    int numerator = 1, denominator = 1;
    if ( n == 0 )
            return 0;
    else if ( k == 0 )    
            return n;
    else{
        for ( i=0 ; i < limit; ++i  ){   
            
            numerator *= n;
            denominator *= k;
            n--;
            k--;
        
        }
    }   
    return numerator/denominator;

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
        
 
}
