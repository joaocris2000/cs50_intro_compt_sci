#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int is_not_digit(char k[], int n_input);
char rotate(char letter, int k);

int main (int argc,char* argv[])
{
    int k;
    if (is_not_digit(argv[1], argc)==1)   //check if the user cooperated
    {
        printf("Usage ./caesar key");
        return 1;
    }
    else
    {
        k =atoi(argv[1])%26; //the alphabet has 26 letters, if k=26 it's the same letter
    }
    char textplain[600];
    printf("PlainText: ");
    gets(textplain);
    char cifredtext[600];
    for (int i=0; i<strlen(textplain); i++)
    {
        if (isalpha(textplain[i]))
        {
            cifredtext[i]=rotate(textplain[i], k);
        }
        else
        {
            cifredtext[i]=textplain[i];
        }
    }
    printf("CifredText: ");
    for (int i=0; i<strlen(textplain); i++)
    {
        printf("%c", cifredtext[i]);
    }
}


int is_not_digit(char k[], int n_input)
{
    if (n_input!=2)  //making sure it has the exe name and just another string
    {
        return 1; 
    }
    for( int i=0; i<strlen(k); i++)  //check if the string is just composed of numbers
    {
        if (!isdigit(k[i]))
        {
            return 1; 
        }
    }
    return 0;    //returns something diferent than 1
}

char rotate(char letter, int k)
{
    char new_letter=letter+k;
    if(isupper(letter))
    {
        if(new_letter<=90)
        {
            return new_letter;
        }
        else
        {
            new_letter=(new_letter-91)+65;
        }
    }
    else
    {
        if(new_letter<=122)
        {
            return new_letter;
        }
        else
        {
            new_letter=(new_letter-123)+97;
        }
    }

