#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define  DEBUG

typedef struct list_s{
    
    struct list_s *restp;
    char word[15];
    
}list_node_t;


typedef struct{
    
    int ind_of_word1;
    int ind_of_word2;

}index_of_smilar_words_t;


typedef struct{

    list_node_t* line1;
    list_node_t* line2;

}poem_t;


poem_t createPoem(const char *fileName, int s1, int s2);

int printPoem(poem_t* poem);

int deletePoem(poem_t* poem);

char* readSentence(const char *fileName, int s);/**/

list_node_t* createLL(char *sentence);/**/

int printLine(FILE *out, list_node_t *head_p);

list_node_t* randomizeSentence(list_node_t *head_p);/**/

int checkSimilarity(char *word1, char *word2) ;/**/

index_of_smilar_words_t getSmilarIndexes(list_node_t* head_p1 , list_node_t* head_p2); /**/

list_node_t* putToEnd(list_node_t *head_p, int index);/**/

int freeLL(list_node_t *head_p);



int main( int argc, char* argv[] )
{


    char *fileName;
    int s1, s2;
    poem_t poem;
    srand(time(NULL));
    int numOfCh, numOfWord;
    
    s1 = (int)((*argv[2]) - '0');
    s2 = (int)((*argv[3]) - '0');

    
    if( argv[4] != NULL )
       stdout = fopen( argv[4],"w" );
    
    poem = createPoem( argv[1], s1, s2 );

    numOfCh = printPoem( &poem );
    
    //number of characters
    #if defined (DEBUG)
      printf("\n*****   number of characters in the poem : %d    *****\n",numOfCh);
    #endif
    
    numOfWord = deletePoem( &poem );

    //number of characters
    #if defined (DEBUG)
      printf("*****   number of words in the poem : %d       *****\n",numOfWord);
    #endif
    
    
    return 0;

}

poem_t createPoem(const char *fileName, int s1, int s2)
{
   
    char* sentence;
    int numOfWord;
    list_node_t* head_p1;
    list_node_t* head_p2;
    index_of_smilar_words_t inOfSim;
    poem_t poem;
    
    
    sentence = readSentence( fileName, s1 );
    head_p1 = createLL( sentence );
    
    sentence = readSentence( fileName, s2 );
    head_p2 = createLL( sentence );
    
    randomizeSentence( head_p1 );
    randomizeSentence( head_p2 );
    
    inOfSim = getSmilarIndexes( head_p1 , head_p2);  
    
    head_p1 = putToEnd( head_p1, inOfSim.ind_of_word1 );
    poem.line1 = head_p1;
    
    head_p2 = putToEnd( head_p2, inOfSim.ind_of_word2 );
    poem.line2 = head_p2;
    
   
    return poem;   
   
}


int printPoem( poem_t* poem)
{

    int count=0, n;
    list_node_t* head_p1;
    list_node_t* head_p2;
    
    printLine(stdout,poem->line1);
    printLine(stdout,poem->line2);
    
    head_p1 = poem->line1;
    head_p2 = poem->line2;
    
    /* number of characters */
    while( head_p1 != NULL ){
 
        n = strlen(head_p1->word);
        head_p1 = head_p1->restp;
        count += n;
        
    }

    while( head_p2 != NULL ){
 
        n = strlen(head_p2->word);
        head_p2 = head_p2->restp;
        count += n;
        
    }

    return count;

}


int deletePoem(poem_t* poem)
{
    
    int count=0, numOfDel;
    list_node_t* head_p1;
    list_node_t* head_p2;
    
    
    head_p1 = poem->line1;
    head_p2 = poem->line2;

    /* Number of words */
    while( head_p1 != NULL ){
 
        head_p1 = head_p1->restp;
        ++count;       
    }


    while( head_p2 != NULL ){

        head_p2 = head_p2->restp;
        ++count;        
    }

    numOfDel = freeLL(poem->line1);
    #if defined (DEBUG)
      printf("*****   number of words was deleted line1 : %d       *****\n",numOfDel);
    #endif
    
    numOfDel = freeLL(poem->line2);
    #if defined (DEBUG)
      printf("*****   number of words was deleted line2 : %d       *****\n",numOfDel);
    #endif



    return count;
}


char* readSentence(const char *fileName, int s)
{

    FILE* inp;
    inp = fopen(fileName,"r");
    int i;
    char ch;
    char* line;
    
    
    line = (char*)calloc( 80,sizeof(char));
    /* reads row as empty */
    
    for( i=0 ; i<s ; ++i ){
      
      fscanf(inp,"%c",&ch);
      while( ch != '\n' )
        fscanf(inp,"%c",&ch);
    
    }
    
    fgets( line, 80, inp );
    
    return line;

}


list_node_t* createLL(char *sentence)
{
    
    list_node_t* headp, *restp;
    int number=0;
    
    if( sentence[0] == '\n' || sentence[0] == '\0' )
        return NULL;
    
    headp = (list_node_t*)malloc( sizeof(list_node_t) );
    
    
    while( sentence[number] != ' ' && sentence[number] != '\n' 
           && sentence[number] != '\0'                     ){
        
        headp->word[number] = sentence[number];
        ++number;
        
    }
    
    headp->restp = createLL( &sentence[number+1] );    
    
    return headp;
    
}



int printLine(FILE *out, list_node_t *head_p) 
{

    int number;
    
    
    if( head_p == NULL ){
        fprintf(out,"\n");
        return 0;
    }
    else {
       
        printf("%s ",head_p->word );
        head_p = head_p->restp;
        number += printLine( out, head_p );
        
    }    

    return number;

}


list_node_t* randomizeSentence(list_node_t *head_p) 
{

    int number, counter; /* for random */
    list_node_t* temp, *temp2, *temp3;
    
    number = rand()%80;
    
    if( number < 10 )   
        return head_p;
    else { 
        
        for( counter=0,temp=head_p ; temp->restp != NULL ; ++counter, temp = temp->restp ){}
            
            number = rand()%(counter-1);
            
            for( counter = 0,temp=head_p; counter<=number ; ++counter ,temp = temp->restp  ){}
        
            temp2 = temp->restp;
            temp3 = head_p->restp;
            temp->restp = temp->restp->restp;
            head_p->restp = temp2;
            temp2->restp = temp3;
            
    }
    
    return randomizeSentence(  head_p );

}


int checkSimilarity(char *word1, char *word2)
{

    int leng1, leng2;
    int times=1;
    char tempStr1[20], tempStr2[20];
    leng1 = strlen(word1);
    leng2 = strlen(word2);
    
    
    if( word1[leng1-1] == word2[leng2-1] ){
        
        strcpy(tempStr1, word1 );
        tempStr1[leng1-1] = '\0';
        strcpy(tempStr2, word2 );
        tempStr2[leng2-1] = '\0';
        
        return 1 + checkSimilarity( tempStr1 , tempStr2 );
    
    }
    else
        return 0;
    
    

}


index_of_smilar_words_t getSmilarIndexes(list_node_t* head_p1 , list_node_t* head_p2)
{

    int i ,j, max=0;
    list_node_t* tempNode;
    index_of_smilar_words_t indexes;    
    
    
    for( i=0 ;  head_p1 != NULL ; head_p1=head_p1->restp, ++i ){
        
        for( j=0,tempNode=head_p2 ; tempNode != NULL ; tempNode = tempNode->restp, ++j  ){
            
            if( checkSimilarity( head_p1->word,tempNode->word ) > max ){
                        
                max = checkSimilarity( head_p1->word,tempNode->word );
                indexes.ind_of_word1 = i;
                indexes.ind_of_word2 = j;         
                
            
            }
    
        }
    
    }
    
    return indexes;
    
}


list_node_t* putToEnd(list_node_t *head_p, int index)
{
    int i;   
    list_node_t* temp;      
    list_node_t* temp2;
    temp = head_p;
    
    for( i=0 ; i<index-1 ; head_p = head_p->restp,++i ){}
        
        temp2 = head_p->restp;
        head_p->restp = temp2->restp;
    
    while( head_p->restp != NULL ){
        head_p = head_p->restp;
        
    }
        
        head_p->restp = temp2;
        temp2->restp = NULL;
  
    return temp;

}

int freeLL(list_node_t *head_p)
{

    list_node_t *temp = head_p;
    
    
    if( head_p->restp == NULL ){/* Do nothing and return 0 */
        return 1;
        free(temp);
    }
    else {
        head_p = head_p->restp;
        free(temp);
        return 1 + freeLL( head_p );
        
   }
   
   
   
}


