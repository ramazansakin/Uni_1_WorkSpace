#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PR_111044024.h"


void UsersRead(char dosya[],users_t users[], int numberOfUsers, egitimci_t egis[] , ogrenci_t ogrs[] )
{
       int i,j;
    char ch;
    int tcInd;
    
    FILE * inp;

    inp = fopen( dosya , "r");

    for(i=0;i<numberOfUsers;++i){
    
        fscanf(inp,"%lf%c%d%c",&users[i].TCno,&ch,&users[i].mod,&ch);
        
        j=0;
        ch = ' ';
        while(ch != ',')
        {
     
            if(j != 0)
                users[i].kullanici[j-1] = ch ;
            fscanf(inp,"%c",&ch);
            ++j;   
        }
        
        j=0;
        ch = ' ';
        while(ch != '\n')
        {
            if(j != 0){
                users[i].sifre[j-1] = ch ;
            }
            
            fscanf(inp,"%c",&ch);
            ++j;   
        }

        if( users[i].mod == 1 ){
        	tcInd = searchOgr( ogrs, users[i].TCno , numberOfUsers  );
        	sprintf(ogrs[tcInd].sifrem , "%s", users[i].sifre );

        }else {
        	tcInd = searchEgit( egis, users[i].TCno, numberOfUsers );
        	sprintf( egis[tcInd].sifrem , "%s", users[i].sifre );

        }
        
    }
    
    fclose(inp);

}


int searchEgit( egitimci_t egis[],  double TC , int size ){
	int i;

	for( i=0; i< size; ++i )
		if( egis[i].TCno == TC  )
			return i;

	return -1;

}

int searchOgr( ogrenci_t ogrs[],  double TC , int size ){
	int i;

	for( i=0; i< size; ++i )
		if( ogrs[i].TCno == TC )
			return i;

	return -1;	
}


void CoursRead(char dosya[],ders_t ders[], int numberOfCours)
{
    int i,j,t, a;
    char ch;
    int status;
    int temp;
    char prereq[4];
    char line[1000];
    int num = 1000;        
    char Id[12];   
    int f;     
            
    FILE * inp;
    inp = fopen(dosya,"r");
    
    
    for(i=0;i<numberOfCours;++i){
        
        a=0;
        fgets( line, num, inp  ); 

        j=0;
        ch = ' ';
        while(ch != ','){
            ch = line[a];
            if( ch == ',' )
            	break;
			Id[j] = ch;
            ++a;
            ++j;   
        }

        Id[j] = '\0';   
        ders[i].ID = atoi( Id );

        j=0;
        line[a] = ' ';
        while( line[a] != ','){
     		++a;
     		if( line[a] == ',' )
     			break;
            ders[i].Ad[j] = line[a] ;
            ++j;   
        }


        j=0;
        line[a] = ' ';
        while( line[a] != ',' ){
            
            ch = line[a];
            if( ch == ',' )
            	break;
			Id[j] = ch;
            ++a;            
            ++j;   
        }

        Id[j] = '\0';   
        ders[i].egitimci = atof( Id );

        f = 0;
        for(t=0; line[a] == ',' || (line[a] >= '0' && line[a] <= '9') ;++t)
        {

           for( j=0; j < 3 ; ++j ){
             	     
                ++a;
                if( !(line[a] >= '0' && line[a] <= '9') )
                    break;
                prereq[j] = line[a];           
           }

           //fprintf(stderr, "line  **%c**\n", line[a]);

           if( line[a] == '\n'/*!(line[a] >= '0' && line[a] <= '9') && line[a] != ','*/ )
                break;

           prereq[j] = '\0';

           if( !(t%2 == 1)  ){
           	 ders[i].OnKosul[f] = atoi(prereq);
           	 ++f;	 
           }

        }	

        }      
               
    fclose(inp);
}


void InstrucRead(char dosya[], egitimci_t egitimci[], int numberOfIns )
{
    int i,j;
    char ch;
    
    FILE * inp;
    inp = fopen(dosya,"r");
    
    for(i=0;i<numberOfIns;++i){
    
        fscanf(inp,"%lf%c",&egitimci[i].TCno,&ch);
        
        j=0;
        ch = ' ';
        while(ch != ',')
        {
     
            if(j != 0)
                egitimci[i].Ad[j-1] = ch ;
                
            fscanf(inp,"%c",&ch);
            ++j;   
        }
        
        j=0;
        ch = ' ';
        while(ch != '\n')
        {
            if(j != 0)
                egitimci[i].Soyadi[j-1] = ch ;
            
            fscanf(inp,"%c",&ch);
            ++j;   
        }
        
    }
    
    fclose(inp);

}


int getLineNumber(char dosya[])
{
    int counter=0;
    char ch;
    
    FILE *inp = fopen(dosya,"r");
    
    
    while(  (fscanf(inp,"%c",&ch)) != EOF  ){
    
        if(ch == '\n' )
            ++counter;
    
    }

    return counter;
}
void StudentRead(char dosya[],ogrenci_t ogrenci[], int numberOfStud )
{
    int i,j;
    char ch;
    
    FILE * inp;
    inp = fopen(dosya,"r");

    for(i=0;i<numberOfStud;++i){
    
        fscanf(inp,"%lf%c",&ogrenci[i].TCno,&ch);
        
        j=0;
        ch = ' ';
        while(ch != ',')
        {
     
            if(j != 0)
                ogrenci[i].Ad[j-1] = ch ;
                
            fscanf(inp,"%c",&ch);
            ++j;   
        }
        
        j=0;
        ch = ' ';
        while(ch != ',')
        {
            if(j != 0)
                ogrenci[i].SoyAdi[j-1] = ch ;
            
            fscanf(inp,"%c",&ch);
            ++j;   
        }
        
        fscanf(inp,"%d%c%d",&ogrenci[i].OgrenciNo,&ch,&ogrenci[i].BasYili);
        
    }
    

    fclose(inp);
}


void listLessons( ogrenci_t ogrenci[], int index ){
	int i;

	fprintf(stderr, "-----------------------------------------------------\n" );
	if( ogrenci[index].AdersNum == 0 )
		fprintf(stderr, "Kayitli oldugu ders yok!!!\n" );

	for( i=0; i<ogrenci[index].AdersNum; ++i  )
		printf("%s\n",ogrenci[index].ADersler[i] );	
	fprintf(stderr, "-----------------------------------------------------\n" );

}

void addLesson( ogrenci_t ogrenci[], int index ){

	fprintf(stderr, "-----------------------------------------------------\n" );
	printf("Lutfen dersin adini giriniz : \n" );
	scanf("%s",ogrenci[index].ADersler[ogrenci[index].AdersNum++] );
	fprintf(stderr, "-----------------------------------------------------\n" );

}

void extractLesson( ogrenci_t ogrenci[], int index ){

	fprintf(stderr, "-----------------------------------------------------\n" );
	int i, j;
	char ders[20];
	printf("Lutfen cikaracaginiz dersin adini giriniz: \n");
	scanf( "%s", ders );

	for( i=0; i<ogrenci[index].AdersNum; ++i ){
		if( !strcmp( ogrenci[index].ADersler[i], ders ) ){
			for( j=i; j<ogrenci[index].AdersNum-1; ++j ){
				sprintf(ogrenci[index].ADersler[j] ,"%s",ogrenci[index].ADersler[j+1]  );		
			}
		}else{
			printf("Boyle bir dersiniz yok!!\n");
			fprintf(stderr, "-----------------------------------------------------\n" );
			return;
		}

		sprintf(ogrenci[index].ADersler[ogrenci[index].AdersNum--] ,"\0"  );

	}	
	fprintf(stderr, "-----------------------------------------------------\n" );

}


void stuMode( ogrenci_t ogrenci[], int numberStu ){

	int selection, isThere;
	double TcNum;
	char sifre[20];
	char ad[20];

	fprintf(stderr, "################################################\n" );
	    	fprintf(stderr, "< Ogrenci Modu >\n");
	    	fprintf(stderr, "Lütfen kullanıcı adı ve şifrenizi giriniz :\n" );
	    	fprintf(stderr, "Tc Number : \n" );
	    	scanf("%lf", &TcNum );
	    	fprintf(stderr, "Ad : \n" );
	    	scanf("%s", ad );
	    	fprintf(stderr, "Sifre : \n" );
	    	scanf("%s", sifre ) ;
	    	
	    	isThere = searchOgr( ogrenci, TcNum, numberStu );

	    	if( isThere != -1 ){
	    		fprintf(stderr, "----------------------------------------------------------\n" );
	    		printf("%s  %s giris yapti\n", ogrenci[isThere].Ad, ogrenci[isThere].SoyAdi );
	    		fprintf(stderr, "----------------------------------------------------------\n" );

	    		while( 1 ){
	    			
	    			printf("Secenekler : \n" );
	    			printf("1-) Dersleri Listele\n" );
	    			printf("2-) Ders Ekleme \n" );
	    			printf("3-) Ders Cikarma \n");
	    			printf("(-1)-) Cikis \n");
	    			scanf( "%d", &selection );

	    			switch( selection ){
	    				case 1:
	    					listLessons( ogrenci, isThere );
	    				break;
	    				case 2:
	    					addLesson( ogrenci, isThere );
	    				break;
	    				case 3:
	    					extractLesson( ogrenci, isThere );
	    				break;
	    				case -1:
	    					break;	
	    				default:
	    					printf("You selected wrong choice!!!Please choose again:\n");
	    			}

	    			if( selection == -1 )
	    				break;	
	    		}

	    	}else{
	    		fprintf(stderr, "Wrong Password!!Please enter the System again!!\n" );
	    		fprintf(stderr, "################################################\n" );
	    		exit(0);
	    	}


}

void instMode( egitimci_t egitimci[], int numberIns ){

	int selection, isThere;
	double TcNum;
	char sifre[20];
	char ad[20];

	fprintf(stderr, "################################################\n" );
	fprintf(stderr, "< Instructor Modu >\n");
	fprintf(stderr, "Lütfen kullanıcı adı ve şifrenizi giriniz :\n" );
	fprintf(stderr, "Tc Number : \n" );
	scanf("%lf", &TcNum );
	fprintf(stderr, "Ad : \n" );
	scanf("%s", ad );
	fprintf(stderr, "Sifre : \n" );
	scanf("%s", sifre ) ;
	
	isThere = searchEgit( egitimci, TcNum, numberIns );

	if( isThere != -1 ){
		fprintf(stderr, "----------------------------------------------------------\n" );
		printf("%s  %s giris yapti\n", egitimci[isThere].Ad, egitimci[isThere].Soyadi );
		fprintf(stderr, "----------------------------------------------------------\n" );
	}else{
		fprintf(stderr, "Wrong Password!!Please enter the System again!!\n" );
		fprintf(stderr, "################################################\n" );
		exit(0);
	}
	
}

int readBinIns(egitimci_t *egitimci , int a, int numberOfIns ){
    
    int i;
    FILE *inp;
    inp = fopen("egitimci.bin","rb");
    if( inp == NULL )
    	return -1;

    fread(&numberOfIns,sizeof(int),1,inp);

    if( a == 1 )
    	return numberOfIns;

    for(i=0;i<numberOfIns;++i)
     	fread(&egitimci[i],sizeof(egitimci_t),1,inp);
    


    return numberOfIns;
}

int readBinStu(ogrenci_t *ogrenci, int a, int numberOfStu ){
    
    int i;
    FILE *inp;
   	inp = fopen("ogrenci.bin","rb");

	    if( inp == NULL )
	    	return -1;

	    fread(&numberOfStu,sizeof(int),1,inp); 
	    if( a == 1 )
    		return numberOfStu;
	    	
	    for(i=0;i<numberOfStu;++i)
	        fread(&ogrenci[i],sizeof(ogrenci_t),1,inp);


    return numberOfStu;
}

int readBinUsers(users_t *users , int a, int numberOfUsers ){
    
    int i;
    FILE *inp;
	inp = fopen("kullanici.bin","rb");
 
	    if( inp == NULL )
	    	return -1;

	    fread(&numberOfUsers,sizeof(int),1,inp);
	    users = (users_t*)malloc(sizeof( users_t ) * numberOfUsers);
		
		if( a == 1 )
    		return numberOfUsers;

    	for(i=0;i < numberOfUsers ;++i)
        	fread(&users[i],sizeof(users_t),1,inp);



    return numberOfUsers;
}


void fillTheEgit( egitimci_t egitimci[], int numberOfIns ){

	int i;
	int size = numberOfIns;
	FILE *bin = fopen("egitimci.bin" , "wb" );
	    
	fwrite( &size, sizeof(int), 1, bin );
	
	for(i=0;i< numberOfIns ; ++i)
	    fwrite( &egitimci[i], sizeof(egitimci_t), 1, bin );
        
}

void fillTheStu( ogrenci_t ogrenci[], int numberOfStu ){

	int i;
	FILE *bin = fopen("ogrenci.bin" , "wb" );

	fwrite( &numberOfStu, sizeof(int), 1, bin );
	fwrite( ogrenci, sizeof(ogrenci_t), numberOfStu, bin );

}

void fillTheUsers( users_t users[], int numberOfUsers ){

	int i;
	FILE *bin = fopen("kullanici.bin" , "wb" );

	fwrite( &numberOfUsers, sizeof(int), 1, bin );
	fwrite( users, sizeof(ogrenci_t), numberOfUsers, bin );

}
