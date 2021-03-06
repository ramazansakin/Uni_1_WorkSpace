#include<stdio.h>

#define _DEBUG

typedef struct{
    int pID;
    char name[20];
    double uPer;
    double uSale;
    int exist;
    
}pro_t;

typedef struct{
    int cosID;
    int pID;
    int amount;
    char date[20];
    
}sell_t;

typedef struct{
    int cosID;
    char name[20];
    char surname[20];
    
}cos_t;


int reader1( FILE*inp, pro_t prod[10] );

int reader2( FILE*inp, sell_t sell[10] );

int reader3( FILE*inp, cos_t custom[10] );

void printer1( pro_t prod[10], int size );

void printer2( sell_t sell[10], int size );

void printer3( cos_t custom[10], int size );

int calcProf( pro_t prod[10] ,sell_t sell[10] , int size1, int size2 );

int Ind( int pID, pro_t prod[10], int size );

int introduceTheCustomer( cos_t custom[10], pro_t prod[10], sell_t sell[10], int size1, int size2 ,int size3 );

int main(void)
{

    pro_t prod[10];
    sell_t sell[10];
    cos_t custom[10];
    pro_t temp;
    int size1, size2, size3;
    int totalProf;
    
    FILE* inp1,
         *inp2,
         *inp3,
         *outp;
          
    inp1 = fopen("products.txt","r");
    inp2 = fopen("sellings.txt","r");
    inp3 = fopen("customers.txt","r");

    size1 = reader1(inp1, prod);
    printf("The size is %d\n",size1 );

    printer1( prod, size1 );

    size2 = reader2( inp2, sell );

    printer2( sell, size2 );

    size3 = reader3( inp3, custom );

    printer3( custom , size3 );
    
    totalProf = calcProf( prod, sell, size1, size2 );

    printf("\nThe total profit is %d\n",totalProf);

     introduceTheCustomer( custom,prod,sell,size1,size2 ,size3 );  
    

   
        if ( prod[0].cosID > prod[1].cosID ){
            temp =  prod[1];
            prod[1] = prod[0];
            prod[0] = temp;
         
         }
         
    #if defined(_DEBUG)
         printf("The new cosID is %d\n",prod[1].exist );
    #endif


    return 0;
}

int reader1( FILE*inp, pro_t prod[10] )
{
    
    int i, size=0, status;
    
    for ( i=0 ; status != EOF; ++i ){
        
        status = fscanf(inp, "%d",&prod[i].pID );
        if ( status == EOF )
            break;
        else
            ++size;
            
        fscanf(inp, "%s", prod[i].name );   
        fscanf(inp, "%lf",&prod[i].uPer );
        fscanf(inp, "%lf",&prod[i].uSale );
        fscanf(inp, "%d",&prod[i].exist );
    }


    return size;
}


void printer1( pro_t prod[10], int size )
{

    int i;
    
    for ( i=0 ; i<size ; ++i ){
        
        printf("%d %s %.2f %.2f %d\n",prod[i].pID, prod[i].name, prod[i].uPer, prod[i].uSale, prod[i].exist );        
           
    }

}

int reader2( FILE*inp, sell_t sell[10] )
{
    
    int i, size=0, status;
    
    for ( i=0 ; status != EOF; ++i ){
        
        status = fscanf(inp, "%d", &sell[i].cosID );
        if ( status == EOF )
            break;
        else
            ++size;
               
        fscanf(inp, "%d", &sell[i].pID );
        fscanf(inp, "%d", &sell[i].amount );
        fscanf(inp, "%s", sell[i].date );
    }


    return size;

}

void printer2( sell_t sell[10], int size )
{
    
    int i;
    
    printf("\n\nThe Sellings \n\n");
    for ( i=0 ; i<size ; ++i ){
        
        printf("%d %d %d %s\n", sell[i].cosID, sell[i].pID, sell[i].amount, sell[i].date );        
           
    }

    
}



int reader3( FILE*inp, cos_t custom[10] )
{

    int i, size=0, status;
    
    for ( i=0 ; status != EOF; ++i ){
        
        status = fscanf(inp, "%d", &custom[i].cosID );
        if ( status == EOF )
            break;
        else
            ++size;
               
        fscanf(inp, "%s", custom[i].name );
        fscanf(inp, "%s", custom[i].surname );
        
    }


    return size;


}

void printer3( cos_t custom[10], int size )
{

    int i;
    
    printf("\n\nCustomers \n\n");
    for ( i=0 ; i<size ; ++i ){
        
        printf("%d %s %s\n", custom[i].cosID, custom[i].name, custom[i].surname );        
           
    }


}


int calcProf( pro_t prod[10] ,sell_t sell[10] , int size1, int size2 )
{
    int i,
        totalProf=0;

    for ( i=0 ; i< size2 ; ++i ){
        
        totalProf += sell[i].amount*( prod[Ind(sell[i].pID, prod, size1 )].uSale - prod[Ind(sell[i].pID, prod, size1 )].uPer );
        
    }

    return totalProf;
}


int Ind( int pID, pro_t prod[10], int size ){
    int i;
    
    for ( i=0 ; i<size ; ++i ){
        
        if ( pID == prod[i].pID ){       
            return (i);
        }
    
    }


}


int introduceTheCustomer( cos_t custom[10], pro_t prod[10], sell_t sell[10] , int size1, int size2 ,int size3 )
{

    char Cname[20], Csurname[20];    
    int i, j;

    printf("Please enter a name and surname for searching>");
    scanf("%s%s",Cname, Csurname);
    
    for ( i=0; i<size3 ; ++i ){
        
        if (strcmp( Cname, custom[i].name ) == 0 && strcmp(Csurname, custom[i].surname) == 0 )
            break;
            printf("\n%d*-*-*-*\n",i);
    }      
    
    for ( j=0 ; j<size2 ; ++j ){    
        if ( custom[i].cosID == sell[j].cosID )
            printf("%s  ",sell[j].date );
            
    }
    
}



