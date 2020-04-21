#include<stdio.h>
#include<cs50.h>
#include<math.h>
int coin(int n);
int main(void)
{
    float d;
    int c;
do
  {
     d=get_float("change owed:");
     c=round(d*100);
          }
     while (c<1);
     printf("%i\n",coin(c));
}
int coin(int n)
{     int co=0;
    while(n>0)
    {
        if(n>=25)
        {
            n=n-25;
            co=co+1;
        }
        else if(n<25 && n>=10)
        {
            n=n-10;
            co=co+1;
        }
        else if(n<10 && n>=5)
        {
            n=n-5;
            co=co+1;
        }
        else
        {
            n=n-1;
            co=co+1;
        }
    }
    return co;
} 
