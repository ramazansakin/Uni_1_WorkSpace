
#ifndef KARADAYI_H
#define KARADAYI_H


#define ISIMS 50
#define SIZE 50

typedef struct{

    double TCno;
    int mod;
    char kullanici[SIZE];
    char sifre[SIZE];

}users_t;

typedef struct{

    double TCno;
    char Ad[SIZE];
    char Soyadi[SIZE];
    char VerDers[SIZE];
    char sifrem[20];
    
}egitimci_t;

typedef struct{

    double ID;
    char Ad[SIZE];
    double egitimci;
    int OnKosul[SIZE];
    double Olusturan;
    int A_K;
    
}ders_t;

typedef struct{
    
    double TCno;
    char Ad[ISIMS];
    char SoyAdi[ISIMS];
    int OgrenciNo;
    int BasYili;
    char ADersler[SIZE][SIZE];
    char GDersler[SIZE][SIZE];
    int AdersNum;
    double Notlar[SIZE];
    char sifrem[20];

}ogrenci_t;

void StudentRead(char dosya[],ogrenci_t ogrenci[], int numberOfStud );
void InstrucRead(char dosya[],egitimci_t egitimci[], int numberOfIns);
void CoursRead(char dosya[],ders_t ders[], int numberOfCours);
int getLineNumber(char dosya[]);
void UsersRead(char dosya[],users_t users[], int numberOfUsers, egitimci_t egis[] , ogrenci_t ogrs[] );
int searchEgit( egitimci_t egis[],  double TC , int size );
int searchOgr( ogrenci_t ogrs[],  double TC , int size );
void listLessons( ogrenci_t ogrenci[], int index );
void addLesson( ogrenci_t ogrenci[], int index );
void extractLesson( ogrenci_t ogrenci[], int index );
void stuMode( ogrenci_t ogrenci[], int numberStu );
void instMode( egitimci_t egitimci[], int numberIns );
void fillTheEgit( egitimci_t egitimci[], int numberOfIns );
void fillTheStu( ogrenci_t ogrenci[], int numberOfStu );
void fillTheUsers( users_t users[], int numberOfUsers );
int readBinIns(egitimci_t *egitimci , int a, int numberOfIns );
int readBinStu(ogrenci_t *ogrenci, int a, int numberOfStu );
int readBinUsers(users_t *users , int a, int numberOfUsers );


#endif