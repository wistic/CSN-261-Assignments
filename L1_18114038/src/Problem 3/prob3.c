/**
* @file prob3.c
* @brief This C file is program for manipulating the RGB values 
		of an image.
*
* @author Prathamesh Katkar
*
* @date 31/07/2019
*/
#include <stdio.h>
#include <stdlib.h>
/**
* This struct represents a pixel.
* @date 31/7/2019
*/
struct Pixel
{
  int red;
  int blue;
  int green;
};

/**
* This method imageSize() will be used to width and height of image in terms of pixels.
* @param none
* @date 31/07/2019
*/
 int* imageSize(){
  system("touch storage");
  int out=system("wc -l ../../Resources/Q3_ip_Red.dat >> storage"); //executed bash command to find number of lines in file
  int out1=system("wc -l ../../Resources/Q3_ip_Green.dat >> storage");
  int out2=system("wc -l ../../Resources/Q3_ip_Blue.dat >> storage");
  int out4=system("wc -L ../../Resources/Q3_ip_Red.dat >> storage"); //executed bash command to find maximum number of characters in a line
  int out5=system("wc -L ../../Resources/Q3_ip_Green.dat >> storage");
  int out6=system("wc -L ../../Resources/Q3_ip_Blue.dat >> storage");
  if ((out!=0) || (out2!=0) || (out2!=0) || (out4!=0) || (out5!=0) || (out6=0))
  {
    printf("Error reading the data files.\n");
    return NULL;
  }
  FILE* fp=fopen("storage","r");
  if(fp==NULL){
    printf("Storage file not generated.\n");
    return NULL;
  }
  int x1,x2,x3,y1,y2,y3;
  fscanf(fp,"%d %*s\n",&x1); //Scanning the output of bash commands from the file storage
  fscanf(fp,"%d %*s\n",&x2);
  fscanf(fp,"%d %*s\n",&x3);
  fscanf(fp,"%d %*s\n",&y1);
  fscanf(fp,"%d %*s\n",&y2);
  fscanf(fp,"%d %*s\n",&y3);
  if ((x1!=x2) || (x2!=x3) || (x1!=x3) || (y1!=y2) || (y2!=y3) || (y1!=y3))
  {
    printf("Data files corrupted.\n");
    return NULL;
  }
  static int maxvalues[2];
  maxvalues[0]=x1;
  maxvalues[1]=(y1+1)/4; //No of values*3 + No of commas = Maximum length of line  [No of commas=No of values-1]
  system("rm storage");
  return maxvalues;
 }
/**
* This method loadData() will be used to load the image data in the given array.
* @param int[][][] array, int height,int width
* @date 31/07/2019
*/
 void loadData(struct Pixel *rgb,int max_x,int max_y){
  FILE* fp_red=fopen("../../Resources/Q3_ip_Red.dat","r"); //loading file into file pointers
  FILE* fp_green=fopen("../../Resources/Q3_ip_Green.dat","r");
  FILE* fp_blue=fopen("../../Resources/Q3_ip_Blue.dat","r");
  if ((fp_red==NULL) || (fp_green==NULL) || (fp_blue==NULL))
  {
    printf("Error opening the data files.\n");
    return;
  }
  
  if (rgb==NULL){
    printf("Array not received.\n");
    return;
  }
  for (int x=0;x<max_x;x++){
    for (int y=0;y<max_y-1;y++){
      fscanf(fp_red,"%d,",&rgb[x+y*max_x].red);
      fscanf(fp_green,"%d,",&rgb[x+y*max_x].green);
      fscanf(fp_blue,"%d,",&rgb[x+y*max_x].blue);
    }
    fscanf(fp_red,"%d\n",&rgb[x+(max_y-1)*max_x].red);
    fscanf(fp_green,"%d\n",&rgb[x+(max_y-1)*max_x].green);
    fscanf(fp_blue,"%d\n",&rgb[x+(max_y-1)*max_x].blue);
  }
  fclose(fp_red); //Closing the file pointers
  fclose(fp_green);
  fclose(fp_blue);
 }

/**
* This method pixelValue() will be used to print the RGB values of a given pixel.
* @param int[][][] array,int x_coordinate, int y_coordinate, int height,int width
* @date 31/07/2019
*/
  void pixelValue(struct Pixel*rgb, int x,int y,int max_x,int max_y){
  if ((x<=max_x) && (y<=max_y))
    printf("RGB values are as follows:\nRED=%d\nGREEN=%d\nBLUE=%d\n", rgb[x+y*max_x].red,rgb[x+y*max_x].green,rgb[x+y*max_x].blue);
  else
    printf("Enter genuine coordinates for the pixel.\n");

 }
/**
* This method removeRed() will be used to remove all the Red shades in the image.
* @param int[][][] array, int height,int width
* @date 31/07/2019
*/
 void removeRed(struct Pixel*rgb,int max_x,int max_y){
  for (int x=0;x<max_x;x++){
    for (int y=0;y<max_y;y++){
      if (rgb[x+y*max_x].red>rgb[x+y*max_x].green)
      {
        if (rgb[x+y*max_x].red>rgb[x+y*max_x].blue)
        {
          rgb[x+y*max_x].red=0;
        }
      }
    }
  }
 }
/**
* This method removeGreen() will be used to remove all the Green shades in the image.
* @param int[][][] array, int height,int width
* @date 31/07/2019
*/
 void removeGreen(struct Pixel*rgb,int max_x,int max_y){
  for (int x=0;x<max_x;x++){
    for (int y=0;y<max_y;y++){
      if (rgb[x+y*max_x].green>rgb[x+y*max_x].red)
      {
        if (rgb[x+y*max_x].green>rgb[x+y*max_x].blue)
        {
          rgb[x+y*max_x].green=0;
        }
      }
    }
  }
 }
/**
* This method removeBlue() will be used to remove all the Blue shades in the image.
* @param int[][][] array, int height,int width
* @date 31/07/2019
*/
 void removeBlue(struct Pixel*rgb,int max_x,int max_y){
  for (int x=0;x<max_x;x++){
    for (int y=0;y<max_y;y++){
      if (rgb[x+y*max_x].blue>rgb[x+y*max_x].green)
      {
        if (rgb[x+y*max_x].blue>rgb[x+y*max_x].red)
        {
          rgb[x+y*max_x].blue=0;
        }
      }
    }
  }
 }
/**
* This method preserveRed() will be used to remove all the Blue and Green shades in the image.
* @param int[][][] array, int height,int width
* @date 31/07/2019
*/
 void preserveRed(struct Pixel*rgb,int max_x,int max_y){
  removeGreen(rgb,max_x,max_y);
  removeBlue(rgb,max_x,max_y);
 }
 /**
* This method preserveGreen() will be used to remove all the Blue and Red shades in the image.
* @param int[][][] array, int height,int width
* @date 31/07/2019
*/
 void preserveGreen(struct Pixel*rgb,int max_x,int max_y){
  removeRed(rgb,max_x,max_y);
  removeBlue(rgb,max_x,max_y);
 }
 /**
* This method preserveBlue() will be used to remove all the Red and Green shades in the image.
* @param int[][][] array, int height,int width
* @date 31/07/2019
*/
 void preserveBlue(struct Pixel*rgb,int max_x,int max_y){
  removeGreen(rgb,max_x,max_y);
  removeRed(rgb,max_x,max_y);
 }
 /**
* This method generateFile() will be used to generate the data file of the image.
* @param int[][][] array, int height,int width
* @date 31/07/2019
*/
 void generateFile(struct Pixel*rgb,int max_x,int max_y){
  system("touch ../../Generated_output_files/Q3_op_Red.dat");
  system("touch ../../Generated_output_files/Q3_op_Green.dat");
  system("touch ../../Generated_output_files/Q3_op_Blue.dat");
  FILE* ofp_red=fopen("../../Generated_output_files/Q3_op_Red.dat","w");
  FILE* ofp_green=fopen("../../Generated_output_files/Q3_op_Green.dat","w");
  FILE* ofp_blue=fopen("../../Generated_output_files/Q3_op_Blue.dat","w");
  if ((ofp_red==NULL) || (ofp_green==NULL) || (ofp_blue==NULL))
  {
    printf("Error creating the data files.\n");
    return;
  }
  else
  {
    for (int x=0;x<max_x;x++){
      for (int y=0;y<max_y-1;y++){
        fprintf(ofp_red,"%d,",rgb[x+y*max_x].red); // Printing integers to file
        fprintf(ofp_green,"%d,",rgb[x+y*max_x].green);
        fprintf(ofp_blue,"%d,",rgb[x+y*max_x].blue);
      }
      fprintf(ofp_red,"%d\n",rgb[x+(max_y-1)*max_x].red);
      fprintf(ofp_green,"%d\n",rgb[x+(max_y-1)*max_x].green);
      fprintf(ofp_blue,"%d\n",rgb[x+(max_y-1)*max_x].blue);
    }
  }
  fclose(ofp_red);
  fclose(ofp_green);
  fclose(ofp_blue);
 }
 int main(int argc, char const *argv[])
 {
 	//Driver Program
  int* maxvalues=(int *)imageSize();
  struct Pixel * rgb = malloc(sizeof(struct Pixel)*maxvalues[0]*maxvalues[1]);
  printf("Height of Image = %d\n", maxvalues[0]); //Prints height of image
  printf("Width of Image = %d\n", maxvalues[1]); //Prints width of image
  loadData(rgb,maxvalues[0],maxvalues[1]);
  preserveGreen(rgb,maxvalues[0],maxvalues[1]); //removing green shades
  pixelValue(rgb,320,650,maxvalues[0],maxvalues[1]);
  generateFile(rgb,maxvalues[0],maxvalues[1]); 
  return 0;
 }
