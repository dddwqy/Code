#include<stdio.h>
#include<math.h>

int main()
{
  int n;
  scanf("%d",&n);
  double i=1.0;
  double q=1.0;
  double s=1.0;
  double sum=0.0;

 while(1)
 {    
     q=s/i;
     sum+=q;
     s=-1.0*s;
     i=i+2;
     if((1/i)<=pow(0.1,n))
     {
        break;
     }
  }
  sum=4*sum;
  printf("%lf\n",sum);
  return 0;
}