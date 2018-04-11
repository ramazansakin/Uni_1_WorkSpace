#include<stdio.h>


	char gradeToLetter(double grade);

int
main(void)
{
	int numberOfExams,mark1,mark2,mark3,mark4,mark5;
	char grade,aver;
	
	printf("Please enter number of exams of the student:\n");
	scanf("%d",&numberOfExams);
	
	if( numberOfExams > 5 || numberOfExams <= 0 ){
		printf("the exam numbers are the most 5 and at least 1!\n"); 		printf("Try again to calculate your grade!\n");	
		return 0;
		}
	
	printf("Please enter the marks of the student:\n");
	
	if ( numberOfExams == 1 ){
		scanf("%d",&mark1);
		grade=mark1;
		}
	if ( numberOfExams == 2 ){
		scanf("%d %d",&mark1,&mark2);
		grade=(mark1 + mark2)/2;
		}
	if ( numberOfExams == 3 ){
		scanf("%d %d %d",&mark1,&mark2,&mark3);
		grade=(mark1+ mark2 + mark3)/3 ;
		}
	if ( numberOfExams == 4 ){
		scanf("%d %d %d %d",&mark1,&mark2,&mark3,&mark4);
		grade=(mark1+ mark2 + mark3 + mark4)/4;
		}
	if ( numberOfExams == 5 ){
		scanf("%d %d %d %d %d",&mark1,&mark2,&mark3,&mark4,&mark5);
		grade=(mark1+ mark2 + mark3 + mark4 + mark5 )/5 ;
		}
		
		grade=gradeToLetter(grade);
		
	printf("Your grade is %c\n",grade);

return 0;
}

	char gradeToLetter(double grade)
			{
			
			 if      ( grade == 100 )
			          grade = 'A';
			else if  ( grade <= 99 && grade >= 80)
			 	  grade = 'B';
			 else if ( grade <= 79 && grade >= 50)
			 	  grade = 'C';
		         else if ( grade <= 49 && grade >= 20)
			 	  grade = 'D';
			 else if ( grade <= 19 && grade >= 1)	
				  grade = 'E';
			 else if ( grade == 0)
			 	  grade = 'F';
			 		
			return    grade;
			}	
