#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void grade(string x);

int main(void)
{
    string s=get_string("Text: ");
    grade(s);                                       //  calling grade function

}
 // function to calculate index
void grade(string x)
{
    int sentence=0;
    int letter=0;
    int word=0;
    int none=0;
    for(int i=0,n=strlen(x);i<n;i++)
    {
        if ((x[i]=='.') || (x[i]=='!') || (x[i]=='?'))             // counting sentence
        {
            sentence+=1;
        }
        else if (x[i]==' ')                                       // counting word
        {
            word+=1;
        }
        else if ((islower(x[i])==0) || (isupper(x[i])==0))         // counting letter
        {
            letter+=1;
        }
        else
        {
            none+=1;                                             // if other case happen other than above
        }
    }
    float l= (float)letter/(word+1)*100;
    float s=(float)sentence/(word+1)*100;
    int index= 0.0588*l-0.296*s-15.8;
    if (index<1)
    {
        printf("Before Grade 1\n");
    }
    else if (index>16)
    {  
        
        printf("Grade 16+\n");
    }
    else
    {   if (index==4)
        {
            printf("Grade 5\n");
        }
        else
        {
            printf("Grade %i\n",index);
        }
    }
}
