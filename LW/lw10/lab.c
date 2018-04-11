#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct{

    int ID;
    int lenght;
    char *text;    

}text_t;


typedef struct node_s{
    
    int ID;
    text_t text;
    struct node_s* restp;
    
}node_t;


typedef struct{
    
    int size;
    node_t *headp;

}ordered_t;


text_t  getText( int ID, char  ch );

int print( const  text_t* text );

node_t* createOrdered( unsigned int a, unsigned int b, unsigned number ,char ch  );

int printfLL( node_t* list );

node_t* mergeTheList( node_t* list1, node_t *list2 );

int main()
{
    
        
    char ch;
    int ID;  
    text_t text1;
    text_t  text2;
    node_t *list1, *list1cp;
    node_t *list2, *list2cp;
    node_t *mergeList;
    int randomV, randomV2;
    int num;
    
    srand(time(NULL));
     
    
    text1=getText( 0, 'a' );

    text2=getText( 1,  'b' );

    print( &text1 );
    print( &text2 );
    

    free(text1.text);
    free(text2.text);

    
    randomV=rand()%10;
    list1 = createOrdered( randomV, 0, 8, 'a'  );
    
    randomV2=rand()%10;
    list2 = createOrdered( randomV2, 0, 5, 'b'  );
    
    list1cp = list1;
    printfLL( list1cp );
    
    list2cp = list2;
    printfLL( list2cp );

    mergeList = mergeTheList( list1, list2 );
    printfLL( mergeList );
    
    return 0;
}


text_t  getText( int ID, char  ch ){

    text_t text;
    int i;

    text.lenght = rand()%26 + 5;
    
    text.text = (char*)malloc( (text.lenght+1)*sizeof(char) );
    
    /*text.text = ( char* )calloc(text.lenght+1, sizeof(char)  );*/

    text.ID = ID;
    
    for( i=0 ; i<text.lenght ; ++i ){
        
        text.text[i] = ch;
            
    }

    text.text[i]='\0';
    
    
    
    return  text;


}



int print( const text_t* text ){

    printf("%d   %d  %s\n",text->ID , text->lenght ,text->text );

    return text->lenght;

}


node_t* createOrdered( unsigned int a, unsigned int b, unsigned number ,char ch  )
{
    
    node_t *headp;      
    node_t  *currp;
    node_t *ansp;
    
    int i;
    
    
    headp = (node_t*)malloc( sizeof(node_t) );
    
    headp->ID = b;
    
    headp->restp = ansp;
    
    for( i=0 ; i<number ; ++i ){
        
        currp = (node_t*)malloc( sizeof(node_t) );      
        currp->ID = a*(i+1)+b;
        ansp->restp = currp;
        ansp = currp; 
        
    }  
    
    ansp = (node_t*)malloc( sizeof(node_t) );
    ansp->restp = NULL;
    
    
    return  headp;
    
}


int printfLL( node_t* list )
{

    int i;
    int number=0;
    node_t *currp;
    
    currp = list->restp;
    
    while( currp != NULL  ){
        
        printf("%d  ", currp->ID );
        number++;
        currp = currp->restp;
    
    }
           
    printf("\n");        
    
    
}


node_t* mergeTheList( node_t* list1, node_t *list2 )
{
    
    node_t *finalp;
    int i;
    
    finalp= list1->restp;
    
    for( i=0; i<8 ;++i ){
        finalp = finalp->restp;   
    
    }
   
    finalp->restp /* it was NULL */ = list2->restp; 

    return list1;

}







