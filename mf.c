#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>// for ceiling function
#include "caa2.c"
#include "qwerty.c"
#include "header.h"
//#include "nm2.c"

//#include "iaa.c"
FILE *fp;

void readFile();
void printDirectory();
void methodSelection();
void printStorage();
void printDirectory();
void initFreespace();
void initArray();

int blockSize, excessBlock, dirBlocks;
int anotherdirblock;

void main(){
   readFile();
   initArray();
   methodSelection();
}


void readFile(){

   char file_name[25];
   char *token;
   char buff[1024];

   printf("Please Enter your desired csv file\n");
   scanf("%s",&file_name);

   fp = fopen(file_name, "r"); 

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   while(fgets(buff,sizeof(buff),fp)){
      int j = 0;
      token = strtok(buff,",");
      strcpy(d[e].func,token);
      token = strtok(NULL,",");
      d[e].filename = atoi(token);
      token = strtok(NULL,",");
      while(token != NULL){   
         d[e].data[j]= atoi(token);
         token = strtok(NULL,",");
         j++;
         
      }
      e++;
      
   } 
   fclose(fp);
}

void methodSelection(){
    int method_choice;
      printf("\nPlease select allocation method: 1. contiguous 2. linked 3. indexed 4. New Method");
		scanf("%d", &method_choice);
      switch(method_choice)
		{
			case 1:
            printf("inside first method");
            // call method contigous
            printDirectory();
            checkFunc();
            printDirectory();
            break;
			case 2:
            printDirectory();
            checkFuncLink();
            printDirectory();

   // call method linked
            break;
         case 3:
            printDirectory();
            // call method indexedB
            break;
         case 4:
         // call method new method
            printDirectory();
            //checkFuncNM();
             printDirectory();
            break;

         default:
            printf("Unable to understand your input");
            break;
      }
}

void initArray(){
   int choice;
   do{
      printf("\nPlease select an option: (1)BlockSize (2)No. of Blocks ");
		scanf("%d", &choice);
      
		switch(choice)
		{
			case 1:
            printf("Enter block size between(2-43): ");
	         scanf("%d", &blockSize); 
            excessBlock = 130%blockSize;
            dirBlocks = (130-excessBlock)/blockSize;
            break;
			case 2:
			   printf("Enter the amount of block you want:");
            scanf("%d", &anotherdirblock);
            excessBlock = 130%anotherdirblock;
            blockSize =(130-excessBlock)/anotherdirblock;
            break;
         default:
            printf("Reached Default");
            break;
      }
      if(blockSize<2 || blockSize > 43){
         count1 = 0;
      }else if(anotherdirblock < 2 || anotherdirblock > 43){
         count1 = 0;
      }else{
         count1 = 1;
      }
      
   }while(count1 = 0);
      int temp[MAX]; 
	   int counter = 0;
      int blockNum = 0;

      if(choice == 1)
      {
         for(int a = 0; a<MAX;a++)\
         {
            counter = counter + 1;
            temp[a] = blockNum;
            if(counter == blockSize)
            {
               counter = 0;
               blockNum = blockNum +1;
            }
         }
      }else if(choice == 2)
      {
         
         blockSize = MAX/anotherdirblock;
         for(int a = 0; a<MAX;a++)
         {
            counter = counter + 1;
            temp[a] = blockNum;
            if(counter == blockSize)
            {
			      counter = 0;
			      blockNum = blockNum +1;
		      }
         }
      }
      
      for(int i = 0;i < MAX; i++){
		   indexf[i] = i;
		   block[i] = temp[i];
		   dataf[i] = -1;
         startLoc[i] = -1;
         endLoc[i] = -1;
	   }
      for(int i = 0; i < blockNum; i++){
         bitmap[i]=1;
      }
      if(choice==1)
      {
         if(excessBlock > 0)
         {
            noOfBlock = dirBlocks -1;
            printf("%d",noOfBlock);
         }
         else
         {
            noOfBlock = dirBlocks;    
         }
      }
      else if (choice ==2)
      {
         if(excessBlock > 0)
         {
            noOfBlock = anotherdirblock -1;
         }
         else
         {
            noOfBlock = dirBlocks;
         }
      }
      printf("Total Num of Blocks: %d",noOfBlock);
}

void printDirectory(){
   temp3 = noOfBlock; 
   while(temp3 > (temp2 * blockSize)){
      temp3 -= 1;
      temp2 += 1;
   }
   printf("*-------------Directory Section--------------*");
	printf("\n|  Index    Block    FileData   Start    End\n"); 
	for(int i = 0;i < (temp2 * blockSize); i++){
   
      	printf("|   %d         %d         %d         %d       %d |\n",indexf[i],block[i],dataf[i],startLoc[i],endLoc[i]);
 
   }
   printf("*----------------------------------------------*\n");
   printStorage();
}


void printStorage(){

   printf("*---------------Storage Section----------------*");
   printf("\n|  Index    Block    Entry\n");
	for(int i = (temp2 * blockSize);i < MAX; i++){
      	printf("|   %d         %d         %d                    |\n",indexf[i],block[i],dataf[i]);
   }
   printf("*-----------------------------------------------*\n");
   
   noOfBlock = noOfBlock-temp2;
   initFreespace();
}

void initFreespace(){
   for(int i = 0; i < noOfBlock; i++){
      bitmap[i] = 1;
   }
}

