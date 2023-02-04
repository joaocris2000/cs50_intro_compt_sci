#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_candidates 9
#define MAX_voters 9

//structs
typedef struct 
{
    char name[10];
    int votes;
    bool eliminated; //standard is false which means it is NOT eliminated
}
candidate;

//global variables
candidate candidates[MAX_candidates];
int n_candidates;
int n_voters;
int n_candidates_still_on;
char preference[10][MAX_voters][MAX_candidates];

//functions
bool vote(int voter);
void tabulate(void);
bool print_winner(void);
int find_min(void);
void eliminated(int min);
bool is_tie(void);


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
    n_candidates=argc-1;
    n_candidates_still_on=argc-1;
    printf("Number of Voter: ");
    scanf("%d", &n_voters);
    //get the votes
    int j=0;
    while (j<n_voters )
     {
        if (vote(j))
        {
            j++;
        }
        else
        {
            return false;
        }
    }
    while(true)
    {
        tabulate(); //tabe the results
        if(n_candidates_still_on!=2)
        {   if (print_winner()) //if majority print the winner
            {
                break;
            }
            else
            {
                int min;
                min=find_min();
                eliminated(min);
            }
        }
        else
        {
            if(is_tie())  //also checks if it is 
            {
                break;
            }
            else
            {
                int min;
                min=find_min();
                eliminated(min);
            }
        }
    }
    return 0;
}


bool vote(int voter)
{   
    printf("\n");
    char name[10];
    for(int rank=0; rank<n_candidates; rank++)
    {
        printf("Rank %i: ", rank+1);
        scanf("%s", &name);
        int h=0;
        for(int i=0; i<n_candidates; i++)//check if the name of the candidate existes
        {
            if (strcmp(name, candidates[i].name)==0) 
            {
                h=1;
            }   
        }
        if(h==1)
        {
            strcpy(preference[voter][rank], name);
        }
        else
        {
            return false;
        }
    }
    return true;
}

void tabulate(void)
{
    //set all to zero
    for(int i=0; i<n_candidates;i++)
    {
        candidates[i].votes=0;
    }
    //for each voter we add the vote of the first not eliminated candidate on the rank
    for(int voter=0; voter<n_voters; voter++)
    {
        int rank=0;
        while (rank<n_candidates)
        {
            char name[10];
            strcpy(name,preference[voter][rank]);
            for(int i=0; i<n_candidates; i++)
            {
                
                if (strcmp(name, candidates[i].name)==0 && !candidates[i].eliminated) 
                {
                    candidates[i].votes++;
                    i=100; //huge value to gets of while loop
                }
                  
            }
            rank++;
        }
    }
}

bool print_winner(void)
{
    // see what was the maximum number of votes
    int max_votes=0, winner=-1;
    for(int i=0;i<n_candidates; i++)
    {
        if (candidates[i].votes>max_votes)
        {
            max_votes=candidates[i].votes;
            winner=i;
        }
    }
    //if the max votes is a majority, it prints the winner
    if(max_votes>n_voters/2)
    {
        printf("%s", candidates[winner].name);
        return true;
    }
    else
    {
        return false;
    }
}

int find_min(void)
{
    int min_votes=100; //a impossibly big number so it initiates the for loop
    for(int i=0;i<n_candidates; i++)
    {
        if (candidates[i].votes<min_votes && !candidates[i].eliminated)
        {
            min_votes=candidates[i].votes;
        }
    }
    return min_votes;
}

void eliminated(int min)
{
    for(int i=0;i<n_candidates; i++)
    {
        if (candidates[i].votes==min && !candidates[i].eliminated)
        {
            candidates[i].eliminated=true;
            n_candidates_still_on=n_candidates_still_on-1;
        }
    }
}

bool is_tie(void)
{
    int u=0;
    for(int i=0;i<n_candidates; i++)
    {
        if (!candidates[i].eliminated)  //still in the election
        {
            if(candidates[i].votes=(n_voters/2))
            {
                printf("%s\n", candidates[i].name);
                u++;
            }
        }
    }
    if(u==2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
