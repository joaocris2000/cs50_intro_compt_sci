//lab 2 from CS50’s Introduction to Computer Science
//in a scrable game, from two words decide which has more points
#include<stdio.h>
#include<string.h>
#include<ctype.h>
int compute_score(char word[]);

int main (int argc,char* argv[])
{
    //get words
    char word1[30], word2[30];
    printf("Player 1: ");
    gets(word1);
    printf("Player 2: ");
    gets(word2);
    //get scores from each word
    int score1=compute_score(word1);
    int score2=compute_score(word2);
    //compare scores
    if(score1>score2)
    {
        printf("PAYLER 1 WINS");
    }
    else if (score1<score2)
    {
        printf("PLAYER 2 WINS");
    }
    else
    {
        printf("TIE!!!!");
    }
}

int compute_score(char word[])
{
    
    int points=0;
    //pontuate every letter
    for(int i=0; i<strlen(word); i++)
    {
        //select each letter from the string aka char array
        char l=word[i];
        //turn every letter in the word into uppercase
        l=toupper(l);
        switch (l) 
        {
            case 'A' :
                points=points+1;
                break; 
            case 'B' :
                points=points+3;
                break;
            case 'C' :
                points=points+3;
                break;   
            case 'D':
                points=points+2;
                break;
            case 'E':
                points=points+1;
                break;
            case 'F':
                points=points+4;
                break;
            case 'G':
                points=points+2;
                break;
            case 'H':
                points=points+4;
                break;
            case 'I':
                points=points+1;
                break;
            case 'J':
                points=points+8;
                break;
            case 'K':
                points=points+5;
                break;
            case 'L':
                points=points+1;
                break;
            case 'M':
                points=points+3;
                break;
            case 'N':
                points=points+1;
                break;
            case 'O':
                points=points+1;
                break;
            case 'P':
                points=points+3;
                break;
            case 'Q':
                points=points+10;
                break;
            case 'R':
                points=points+1;
                break;
            case 'S':
                points=points+1;
                break;
            case 'T':
                points=points+1;
                break;
            case 'U':
                points=points+1;
                break;
            case 'V':
                points=points+4;
                break;
            case 'W':
                points=points+4;
                break;
            case 'X':
                points=points+8;
                break;
            case 'Y':
                points=points+4;
                break;
            case 'Z':
                points=points+10;
                break;
            default:
                points=points+0;
        }
    }
    return points;
}
