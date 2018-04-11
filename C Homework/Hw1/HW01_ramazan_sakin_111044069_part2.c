#include <stdio.h>
#include <math.h>

    #define WORKING_HOURS		 184
    #define BHP		                   6
    #define ADDITIONAL_PAY_MULT	         1.5
    #define LOPM			 0.8
    #define QOPM			0.15
    #define WDOM			   2
    #define WEOM		 	   3

	int getWeekdayOvertime(int employeeNo);

	int getWeekendOvertime(int employeeNo);

	double obtainDataAndCalculateSalary(FILE* employeeFile, int employeeNo);
	
	double CalculateSalary(int workingYear, int NumOfProject, int performancePoint, double departmentMultiplier, int weekdayOvertime, int weekendOvertime);
	
	double getSalaryPerHour(int workingYear, int NumOfProject, int performancePoint, double departmentMultiplier);

	double getOvertimePayment(int weekdayOvertime, int weekendOvertime, double SalaryPerHour);

	void writeSalaryToFile(FILE* outFile, int employeeNo, double salary);

int main(void)
{
	double salary;

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

	salary=obtainDataAndCalculateSalary(inp1,1);   
	writeSalaryToFile(outp,1,salary);   
	
	salary=obtainDataAndCalculateSalary(inp2,2);
	writeSalaryToFile(outp,2,salary); 
	
	salary=obtainDataAndCalculateSalary(inp3,3);
   	writeSalaryToFile(outp,3,salary); 
	
	salary=obtainDataAndCalculateSalary(inp4,4);
	writeSalaryToFile(outp,4,salary); 
        
	salary=obtainDataAndCalculateSalary(inp5,5);
        writeSalaryToFile(outp,5,salary);     

	fclose(inp1);	
	fclose(inp2);
	fclose(inp3);
	fclose(inp4);	
	fclose(inp5);
	fclose(outp);

	return 0;
}


/*Functions*/
int getWeekdayOvertime(int employeeNo)
{
	int wdayo;
	printf("Please enter the weekday overtime of %d.emloyee:\n",employeeNo);
	scanf("%d",&wdayo);
	return wdayo;
}


int getWeekendOvertime(int employeeNo)
{
	int wendo;
	printf("Please enter the weekend overtime of %d.emloyee:\n",employeeNo);
	
	scanf("%d",&wendo);
	return wendo;
}


double obtainDataAndCalculateSalary(FILE*employeeFile, int employeeNo)
{
	int workingYear, NumOfProject, performancePoint; 
	int weekdayOvertime,weekendOvertime;
	double departmentMultiplier;
	double SalaryPerHour,OvertimePayment,salary;	

	fscanf(employeeFile, "%d %d %d %lf", &workingYear, &NumOfProject, &performancePoint, &departmentMultiplier);

	weekdayOvertime= getWeekdayOvertime(employeeNo);
	weekendOvertime= getWeekendOvertime(employeeNo);

	SalaryPerHour= getSalaryPerHour(workingYear, NumOfProject, performancePoint, departmentMultiplier);
	
	OvertimePayment= getOvertimePayment(weekdayOvertime, weekendOvertime, SalaryPerHour);

	salary= CalculateSalary(workingYear, NumOfProject, performancePoint, departmentMultiplier, weekdayOvertime, weekendOvertime);

	return salary;
}
	

double CalculateSalary(int workingYear, int NumOfProject, int performancePoint, double departmentMultiplier, int weekdayOvertime, int weekendOvertime)
{
	double SalaryPerHour,OvertimePayment,normalPayment,salary;

	SalaryPerHour= getSalaryPerHour(workingYear, NumOfProject, performancePoint, departmentMultiplier);
	
	OvertimePayment= getOvertimePayment(weekdayOvertime, weekendOvertime, SalaryPerHour);

	normalPayment= SalaryPerHour * WORKING_HOURS;
	
	salary=normalPayment+OvertimePayment;
	
	return salary;
}



double getSalaryPerHour(int workingYear, int NumOfProject, int performancePoint, double departmentMultiplier)
{
	int ExperiencePoint;
	double SalaryPerHour;	

	ExperiencePoint= log(workingYear*NumOfProject)/log(2);
	
	SalaryPerHour=BHP+ADDITIONAL_PAY_MULT*departmentMultiplier * (ExperiencePoint + performancePoint);

	return SalaryPerHour;
}

double getOvertimePayment(int weekdayOvertime, int weekendOvertime, double SalaryPerHour)
{
	int opb;
	double overtimePayment;
	
	opb= WEOM*weekendOvertime + WDOM*weekdayOvertime;

	overtimePayment= (QOPM*pow(opb,2)+LOPM*opb)*SalaryPerHour;

	return overtimePayment;
}
void writeSalaryToFile(FILE*outp, int employeeNo, double salary)
{
	fprintf(outp,"Salary of the %d. employee is %.2f\n",employeeNo,salary);
}
