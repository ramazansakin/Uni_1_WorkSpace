/*#################################################################*/
/*The program that calculates 5 employees' salary without functions*/
/*111044069-Created by Ramazan Sakin                               */
/*#################################################################*/
    #include<stdio.h>
    #include<math.h>
    #define WORKING_HOURS 184
    #define BHP 6
    #define ADDITIONAL_PAY_MULT 1.5
    #define LOPM 0.8
    #define QOPM 0.15
    #define WDOM 2
    #define WEOM 3

	int main(void)
{
	int opb,WY,NofP,PerPo,DMult,wdo,weo;  
	/*WY=working years--NofP=number of project--DMult=Department Multiplier*/
	double SperH,ExpPo,overtimepayment,salary,normalpayment;	
        /*SperH=salary per hour--ExpPo=Experience point*/

/*open files*/
FILE*inp1,
    *inp2,
    *inp3,
    *inp4,
    *inp5,
    *outp;

  	inp1=fopen("Employee1.txt","r");
  	inp2=fopen("Employee2.txt","r");
  	inp3=fopen("Employee3.txt","r");
  	inp4=fopen("Employee4.txt","r");
  	inp5=fopen("Employee5.txt","r");
  	outp=fopen("Salaries.txt","w");

    	/*Salary of First Employee*/
    	fscanf(inp1,"%d %d %d %d",&WY ,&NofP ,&PerPo, &DMult);
    
    	printf("Please enter overtime working hours for first employee as weekday and weekend orderly:\n");

    	scanf("%d %d",&wdo,&weo);/*to take overtime working hours*/  

    	/*calculating salary*/
    	ExpPo=log(WY*NofP)/log(2);
    	SperH=BHP+ADDITIONAL_PAY_MULT*DMult*(ExpPo+PerPo);     
    	opb=WEOM*weo+WDOM*wdo;
    	normalpayment=SperH*WORKING_HOURS;
    	overtimepayment=(QOPM*pow(opb,2)+LOPM*opb)*SperH;
    	salary=normalpayment+overtimepayment;    

    	fprintf(outp,"The salary of first employee is %.2f\n",salary);


    	/*Salary of Second Employee*/
    	fscanf(inp2,"%d %d %d %d",&WY ,&NofP ,&PerPo, &DMult);
    
    	printf("Please enter overtime working hours for second employee as weekday and weekend orderly:\n");

    	scanf("%d %d",&wdo,&weo);/*to take overtime working hours*/  

    	ExpPo=log(WY*NofP)/log(2);
    	SperH=BHP+ADDITIONAL_PAY_MULT*DMult*(ExpPo+PerPo);     
    	opb=WEOM*weo+WDOM*wdo;
    	normalpayment=SperH*WORKING_HOURS;
    	overtimepayment=(QOPM*pow(opb,2)+LOPM*opb)*SperH;
    	salary=normalpayment+overtimepayment;    
 
    	fprintf(outp,"The salary of second employee is %.2f\n",salary);
    

    	/*Salary of Third Employee*/
    	fscanf(inp3,"%d %d %d %d",&WY ,&NofP ,&PerPo, &DMult);
    	printf("Please enter overtime working hours for third employee as weekday and weekend orderly:\n");

    	scanf("%d %d",&wdo,&weo);/*to take overtime working hours*/  

    	ExpPo=log(WY*NofP)/log(2);
    	SperH=BHP+ADDITIONAL_PAY_MULT*DMult*(ExpPo+PerPo);     
    	opb=WEOM*weo+WDOM*wdo;
    	normalpayment=SperH*WORKING_HOURS;
    	overtimepayment=(QOPM*pow(opb,2)+LOPM*opb)*SperH;
    	salary=normalpayment+overtimepayment;    
	
    	fprintf(outp,"The salary of third employee is %.2f\n",salary);


    	/*Salary of Fourth Employee*/
    	fscanf(inp4,"%d %d %d %d",&WY ,&NofP ,&PerPo, &DMult);
    
    	printf("Please enter overtime working hours for forth employee as weekday and weekend orderly:\n");

    	scanf("%d %d",&wdo,&weo);/*to take overtime working hours*/  

    	ExpPo=log(WY*NofP)/log(2);
    	SperH=BHP+ADDITIONAL_PAY_MULT*DMult*(ExpPo+PerPo);     
    	opb=WEOM*weo+WDOM*wdo;
    	normalpayment=SperH*WORKING_HOURS;
    	overtimepayment=(QOPM*pow(opb,2)+LOPM*opb)*SperH;
    	salary=normalpayment+overtimepayment;    
	
    	fprintf(outp,"The salary of fourth employee is %.2f\n",salary);    



    	/*Salary of Fifth Employee*/
    	fscanf(inp5,"%d %d %d %d",&WY ,&NofP ,&PerPo, &DMult);
    	
    	printf("Please enter overtime working hours for fifth employee as weekday and weekend orderly:\n");

    	scanf("%d %d",&wdo,&weo);/*to take overtime working hours*/  
	
    	ExpPo=log(WY*NofP)/log(2);
    	SperH=BHP+ADDITIONAL_PAY_MULT*DMult*(ExpPo+PerPo);     
    	opb=WEOM*weo+WDOM*wdo;
    	normalpayment=SperH*WORKING_HOURS;
    	overtimepayment=(QOPM*pow(opb,2)+LOPM*opb)*SperH;
    	salary=normalpayment+overtimepayment;    
	
    	fprintf(outp,"The salary of fifth employee is %.2f\n",salary);
    	
	/*close the open files*/
    	fclose(inp1);
    	fclose(inp2);
    	fclose(inp3);
    	fclose(inp4);
    	fclose(inp5);
    	fclose(outp);
	
return 0;
}
