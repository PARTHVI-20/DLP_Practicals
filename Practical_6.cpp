#include <iostream>
using namespace std;

#define SUCCESS 1
#define FAILED 0

const char *pointer;


int S();
int L();
int Ldash();

int main()
{
    string input;
    cout << "Enter String: ";
    cin >> input;
    pointer = input.c_str();

    int result = S();

    if (result && *pointer == '\0')
    {
        cout << "String parsed successfully";
    }
    else
    {
        cout << "String not parsed successfully";
    }
}

int S()
{
    if (*pointer == '(')
    {
        pointer++;

        if (L())
        {
            if (*pointer == ')')
            {
                pointer++;
                return SUCCESS;
            }
            else
            {
                return FAILED;
            }
        }
        else
        {
            return FAILED;
        }
    }
    else if (*pointer == 'a')
    {
        pointer++;
        return SUCCESS;
    }
    else
    {
        return FAILED;
    }
}

int L()
{
    if (S())
    {
        if (Ldash())
        {
            return SUCCESS;
        }
        else
        {
            return FAILED;
        }
    }
    else
    {
        return FAILED;
    }
}

int Ldash()
{
    if (*pointer == ',')
    {
        pointer++;
        if (S())
        {
            if (Ldash())
            {
                return SUCCESS;
            }
            else
            {
                return FAILED;
            }
        }
        else
        {
            return FAILED;
        }
    }
    return SUCCESS;
}
