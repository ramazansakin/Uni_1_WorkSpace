/*The program which finds premeter and area of a triangular*/

/*Hocam normal ücgen olma sartlarını sağlayan sayılar verildiğinde sıkıntı olmuyo ama 5-3-2 kenarlarından ücgen olmadıgından sonucu 0 veriyo...*/

#include<stdio.h>
#include<math.h>

int main()
{
	double area,premeter,edge1,edge2,edge3,u;

	printf("Please enter the edges of the triangular:\n");
	scanf("%lf%lf%lf",&edge1,&edge2,&edge3);
	premeter=edge1+edge2+edge3;
	u=premeter/2;
	/*I use this formula => area=u(u-a)(u-b(u-c) kök    		icinde */ 
	area=u*(u-edge1)*(u-edge2)*(u-edge3);
	
	printf("The premeter of the triangular is %.3f\n",premeter);
	printf("The area of the triangular is %.3f\n",sqrt(area));

return 0;
}
