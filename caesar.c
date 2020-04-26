#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void encmsg(string x,int y);

int main(int argc,string argv[])
{
    if (argc!=2)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }
    else
    {       int count=0;
            for(int i=0,n=strlen(argv[1]);i<n;i++)
            {
                if ((argv[1][i]>='0') && (argv[1][i]<'9'))
                {
                     count+=1;
                }
                else
                {
                    break;
                }
            }
        if (count==strlen(argv[1]))
            {
                string s=get_string("plaintext:");
                int x=atoi(argv[1]);
                encmsg(s,x);
            }
        else
            {
                printf("usage: ./caesar key\n");
                return 1;
            }
    }
}

void encmsg(string x,int y)                             // function to rotate the alphabet
{
    for(int j=0,n=strlen(x);j<n;j++)
    {
        { if (isalpha(x[j])==0)
           {
              x[j]=x[j];
           }
           else
          {
            if (islower(x[j])!=0)
           {
               if (x[j]+y<=122)
             {
               x[j]=x[j]+y;
             }
            else
             {   int k=x[j]+y-26;
                 while(k>122)
                {
                   k-=26;
                }
                x[j]=k;
             }
           }
           else if (isupper(x[j])!=0)
          {
             if(x[j]+y<=90)
             {
                x[j]=x[j]+y;
             }
            else
             {
                int l=x[j]+y-26;
                while(l>90)
                {
                    l-=26;
                }
                x[j]=l;
            }
           }
         }
       }
    }
    printf("ciphertext:%s\n",x);
}