#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale 
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            //calculating the average number of the colors
            int average=round((image[j][i].rgbtBlue+image[j][i].rgbtGreen+image[j][i].rgbtRed)/3);
            //both colors need to have the same value so it's a shade o grey, between black(0,0,0) and white(255,255,255)
            image[j][i].rgbtBlue=average;
            image[j][i].rgbtGreen=average;
            image[j][i].rgbtRed=average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //for each line
    for(int j=0; j<height; j++)
    {
        RGBTRIPLE *temporary_line=malloc(3*sizeof(BYTE)*width);
        //copy the values to a temporary line, but in reversed order
        for(int i=0; i<width; i++)
        {
            temporary_line[i]=image[j][width-1-i];
        }
        //setting the values of the line to the reversed order
        for(int i=0; i<width; i++)
        {
            image[j][i]=temporary_line[i];
        }
        free(temporary_line);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //since its the av. of all nearby values, the pixel map can only be updated after all calcualtions
    //this is 1D but can be used as 2D if counted as j*height + i
    RGBTRIPLE *temporary_map = malloc(3*sizeof(BYTE)*width*height);
    int red, green, blue; 
    //for each line
    for(int j=0; j<height; j++)
    {
        //for each row
        for(int i=0; i<width; i++)
        {
            if(j==0 || i==0 || j==height-1 || i==width-1)
            //ignore the edges setting them as black
            {
                red=0;
                green=0;
                blue=0;
            }
            else
            {
                red=round((image[j-1][i-1].rgbtRed+image[j-1][i].rgbtRed+image[j-1][i+1].rgbtRed+image[j][i-1].rgbtRed+image[j][i].rgbtRed+image[j][i+1].rgbtRed+image[j+1][i-1].rgbtRed+image[j+1][i].rgbtRed+image[j+1][i+1].rgbtRed)/9);
                green=round((image[j-1][i-1].rgbtGreen+image[j-1][i].rgbtGreen+image[j-1][i+1].rgbtGreen+image[j][i-1].rgbtGreen+image[j][i].rgbtGreen+image[j][i+1].rgbtGreen+image[j+1][i-1].rgbtGreen+image[j+1][i].rgbtGreen+image[j+1][i+1].rgbtGreen)/9);
                blue=round((image[j-1][i-1].rgbtBlue+image[j-1][i].rgbtBlue+image[j-1][i+1].rgbtBlue+image[j][i-1].rgbtBlue+image[j][i].rgbtBlue+image[j][i+1].rgbtBlue+image[j+1][i-1].rgbtBlue+image[j+1][i].rgbtBlue+image[j+1][i+1].rgbtBlue)/9);
            }
            temporary_map[j*width +i].rgbtRed=red;
            temporary_map[j*width +i].rgbtGreen=green;
            temporary_map[j*width +i].rgbtBlue=blue;
            
        }
    }
    //updating the image bit map
    for(int j=0; j<height; j++)
    {
        for(int i=0; i<width; i++)
        {
            image[j][i]=temporary_map[j*width +i];
        }
    }
    free(temporary_map);
    return;    
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //since its a math with of all nearby values, the pixel map can only be updated after all calculations
    //this is 1D but can be used as 2D if counted as j*width + i
    RGBTRIPLE *temporary_map = malloc(3*sizeof(BYTE)*width*height);
    int gy_red, gx_red, g_red, gy_green, gx_green, g_green, gy_blue, gx_blue, g_blue; 
    //for each line
    for(int j=0; j<height; j++)
    {
        //for each row
        for(int i=0; i<width; i++)
        {
            if(j==0 || i==0 || j==height-1 || i==width-1)
            //ignore the edges setting them as black
            {
                g_red=0;
                g_green=0;
                g_blue=0;
            }
            else
            {
                gy_red=-1*image[j-1][i-1].rgbtRed-2*image[j-1][i].rgbtRed-1*image[j-1][i+1].rgbtRed+image[j+1][i-1].rgbtRed+2*image[j+1][i].rgbtRed+image[j+1][i+1].rgbtRed;
                gx_red=-1*image[j-1][i-1].rgbtRed+image[j-1][i+1].rgbtRed-2*image[j][i-1].rgbtRed+2*image[j][i+1].rgbtRed-image[j+1][i-1].rgbtRed+image[j+1][i+1].rgbtRed;
                if(gy_red<0)
                {
                    gy_red=0;
                }
                if(gx_red<0)
                {
                    gx_red=0;
                }
                g_red=round(sqrt(gy_red^2+gx_red^2));
                gy_green=-1*image[j-1][i-1].rgbtGreen-2*image[j-1][i].rgbtGreen-1*image[j-1][i+1].rgbtGreen+image[j+1][i-1].rgbtGreen+2*image[j+1][i].rgbtGreen+image[j+1][i+1].rgbtGreen;
                gx_green=-1*image[j-1][i-1].rgbtGreen+image[j-1][i+1].rgbtGreen-2*image[j][i-1].rgbtGreen+2*image[j][i+1].rgbtGreen-image[j+1][i-1].rgbtGreen+image[j+1][i+1].rgbtGreen;
                 if(gy_green<0)
                {
                    gy_green=0;
                }
                if(gx_green<0)
                {
                    gx_green=0;
                }
                g_green=round(sqrt(gy_green^2+gx_green^2));
                gy_blue=-1*image[j-1][i-1].rgbtBlue-2*image[j-1][i].rgbtBlue-1*image[j-1][i+1].rgbtBlue+image[j+1][i-1].rgbtBlue+2*image[j+1][i].rgbtBlue+image[j+1][i+1].rgbtBlue;
                gx_blue=-1*image[j-1][i-1].rgbtBlue+image[j-1][i+1].rgbtBlue-2*image[j][i-1].rgbtBlue+2*image[j][i+1].rgbtBlue-image[j+1][i-1].rgbtBlue+image[j+1][i+1].rgbtBlue;
                 if(gy_blue<0)
                {
                    gy_blue=0;
                }
                if(gx_blue<0)
                {
                    gx_blue=0;
                }
                g_blue=round(sqrt(gy_blue^2+gx_blue^2));
            }
            if(g_red>255)
            {
                g_red=255;
            }
            if(g_green>255)
            {
                g_green=255;
            }
            if(g_blue>255)
            {
                g_blue=255;
            }
            temporary_map[j*width +i].rgbtRed=g_red;
            temporary_map[j*width +i].rgbtGreen=g_green;
            temporary_map[j*width +i].rgbtBlue=g_blue;
            
        }
    }
    //updating the image bit map
    for(int j=0; j<height; j++)
    {
        for(int i=0; i<width; i++)
        {
            image[j][i]=temporary_map[j*width +i];
        }
    }
    free(temporary_map);
    return;
}
