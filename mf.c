#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>// for ceiling function
#include "caa2.c"
#include "header.h"
//#include "iaa.c"
FILE *fp;

void readFile();
void printDirectory();
void methodSelection();
void printStorage();
void printDirectory();

//int indexf[MAX], block[MAX], dataf[MAX],startLoc[MAX],endLoc[MAX] , bitmap[MAX], freed[MAX];
//int count1;


void main(){
   readFile();
   methodSelection();
}


void readFile(){//read csv and store everything into struct d[]

   char file_name[25];
   char *token;
   char buff[1024];

   printf("Please Enter your desired csv file\n");//get csv filename
   scanf("%s",&file_name);

   fp = fopen(file_name, "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");//if file does not exist
      exit(EXIT_FAILURE);
   }
   while(fgets(buff,sizeof(buff),fp)){//store file into d[].func d[].filename d[].data
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
   fclose(fp);//close the file
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
            initArray();
            printDirectory();
            checkFunc();
            printDirectory();
            break;
			case 2:
         initArray();
   // call method linked
            break;
         case 3:
         initArray();
            // call method indexed
            break;
         case 4:
         initArray();
         // call method new method
            break;

         default:
            printf("Unable to understand your input");
            break;
      }
}

void initArray(){//init array
int choice;
   do{
      printf("\nPlease select an option: ");
		scanf("%d", &choice);
      
		switch(choice)
		{
			case 1:
            printf("Enter block size between(2-43): ");
	         scanf("%d", &blockSize); 
            break;
			case 2:
			   printf("Enter the amount of block you want:");
            scanf("%d", &anotherdirblock);
            break;
         default:
            printf("Reached Default");//dk what to type in default should i even have a default here idk help me
            break;
      }
      if(blockSize<2 || blockSize > 43){
         count1 = 0;
      }else if(anotherdirblock < 2 || anotherdirblock > 43){
         count1 = 0;
      }else{
         count1 = 1;
      }
      
   }while(count1 =0);
   //why blocksize must be 2 to 43 is cuz when u calculate right per block we have we need an index to store the added block de start and end
   //so like if we put block size 1 we need like 130 index to fill in out file info into directory so means its impossible de so can only start from 2 as to why its until 43
   //cuz if we used 44 so we will have we only have 2 pathetic blocks of size 44 then funny thing is use gonna need to throw away 42 block space cuz redudant 
   //then 1 for directory 1 for storage which wont make sense uh u use such a big space of index 44
   //to store 1 goddamn file info... anw this can edit de if u got better de lets follow it!!!

      //excessBlock = 130%blockSize; dk how use this
	   //dirBlocks = (130-excessBlock)/blockSize; same for this dk how use
      int temp[MAX]; 
	   int counter = 0;
      int blockNum = 0;

      if(choice == 1)
      {
         for(int a = 0; a<MAX;a++)\
         {//get no. of blocks
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
         printf("dir:%d",anotherdirblock);
         blockSize = MAX/anotherdirblock;
         printf("bs: %d:",blockSize);
         for(int a = 0; a<MAX;a++)
         {//get no. of blocks
            counter = counter + 1;
            temp[a] = blockNum;
            if(counter == blockSize)
            {
			      counter = 0;
			      blockNum = blockNum +1;
		      }
         }
      }
      
      for(int i = 0;i < MAX; i++){//init the values and data/start/end to 0
		   indexf[i] = i;
		   block[i] = temp[i];
		   dataf[i] = 0;
         startLoc[i] = 0;
         endLoc[i] = 0;
	   }
      for(int i = 0; i < blockNum; i++){//init bitmap for freespace
         bitmap[i]=1;
      }
      noOfBlock = blockNum;//total block no.
}

void printDirectory(){//print directory
   temp3 = noOfBlock;
   while(temp3 > (temp2 * blockSize)){//this is the cool shit which calculate the blocksize for directory and blocksize for storage temp is directory end block,temp2 is storage start block
      temp3 -= 1;
      temp2 += 1;
   }
   printf("*-------------Directory Section--------------*");
	printf("\n|  Index    Block    FileData   Start    End\n"); 
	for(int i = 0;i < (temp2 * blockSize); i++){
   //   printf("why not running");
      	printf("|   %d         %d         %d         %d       %d |\n",indexf[i],block[i],dataf[i],startLoc[i],endLoc[i]);
 
   }
   printf("*----------------------------------------------*\n");
   printStorage();
}


void printStorage(){

   printf("*---------------Storage Section----------------*");
   printf("\n|  Index    Block    Entry\n");
	for(int i = (temp2 * blockSize);i < MAX; i++){// need include something to push up the list if i decide to add a new file in it will appear at the bottom uh...
      	printf("|   %d         %d         %d                    |\n",indexf[i],block[i],dataf[i]);//i add startLoc[] in this which reflects the start block of each file
   }
   printf("*-----------------------------------------------*\n");
   
   noOfBlock = noOfBlock-temp2;
   initFreespace(noOfBlock);
}

void initFreespace(){//initialize a freespace bitmap based of the total noofblocks available in storage structure 
   for(int i = 0; i < noOfBlock; i++){
      bitmap[i] = 1;//initiate all into 1 so that all is free (1 = free, 0 = used).
   }
}
