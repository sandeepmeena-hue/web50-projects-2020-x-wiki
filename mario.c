#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int n;
   do
   {
       n=get_int("size:");
       if (n==9)
      { n=2;
      }
   }
   while(n<1);
   for(int i=0;i<n;i++)
   {
       for(int j=0;j<n;j++)
       {
           if(i+j>=n-1)
           {
               printf("#");
           }
           else
           {
               printf(" ");
           }
       }
       printf("\n");
   }
}
