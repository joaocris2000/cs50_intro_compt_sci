#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9

typedef struct 
{
    char name[10];
    int votes;
}
candidate;

//global variables
candidate candidates[MAX];
int n_candidates;


bool vote(char name[10]);
void print_winner(void);

int main (int argc,char* argv[10])
{
    //check if there are candidates and less then 9
    if (argc<2 || argc>10)  
    {
        printf("Invalid Number of Candidates");
        return 1;
    }
    //write the candidates name
    int h=1;
    while (h<argc)   
    {
        strcpy(candidates[h-1].name, argv[h]);
        h++;
    }
    //number of voters and candidates
    int n_voters;
    n_candidates=argc-1;
    printf("Number of Votes: ");
    scanf("%d", &n_voters);
    //get the votes
    int j=0;
    while (j<n_voters )
     {
        printf("Vote: ");
        char submitted[10];
        scanf("%s", &submitted);
        //vote function both cheks if the name is valid and adds the vote
        if (vote(submitted))
        {
            j++;
        }
        else
        {
            printf("Invalid \n");
        }
    }
    print_winner();
}


bool vote(char name[10])
{
    int h=0;
    for(int i=0; i<n_candidates; i++)
    {
        if (strcmp(name, candidates[i].name)==0)
        {
            candidates[i].votes=candidates[i].votes+1;
            return true;
        }
    }
    return false;
 }

void print_winner(void)
{
    // see what was the maximum number of votes
    int max_votes=0;
    for(int i=0;i<n_candidates; i++)
    {
        if (candidates[i].votes>max_votes)
        {
            max_votes=candidates[i].votes;
        }
    }
    //print the name of candidates that got the max of votes aka winner(s)
    for(int i=0;i<n_candidates; i++)
    {
        if (candidates[i].votes==max_votes)
        {
            printf("%s \n", candidates[i].name);
        }
    }
    
}
