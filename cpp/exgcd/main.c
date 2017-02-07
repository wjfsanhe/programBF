#include <stdlib.h> 
#include <stdio.h>


int gcd(int a,int b,int* x,int* y)//扩展欧几里德算法
{
        if(0==b)
        {
                *x=1;
                *y=0;
                return a;
        }
        int r;
        int x_i_2=1,y_i_2=0,x_i_1=0,y_i_1=1,x_i,y_i;
        while(r=a%b)
        {
                x_i=x_i_2-a/b*x_i_1;
                y_i=y_i_2-a/b*y_i_1;
                x_i_2=x_i_1;
                y_i_2=y_i_1;
                x_i_1=x_i;
                y_i_1=y_i;
                a=b;
                b=r;
        }
        *x=x_i;
        *y=y_i;
        return b;
}
int exGcd(int a,int b,int *x,int *y)
{
	if(b==0)
	{
		*x=1;*y=0;
		return a;
	}
	int r=exGcd(b,a%b,x,y);
	int t=*x;
	*x=(*y);
	*y=t-a/b*(*y);
	printf ("[ret] %d - %d\n",*x,*y);
	return r;
} 
int main (char argc,char ** argv){

	int x,y;
	int a,b ;
	int t;

	printf("please input two number\n");
	scanf("%d %d",&a,&b);
	t = exGcd(a,b,&x,&y);
//	t = gcd(a,b,&x,&y);
	printf("gcd(%d , %d ) = %d, a^(-1)(mod b) = %d, b^(-1)(mod a) = %d \n",a,b,t,x,y);

}
