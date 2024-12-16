#include <stdio.h>
#include <string.h>

int main()
{
    int length;
    printf("Enter string length:");
    scanf("%d",&length);
    char input[length];
    printf("Enter String:");
    scanf("%s",&input);
    int j=1;
    if(length<3)
    {
        printf("String length less than 3 not allowed");
    }
    else{
    if ((input[0] == 'a' || input[0] == 'b') && input[length - 1] == 'b' && input[length - 2] == 'b')
    {
        if(input[length-3]=='b')
    {
        printf("Invalid String\n");
    }

    else
    {
     for(int i=1;i<length-2;i++)
        {
        if(input[i]!='a' && input[i]!='b')
        {
            printf("Character other than a or b not allowed in the string");
            break;
        }

        }
    for(j;j<length-2;j++)
      {

        if(input[j-1]=='b' && input[j]=='a')
        {
            printf("b cannot be followed by a");
            break;
        }

      }

    if(j==length-2)
        {
            printf("Valid String");
        }

    }
    }
    else
     {
        printf("Invalid String\n");
    }
    }
}
