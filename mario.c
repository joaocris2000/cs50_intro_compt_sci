#include<stdio.h>


int main (void)
{
    int n;
    do
    {
        printf("Size: ");
        scanf("%i", &n);
    }
    while(n<1);
    //for each row
    for (int i=1; i<=n; i++)
    {
        //for each column
        for(int k=0; k<(n-i);k++)
        {
            //print a brick
            printf(" ");
        } 
        for (int j=0; j<i; j++)
        {
            //print a brick
            printf("#");
        } 
        printf(" ");
        for (int j=0; j<i; j++)
        {
            //print a brick
            printf("#");
        } 
        printf("\n");
        }
   
}
