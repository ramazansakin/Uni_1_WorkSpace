#include<stdio.h>

char gradeToLetter(double grade);

int main(void)
{
	double exam1,
	       exam2,
		   exam3,
		   exam4,
		   exam5,
		   average,
			sum;

	int numberOfExams;

	char grade ;


	printf("Please enter number of exams");
	scanf("%d",&numberOfExams);

	if( numberOfExams <= 0 || numberOfExams > 5)
		{
			printf("Please enter number which between 1 and 5" );
			scanf("%d",&numberOfExams);
		}

		if( numberOfExams == 1)
			{ 
				printf("Please enter exam1:");
				scanf("%lf",&exam1);
				
			
				sum = exam1;
				average = sum / (double)numberOfExams;
				grade = gradeToLetter(average);
			}

			if( numberOfExams == 2)
			{ 
				printf("Please enter exam1:");
				scanf("%lf",&exam1);
				printf("Please enter exam2:");
				scanf("%lf",&exam2);
				sum = exam1 + exam2;
				average = sum / (double)numberOfExams;
				grade = gradeToLetter(average);
			}
			
			if( numberOfExams == 3)
			{
				printf("Please enter exam1:");
				scanf("%lf",&exam1);
				printf("Please enter exam2:");
				scanf("%lf",&exam2);
				printf("Please enter exam3:");
				scanf("%lf",&exam3);
				sum = exam1 + exam2 + exam3;
				average = sum / (double)numberOfExams;
				grade = gradeToLetter(average);
			}

				if( numberOfExams == 4)
			{
				printf("Please enter exam1:");
				scanf("%lf",&exam1);
				printf("Please enter exam2:");
				scanf("%lf",&exam2);
				printf("Please enter exam3:");
				scanf("%lf",&exam3);
				printf("Please enter exam4:");
				scanf("%lf",&exam4);
				sum = exam1 + exam2 + exam3 + exam4;
				average = sum / (double)numberOfExams;
				grade = gradeToLetter(average);
			}

					if( numberOfExams == 5)
			{
				printf("Please enter exam1:");
				scanf("%lf",&exam1);
				printf("Please enter exam2:");
				scanf("%lf",&exam2);
				printf("Please enter exam3:");
				scanf("%lf",&exam3);
				printf("Please enter exam4:");
				scanf("%lf",&exam4);
				printf("Please enter exam5:");
				scanf("%lf",&exam5);
				sum = exam1 + exam2 + exam3 + exam4 + exam5;
				average = sum / (double)numberOfExams;
				grade = gradeToLetter(average);
			}

			printf("Your grade is %c \n",grade);
			return 0;
}

char gradeToLetter(double average)

{

		if(average >= 99)
			return 'A';
		if(average >=80)
			return 'B';
		if(average >=50)
			return 'C';
		if(average >=20)
			return 'D';
		if(average >=1)
			return 'E';
		if(average >=0)
			return 'F';

}





