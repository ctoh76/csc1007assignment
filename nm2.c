#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // for ceiling function
#include "header.h"

#define MAX 130 //define max size of data able to store

int freespaceHMethod();
void addMethod();
void readHMethod();
void deleteHMethod();
int checkFuncNM();
void addHContigous(int index, int size);
void addIndex(int index, int size);

int blocksRequired, blockAvail, indexRequiredBlock; //dk which nvr used need to clear it when i make the code look pretty
int blockSize, excessBlock, dirBlocks, k;           //excess and dir block havent used need rmb to make it remove redudant blocks but if no time do jiu suan le
int choice, anotherdirblock;
int count1;
int blockSize, excessBlock, dirBlocks, k;

void addHContigous(int index, int size)
{
   double value = ceil((double)size / blockSize);                 // 6/2 = 3 or 6/5 = 2 cuz we actually need 2 blocks to store all 6 data uh
   blocksRequired = value;                                        //get amount of blocksrequired to place in storage structure.
   indexRequiredBlock = ceil((double)blocksRequired / blockSize); // calcutate how much block pointer need to use
   printf("\nAdding File %d and ", d[index].filename);            //print filename
   if (freespaceHMethod())
   { //run freespace to check got space or not
      printf("Not allocated due to full Storage\n");
   }
   else
   {

      for (int i = 0; i < noOfBlock; i++)
      {
         printf("freed is %d and i is %d\n", freed[i], i);
      }

      int countIndex = 0;
      int countStart = indexRequiredBlock * blockSize;
      int blockReset = 0;
      int k = 0;
      for (int j = 0; j < blocksRequired + indexRequiredBlock; j++)
      {
         for (int i = (freed[j] + temp2) * blockSize; i < (freed[j] + temp2) * blockSize + blockSize; i++)
         {
            if (countIndex < blocksRequired)
            {
               dataf[i] = freed[0] + temp2 + indexRequiredBlock + countIndex;
               blockReset++;
               bitmap[freed[j]] = 0;
               countStart--;
               countIndex++;
            }
            else
            {
               if (countIndex >= blocksRequired && countStart == 0)
               {
                  if (k < size)
                  {
                     dataf[i] = d[index].data[k];
                     startLoc[i] = d[index].filename; //fill the startblock for the file into it
                     bitmap[freed[j]] = 0;
                     k++;
                  }
               }
               else
               {
                  bitmap[freed[j]] = 0;
                  countStart--;
               }
            }
         }
      }

      //i swear go rmb what is temp2 cuz its everywhere so dumb for a temp int but i did this mess
      //temp2 is the starting block no. of the storage sturcture so if blocksize is 2 temp2 will be 22 if blocksize is 3 temp2 will be 11.
      if (c == temp2 * blockSize - 1)
      { //create a counter for directory struct so if counter reaches the max block of directory struct which is 21 means full le by right shouldnt reach here will be damn weird
         printf("Exceeded Directory allocated");
      }
      else
      {
         dataf[c] = d[index].filename;                                             //add per add file into directory struct
         startLoc[c] = freed[0] + temp2;                                           //add where it start into directory struct
         endLoc[c] = freed[0] + temp2 + (blocksRequired + indexRequiredBlock - 1); //add where it end into directory struct
         c++;
      }

      for (int i = 0; i < temp2; i++)
      {
         if (dataf[i] == -1 && startLoc[i] == -1 && endLoc[i] == -1)
         {
            for (int j = i; j < temp2; j++)
            {
               dataf[j] = dataf[j + 1];
               startLoc[j] = startLoc[j + 1];
               endLoc[j] = endLoc[j + 1];
            }
         }
      }
   }
}

int checkFuncNM()
{ //read csv and store everything into struct d[]
   for (int c = 0; c < e; c++)
   {                              //interestingly enuf a readfile function i go put in here that after every func add, read or delete i go add immediately
      char *function = d[c].func; //d[1].func
      switch (*function)
      {
      case 'a': //read until character a or A means add la, r or R means read, d or D means delete
      case 'A':
         printf("Reached add Func"); //1
         addMethod(c);
         break;
      case 'r':
      case 'R':
         printf("\nEntered Read Function\n");
         readHMethod(c);
         break;
      case 'd':
      case 'D':
         printf("\nEntered Delete Function\n");
         deleteHMethod(c);
         break;
      default:
         printf("Reached Default"); //dk what to type in default should i even have a default here idk help me
         break;
      }
   }

   return 0;
}

void addMethod(int index)
{
   int *ptr = d[index].data; //get the length of file data inthe struct which stored in readfile()
   int size = 0;
   while (*ptr != 0)
   {
      *ptr++;
      size++; //eg. if file is 100 data is 101-106 size or filelength is 6
   }
   addHContigous(index, size);
}

void readHMethod(int index)
{
   int fileNameYN = 0; // default means is it a file data

   int size = 0;
   for (int c = 0; c < index; c++)
   {
      if (d[index].filename == d[c].filename)
      {
         
         int *ptr = d[c].data;
         while (*ptr != 0)
         { //to count the size of data basically is like len(data)
            *ptr++;
            size++;
         }
      }
   }

  
   

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void deleteHMethod(int index)
{ //
   int size = 0;
   int iffileName = 0;
   int tempStart;
   for (int c = 0; c < index; c++)
   {
      if (d[index].filename == d[c].filename) //just to find the data's size
      {
         iffileName = 1;
         tempStart = d[index].filename;

         int *ptr = d[c].data;
         while (*ptr != 0)
         {
            *ptr++;
            size++;
         }
      }
   }

   //printf(" this is size %d\n" , size);
   int tempp = 0;
   int tempp1 = 0;
   int tempp2 = 0;

   for (int i = 0; i < temp2; i++)
   {
      if (tempStart == d[c].filename)
      {
         printf(" this is plus wtffffffffffffffffffffffffffffff %d\n", d[c].filename);
         for (int j = i; j < temp2; j++)
         {
            //   tempp = dataf[j];
            tempp1 = startLoc[j];
            tempp2 = endLoc[j];
            printf("tempp1  %d\n", tempp1);
            printf("temmp2 %d\n", tempp2);
         }
      }
   }
   // printf("data %d\n" , d[c].filename);

   /*
            for (int i = 0; i < temp2; i++)
      {
         if (dataf[i] == -1 && startLoc[i] == -1 && endLoc[i] == -1)
         {
            for (int j = i; j < temp2; j++)
            {
               dataf[j] = dataf[j + 1];
               startLoc[j] = startLoc[j + 1];
               endLoc[j] = endLoc[j + 1];
            }
         }
      }
*/
   /*

   if(iffileName == 1){
         tempStart = 0;
            int t1 = 0, t2 = 0,t3 = 0;
   for(int i = 0; i<temp2*blockSize; i++){
      if(d[index].filename == dataf[i]){//compare to find the file info in directory struct
         printf("File : %d Start: %d End: %d", dataf[i],startLoc[i],endLoc[i]);//start from where and end where
         t1 = dataf[i];//allocate into t1 to use
         t2 = startLoc[i];//allocate into t2 to use
         t3 = endLoc[i];//allocate into t3 to use
         dataf[i] = -1;//set it to -1 cuz its been "deleted"
         startLoc[i] = -1;//set it to -1 cuz its been "deleted"
         endLoc[i] = -1;//set it to -1 cuz its been "deleted"
      }
   }

   }else{
      
   }
*/
}

int ifFull()
{                       //runs thru the who block to check if bitmap[] reaches all 0 #for bitmap[] it stores a value of 0 or 1 to indicate each block in storage structure is used or not used
   int countbitmap = 0; //counter
   int countbitmap1 = noOfBlock;
   for (int i = 0; i < noOfBlock; i++)
   { //run the whole block eg. if block size 2, total storage block got 43(B22 - B64)
      if (bitmap[i] == 0)
      {                 //checks eg. if block size 2, B22 - B64 is all 0s 0= used, 1=free to use
         countbitmap++; //increment per 0 in bitmap
         countbitmap1--;
      }
   }
   if (countbitmap >= noOfBlock)
   {            //if counter bigger than or equal to total storage block(43) means fully used
      return 1; //return 1 or true
   }
   else if (countbitmap1 < (blocksRequired + indexRequiredBlock))
   {
      return 1; //return 0 or false
   }
   else
   {
      return 0;
   }
}

int freespaceHMethod()
{
   int count = 0; //counter
   if (ifFull())
   {            //run ifFull
      return 1; //if ifFull() is full le return 1 or true to add func
   }
   else
   { //if ifFull() is not full continue run

      for (int i = 0; i < noOfBlock; i++)
      { //scan the noOfblocks in the storage structure(basically 43)B22- B64//# for some cases where like if data input is 5 cuz its contiguous alloc so need ceiling it ceil(5/2) = 3
         if (count == (blocksRequired + indexRequiredBlock))
         {
            break;
         }
         if (count < (blocksRequired + indexRequiredBlock) && bitmap[i] == 1)
         {                    //eg. if count(0) less than blocksRequired(3) and bitmap of block 0 is free to use, freed[0] = block no(i)
            freed[count] = i; //freed[count] stores the blockno its currently adding for example freed[0] = 4, 5 or 6
            printf("starting of freedcount %d , and i %d\n", freed[count], i);
            count++;
         }
      }
      printf(" found free ");
      for (int i = 0; i < (blocksRequired + indexRequiredBlock); i++)
      {                                     //if found 3 space for blockrequired(3)
         printf("-B%d-", freed[i] + temp2); //print which block is free
      }
      printf("\n");
      return 0; //then return 0 or false # i might have messed up whether 0 is true or false but basically return it to the add function
   }
}
