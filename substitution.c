#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void encry(string x,string y);

int main(int argc,string argv[])
{   int count=0;
    if (argc!=2)
    {
        printf("usage: ./substitution key\n");
        return 1;
    }
    else
    {   if (strlen(argv[1])==26)
            {   for(int i=0,n=strlen(argv[1]);i<n;i++)
                {
                    if(isalpha(argv[1][i])!=0)
                    {
                      for(int j=0;j<26;j++)
                      {
                          for(int k=j+1;k<27;k++)
                          {
                              if (tolower(argv[1][j])==tolower(argv[1][k]))
                              {
                                  return 1;
                              }
                              else
                              {
                                  count+=1;
                              }
                          }
                      }
                    }
                    else
                    {
                        return 1;
                    }
                }
           }
        else
        {
            printf("usage: ./substitution key\n");
            return 1;
        }

    }

        if (count==9126)
        {
            string s=get_string("plaintext:");
            encry(s,argv[1]);
        }
        else
        {
            printf("usage: ./substitution key\n");
            return 1;
        }
}

void encry(string x,string y)
{   
    for(int i=0,n=strlen(x);i<n;i++)
    {
        for(int j=0;j<26;j++)
        {   if (islower(x[i])!=0)
            {    if(x[i]=='a'+j)
                {
                    x[i]=tolower(y[j]);
                    break;                  
                }
            }
            else if (isupper(x[i])!=0)
            {   if (x[i]=='A'+j)
                 {
                     x[i]=toupper(y[j]);
                     break;
                 }
            }
            else
            {
                x[i]=x[i];
                break;
            }
        }
    }
    printf("ciphertext:%s\n",x);
}
