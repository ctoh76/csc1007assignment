#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>// for ceiling function
#include "header.h"
#define MAX 130//define max size of data able to store

int checkFuncLink();
int freespaceLink();
void addLink();
void readLink();
void deleteLink();

int blockAvail;//dk which nvr used need to clear it when i make the code look pretty
int blockSize, excessBlock, dirBlocks,k;//excess and dir block havent used need rmb to make it remove redudant blocks but if no time do jiu suan le
int choice,anotherdirblock ;
int count1;

int checkFuncLink(){//read csv and store everything into struct d[]

   /*for(int i = 0; i<5; i++){
      printf("Filename: %d\n",d[i].filename);
      printf("Data Func: %s\n",d[i].func);
      for(int k = 0;k < 6;k++){
         printf("data: %d\n",d[i].data[k]);
      }
   }*/
   for(int c= 0; c < e;c++){//interestingly enuf a readfile function i go put in here that after every func add, read or delete i go add immediately
     // printf("function  %s" , d[0].func);
    //  printf("why not running here ");
      char *function = d[c].func;//d[1].func
      switch(*function){
         case 'a'://read until character a or A means add la, r or R means read, d or D means delete
         case 'A':
            printf("Reached add Func");//1
            addLink(c);
            break;
         case 'r':
         case 'R':
            printf("\nEntered Read Function\n");
            //readLink(c);
            break;
         case 'd':
         case 'D':
            printf("\nEntered Delete Function\n");
            //deleteLink(c);
            break;
         default:
            printf("Reached Default");//dk what to type in default should i even have a default here idk help me
            break;
      } 
   }

   return 0;
}
void addLink(int index){
   int *ptr = d[index].data; //get the length of file data inthe struct which stored in readfile()
   int size = 0;
   while(*ptr !=0){
      *ptr++;
      size++;//eg. if file is 100 data is 101-106 size or filelength is 6
   }
   double value1 = ceil((double)size/(blockSize-1));
   blocksRequired = value1;
   printf("\nAdding File %d and",d[index].filename);//print filename
   int j = 0;
   if(freespaceLink()){//run freespace to check got space or not
      printf("Not allocated due to full Storage\n");
   }else{
      for(int i = freed[0]; i < (freed[0] + blocksRequired); i++){
         bitmap[i] = 0;
      }
      for(int i = 0; i< blocksRequired; i++){
         for(int k = ((freed[i] + temp2) * blockSize);k < (((freed[i] + temp2) * blockSize)+ blockSize); k++)
         {
            if(k == (((freed[i] + temp2) * blockSize)+ blockSize)-1){       
               dataf[k] = freed[i + 1] + temp2;
               if(dataf[k] == temp2){
                  dataf[k] = -1;
               }
               printf(".Index: %d. Data: %d ", k,dataf[k]);
            }
            else{
               if(j<=size){
                  dataf[k] = d[index].data[j];
                  printf(".Index: %d. Data: %d ", k,dataf[k]);
                  j++;
               } 
            }  
         } 
      } 
   }
}

int ifFullLink(){//runs thru the who block to check if bitmap[] reaches all 0 #for bitmap[] it stores a value of 0 or 1 to indicate each block in storage structure is used or not used
   int countbitmap = 0;//counter
   for(int i = 0; i < noOfBlock; i++){//run the whole block eg. if block size 2, total storage block got 43(B22 - B64)
      if(bitmap[i] == 0){//checks eg. if block size 2, B22 - B64 is all 0s 0= used, 1=free to use
         countbitmap++;//increment per 0 in bitmap
      }
   }
   if(countbitmap>=noOfBlock){ //if counter bigger than or equal to total storage block(43) means fully used
      return 1; //return 1 or true
   }else{
      return 0; //return 0 or false
   }
}
int freespaceLink(){

   int count = 0;//counter
   if(ifFullLink()){//run ifFull
      return 1;//if ifFull() is full le return 1 or true to add func
   }
   else{  //if ifFull() is not full continue run

      for(int i = 0; i < noOfBlock; i++){//scan the noOfblocks in the storage structure(basically 43)B22- B64//# for some cases where like if data input is 5 cuz its contiguous alloc so need ceiling it ceil(5/2) = 3
         if(count == blocksRequired){
            break;
         }
         if(count < blocksRequired && bitmap[i] == 1){//eg. if count(0) less than blocksRequired(3) and bitmap of block 0 is free to use, freed[0] = block no(i)
            freed[count] = i;//freed[count] stores the blockno its currently adding for example freed[0] = 4, 5 or 6
            count++;
         }
      }
      printf(" found free ");
      for(int i = 0; i < blocksRequired; i++){//if found 3 space for blockrequired(3)
         printf("-B%d-",freed[i]+temp2);//print which block is free
      }
      printf("BitMap");
      for(int i = 0; i < noOfBlock; i++){
         printf("%d",bitmap[i]);
      }
      printf("\n");
      return 0;//then return 0 or false # i might have messed up whether 0 is true or false but basically return it to the add function
   }
}