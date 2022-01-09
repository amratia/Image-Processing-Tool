// AUC – ECNG 1502 – Fall 2020 - Assignment 4
// Program Name: Image Processing Tool.c
// Purpose: Manipulate images by applying filters
// Last Modification Date: 27/11/2020
// Author and ID: Amr M. Atia 900183833 / David Ayman 900181494
// David worked on tasks 2,4 and 6.
// Amr worked on tasks 3,5 and 7.

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmplib.h"

unsigned char image[SIZE][SIZE];

// The Headers of Functions used
void loadImage ();
void saveImage ();
void turnBW ();
void flipV ();
void flipH ();
void darken ();
void lighten ();
void invertImage();
void merge();
void shrink();
void edge();
//----------------------------------------------------------------------------
int main()
{
	// Defining the variable for user choice and welcome message
    char decision;
    printf("Hi welcome to photo editor. What would like to do?\n");
	printf("1- to turn an image to black and white, enter (b)\n");
    printf("2- to invert an image, enter (i)\n");
    printf("3- to darken an imgae, enter (d)\n"
	"4- to lighten an image, enter (l)\n");
    printf("5- to flip an image vertically enter (v)\n"
	"6- to flip an image horizontally, enter (h)\n");
    printf("7- to merge two images, enter (m)\n");
    printf("8- to shrink an image, enter (s)\n");
	printf("9- to detect the edges of an image, enter (t)\n");
	printf("10- to end the program, enter (e)\n");
    scanf("%c", &decision);

	// Calling functions based on the user input (Using nested if)

    if (decision == 'b')
    {
        loadImage();
        turnBW();
        saveImage();
    }
    else if (decision == 'i')
    {
        loadImage();
        invertImage();
        saveImage();
    }
    else if (decision == 'v')
    {
        loadImage();
        flipV();
        saveImage();
    }
    else if (decision == 'h')
    {
        loadImage();
        flipH();
        saveImage();
    }
    else if (decision == 'd')
    {
        loadImage();
        darken();
        saveImage();
    }
    else if (decision == 'l')
    {
        loadImage();
        lighten();
        saveImage();
    }
	else if (decision == 'm')
    {
        merge();
    }
    else if (decision == 's')
    {
        loadImage();
        shrink();
        saveImage();
    }
	else if (decision == 't')
    {
        loadImage();
        edge();
        saveImage();
    }
	else if (decision == 'e')
    	return 0;

	// Showing an error message when the user has chosen a wrong option
	else
		printf("Invalid Input");
}
//----------------------------------------------------------------------------
// Functions

void loadImage () {
	// Taking input image name from user and returning a 2D array
	char imageFileName[100];

    printf ("Enter the name of the image you want to modify: ");
    scanf ("%s", imageFileName);

    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
//----------------------------------------------------------------------------
void saveImage () {
	// Taking a 2D array
	// and storing it as an image with the name chosen by user
    char imageFileName[100];

    printf ("Enter the name of the image you have created: ");
    scanf ("%s", imageFileName);

    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
//----------------------------------------------------------------------------
void turnBW(){
	// Turn the pixel white if it is more than 255
	// Turn the pixel black if it is less than 255
    for (int i = 0; i < SIZE; i++)
        {
        for (int j = 0; j< SIZE; j++)
        {
            if (image[i][j] > 255/2)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
//----------------------------------------------------------------------------
void invertImage(){
	// Getting the invert pixel by using (255 - pixel)
    int num;
        for (int i = 0; i < SIZE; i++)
        	for (int j = 0; j< SIZE; j++)
            	image[i][j] = 255 - image[i][j];
}
//----------------------------------------------------------------------------
void flipH (){
	// Definig two variables store 1 & 2 to store the value of pixel
	// give the value stored in the variable later to the pixel on the other side
    int store1, store2;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE/2; j++)
        {
            store1 = image[i][j];
            store2 = image[i][255-j];
            image[i][255-j] = store1;
            image[i][j] = store2;
        }
}
//----------------------------------------------------------------------------
void flipV()
{
    int store1, store2;
    for (int i = 0; i < SIZE/2; i++)
        for (int j = 0; j< SIZE; j++)
        {
            store1 = image[i][j];
            store2 = image[255-i][j];
            image[255-i][j] = store1;
            image[i][j] = store2;
        }
}
//----------------------------------------------------------------------------
void darken(){
	// to lessen the value of the pixel by amount entered by user
    int amount;
    printf("by how much?\n");
    scanf("%d", &amount);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++){
            if (image[i][j] > amount)
                image[i][j] -= amount;
            else
                image[i][j] = 0;

        }
}
//----------------------------------------------------------------------------
void lighten(){
	// to lessen the value of the pixel by amount entered by user
    int amount = 0;
    printf("by how much?\n");
    scanf("%d", &amount);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++){
            if (image[i][j] <= (255-amount))
                image[i][j] = image[i][j] + (amount);
            else
                image[i][j] = 255;
        }
}
//----------------------------------------------------------------------------
void merge(){
	// Merging two images by getting the average of pixels in the same position
	printf("For first image: \n");
	loadImage();
	int store[SIZE][SIZE];
	for (int i=0; i < SIZE ; i++)
		for(int j=0; j<SIZE; j++)
			store[i][j] = image[i][j];
	printf("For second image: \n");
	loadImage();
	for (int i=0; i < SIZE ; i++)
		for(int j=0; j<SIZE; j++)
			image[i][j] = (store[i][j]+image[i][j])/2;
	saveImage();

}
//----------------------------------------------------------------------------
void shrink(){
	// We start by getting the shrink factor from the user
	// if the factor is 2 then each four pixels in a square will be added up to one
	// we iterate in the for loop with (counter + shrinking factor)
	int scale, k=0, l=0;
	printf("Shrink to what scale?\n"
	"Enter (2) for 1/2\nEnter (3) for 1/3\nEnter (4) for 1/4\n");
	scanf("%d",&scale);
	if (!((scale ==2)||(scale ==3)||(scale ==4))){
		printf("Ivalid input. Enter 1 for scale (1/2) \n"
		"or 2 for sclae (1/3) \nor 3 for scale (1/4)\n");
		scanf("%d",&scale);
	}
	int store[(SIZE/scale)+1][(SIZE/scale)+1];
    for(int i=0 ; i<SIZE ; i=i+scale){
		for(int j=0; j<SIZE ; j=j+scale){
			store[k][l] = image[i][j];
			l++;
		}
		k++;
		l=0;
	}
	// To overwrite the old picture
	for (int i=0; i < SIZE ; i++)
		for(int j=0; j< SIZE ; j++)
			image[i][j] = 0;
	// To write the new shrink picture
	for (int i=0; i < (SIZE/scale) ; i++)
		for(int j=0; j< (SIZE/scale) ; j++)
			image[i][j] = store[i][j];

}
//----------------------------------------------------------------------------
void edge(){
	// line by line, comparing each pixel to the one next to it
	// Horizontally and Virtically
	// if the difference in color is more than 40
	// then the pixle is considered a border
	for(int i=0; i < SIZE ; i++)
		for(int j=0; j< SIZE ; j++)
			if (((image[i][j] - image[i][j+1])>40)||((image[i][j] - image[i][j+1])<(-40)))
				image[i][j] = 0;
			else if (((image[i][j] - image[i+1][j])>40)||((image[i][j] - image[i+1][j])<(-40)))
				image[i][j] = 0;
			else
				image[i][j] = 255;
}
