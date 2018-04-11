
/****************************************************************

    PROJE -- OGUZHAN KARADAYI  -- 111044024

      Yapabildikleri : 

      >>>Eger Binary dosyaları olusmamıs ise csv dosyaları okunarak 
    dosyadaki veriler structlara aktarılıyor ve herhangi bir degişiklikte struct lar güncelleniyor ve
    binary dosyalara en son halini yazdırıyorum. Ikinci calismada da olusturulan binary dosyalaradan okuma
    yapılarak structlar dolduruluyor.

      >>>Ogrenci Modundaki ekleme, cıkarma ve dersleri listeleme işlevlerini dogru bir şekilde yapıyor.
      Eger ders yoksa kullanıcı uyarılıyor.     

      Yapamadıkları :

      >>>Instructor Modunda egitimci Tc no , Kullanıcı ismi ve şifresi bulunarak giriş yapılabiliyor ama 
      herhangi bir secenek implement edilmemistir ...   


*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PR_111044024.h"

int main(int argc, char const *argv[]){

    char StuFile[] ="Students.csv";
    char InsFile[] = "Instructors.csv";
    char CoursFile[] = "Courses.csv";
    char UsersFile[] = "Users.csv";
    int choice;
    char ad[20];
    char sifre[20];
    double TcNum;
    int selection, isThere, i, temp=0;	

    ogrenci_t *ogrenci;
    egitimci_t *egitimci;
    ders_t *ders;
    users_t *users;    

    int numberStu,numberIns,numberCours, numberUsers;
    
    if( ( temp = readBinStu( ogrenci, 1, 0 ) ) == -1 ){
        numberStu = getLineNumber(StuFile);
        ogrenci = (ogrenci_t*)malloc(sizeof(ogrenci_t) * numberStu);
        
        StudentRead(StuFile ,ogrenci , numberStu );
    }
    
    if( temp != -1 ){
        numberStu = temp;
        ogrenci = (ogrenci_t*)malloc(sizeof(ogrenci_t) * numberStu);
        readBinStu( ogrenci, 2, numberStu );
    }

    for( i=0; i < numberStu -1; ++i )
    	ogrenci[i].AdersNum = 0;

    if(  (temp = readBinIns( egitimci, 1, 0 ) ) == -1 ){
        numberIns = getLineNumber(InsFile);
        egitimci = (egitimci_t*)malloc(sizeof(egitimci_t) * numberIns);
        InstrucRead(InsFile,egitimci,numberIns);
    }
    
    if( temp != -1 ){
        numberIns = temp;
        egitimci = (egitimci_t*)malloc(sizeof(egitimci_t) * numberIns);
        readBinIns( egitimci, 2, numberIns );
    }

    numberCours = getLineNumber(CoursFile);
    ders = (ders_t*)malloc(sizeof(ders_t) * numberCours);
    CoursRead(CoursFile,ders,numberCours);
    
    if( (temp = readBinUsers( users, 1, 0 ) ) == -1 ){
        numberUsers = getLineNumber( UsersFile );
        users = (users_t*)malloc(sizeof(users_t) * numberUsers);
        UsersRead( UsersFile , users , numberUsers, egitimci, ogrenci );	
    }

    if( temp != -1 ){
        numberUsers = temp;
        users = (users_t*)malloc(sizeof(users_t) * numberUsers);
        readBinUsers( users, 2, numberUsers );
    }


    fprintf(stderr, "################################################\n" );
    fprintf(stderr, "## OGRENCI OTOMASYON SISTEMI' ne Hoşgeldiniz. ##\n");
    fprintf(stderr, "################################################\n\n\n" );

    while( 1 ){
	    fprintf(stderr, "# Lütfen modu girin : ( 1:stu - 2:inst )\n-> " );	
	    scanf("%d",&choice);
	    
	    if( choice == 1 ){
	    	stuMode( ogrenci, numberStu );
	    	break;
	    }else if ( choice == 2 ){
	    	instMode( egitimci, numberIns );
	    	break;
		}else
			fprintf(stderr, "Hatalı Mod!!! Lütfen Tekrar Deneyin!!\n" );
	}

	fprintf(stderr, "###########################################################\n" );
	fprintf(stderr, "----------- OGRENCI OTOMASYON SISTEMI kapatıldı  ---------- \n");
	fprintf(stderr, "###########################################################\n" );

	fillTheEgit( egitimci, numberIns );
	fillTheUsers( users, numberUsers );
    fillTheStu( ogrenci, numberStu );

    free(users);
    free(ogrenci);
    free(egitimci);

    return 0;   
}
