/*#######################################################*/
/*The Program which calculates roots of three polynomials*/
/*111044069--created by Ramazan SAKİN                    */
/*#######################################################*/
#include<stdio.h>
#include<math.h>
    /*The formula is  "/\=b2 - 4ac  --  (-b+-kok/\)/2a"  */
    double getRoot(double a,double b,double c,int rootNumber);

int main(void)
{
    double root,a,b,c;
    int rootNumber;
	FILE*inp1,
	    *inp2,
	    *inp3,
    	    *outp;

	/*Files*//*firs Polynomial*/
	inp1=fopen("polynomials.txt","r");
	outp=fopen("polynomials.txt","a");
	
	fscanf(inp1,"%lf %lf %lf %d",&a,&b,&c,&rootNumber);	
	root=getRoot(a,b,c,rootNumber);	
	
	fprintf(outp,"The root that user wants is %.2f\n",root);
	
	/*Second Polynomial*/
	inp2=fopen("polynomials.txt","r");
	
	fscanf(inp2,"%lf %lf %lf %d",&a,&b,&c,&rootNumber);	
	root=getRoot(a,b,c,rootNumber);
	fprintf(outp,"The root that user wants is %.2f\n",root);
	
	/*Third Polynomial*/	
	inp3=fopen("polynomials.txt","r");
	
	fscanf(inp3,"%lf %lf %lf %d",&a,&b,&c,&rootNumber);	
	root=getRoot(a,b,c,rootNumber);
	fprintf(outp,"The root that user wants is %.2f",root);
	
	fclose(inp1);
	fclose(inp2);
	fclose(inp3);
	fclose(outp);


return 0;
}
	/*Fonksiyon katsayıları ve hangi koku istiyorsa degerleri polynomial dosyasından okuyor formulde yerine koyup istenilen koku veriyor...*/
	double getRoot(double a,double b,double c,int rootNumber)
	{
	double root,delta;
	delta= pow(b,2) - 4*a*c;		
	root= ( -b + sqrt(delta) * pow(-1,rootNumber)) / (2 * a);
		 
			
	/*iki kokude donduremedıgımızden kullanıcıdan 1. ve ya 2. koku isteriz. rootNumber da ona gore kökü - ve + sekilde cıkartır...*/	
	return root;  
	}
