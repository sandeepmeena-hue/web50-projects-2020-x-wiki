#include<stdio.h>
#include<cs50.h>
#include<math.h>
int noofdi(long x);
int retdi(long y);
int sumoth(long z);
void typecard(void);
long n;
int main(void)
{
    do
    {
        n=get_long("Number: ");
    }
    while(n<1);
    typecard();
    }
int noofdi(long x)
{   int r=0;
    while(x>=10)
    {
        x=x/10;
        r=r+1;
    }
   r=r+1; 
   return r;
}
int retdi(long y)
{    int sum=0;
     int m;
     for(int j=1;j<noofdi(n);j+=2)
     {    y=n;
         for(int i=0;i<j;i++)
     {
         y=y/10;
     }
     if (y>10)
     {
         m=(y%10)*2;
     }
     else 
     {
         m=y*2;
     }
     if (m<10)
     {
         sum+=m;
     } 
     else 
     {
         sum+=m/10+m%10;
     }
     } return sum;
}
int sumoth(long z)
{
    int sum1=0;
    for(int k=0;k<noofdi(n);k+=2)
     {  z=n;
        for(int j=0;j<k;j++)
        {
            z=z/10;
        }
        if (z>10)
        {
            sum1+=z%10;
               }
        else 
        {
            sum1+=z;
        }       
     } return sum1;
}
void typecard(void)
{     int u=sumoth(n)+retdi(n);
         if (u%10==0)
          {
              if (noofdi(n)==15)
              {
                  printf("AMEX\n");
              }
              else if (noofdi(n)==16)
              {   for(int i=noofdi(n);i<0;i--)
                  {
                      n=n/10;
                  }
                  if (n==5)
                  {
                      printf("MASTERCARD\n");
                        }
                  else
                  {
                      printf("VISA\n");
                  }      
              }
              else if (noofdi(n)==13)
              {
                  printf("VISA\n");
              }
              else
              {
                  printf("INVALID\n");
              }
          }
    else
    {
        printf("INVALID\n");
    }    
}
