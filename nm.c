#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "header.h"

#define MAX 130 

int freespaceHMethod(int index);
void addMethod(int index);
void readHMethod();
void deleteHMethod();
int checkFuncNM();
void addIndex(int index);
int indexfreespace(int index);

int blocksRequired, blockAvail, indexRequiredBlock; 
int blockSize, excessBlock, dirBlocks, k;           
int choice, anotherdirblock;
int count1;
int blockSize, excessBlock, dirBlocks, k;
int readCount = 0;
int store[MAX];

int checkFuncNM()
{ 
   for (int c = 0; c < e; c++)
   {                              
      char *function = d[c].func;
      switch (*function)
      {
      case 'a':
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
      }
   }

   return 0;
}

void addMethod(int index)
{
   int *ptr = d[index].data; 
   int size = 0;
   while (*ptr != 0)
   {
      *ptr++;
      size++; 
   }
   double value = ceil((double)size / blockSize);                
   blocksRequired = value;                                       
   //indexRequiredBlock = ceil((double)blocksRequired / blockSize); 
   printf("\nAdding File %d and ", d[index].filename);          
   if (freespaceHMethod(index))
   {
      printf("Not allocated due to full Storage\n");
   }
   else
   {
         int k = 0;
         int q = (freed[0] + temp2) * blockSize;
         for (int i = q, k = 0; i < (q + size) && k < size; i++, k++)
         {
            dataf[i] = d[index].data[k];
            startLoc[i] = d[index].filename;
         }
         for (int i = 0; i < temp2 * blockSize; i++)
         {
            if (dataf[i] == -1)
            {
               dataf[i] = d[index].filename;
               startLoc[i] = freed[0] + temp2;
               endLoc[i] = freed[0] + temp2 + (value - 1);
               break;
            }
         }

         int l = 0;
         for (int j = 0; j < blocksRequired; j++)
         {
            l = freed[j];
            bitmap[l] = 0;
         }
   }
}
void addIndex(int index){
   int *ptr = d[index].data; 
   int size = 0;
   while (*ptr != 0)
   {
      *ptr++;
      size++; 
   }
      int count = 0;
      int count1 = 0;
      for (int k = 0; k < (blocksRequired); k++)
      {
         for (int i = ((freed[k] + temp2) * blockSize); i < (freed[k] + temp2) * blockSize + blockSize; i++)
         {
            if (k == 0 && count < blocksRequired)
            {
               dataf[i] = freed[count + 1] + temp2;
               printf("count %d,data: %d", count, dataf[i]);
               count++;
               
            }
            else
            {
               dataf[i] = -1;
            }
            if (k > 0 && count1 < size)
            {
               dataf[i] = d[index].data[count1];
               printf("c1 %d,data: %d", count1, dataf[i]);
               count1++;
               
            }
         }
      }
      for (int i = 0; i < temp2 * blockSize; i++)
      {
         if (dataf[i] == -1)
         {
            dataf[i] = d[index].filename;
            startLoc[i] = freed[0] + temp2;
            endLoc[i] = freed[blocksRequired-1] + temp2;
            break;
         }
      }

      int l = 0;
      for (int j = 0; j < blocksRequired; j++)
      {
         l = freed[j];
         bitmap[l] = 0;
         printf("blk %d is use", l + temp2);
      }
}

void readHMethod(int index)
{
   int size = 0;
   for (int c = 0; c < index; c++)
   {
      if (d[index].filename == d[c].filename)
      {
         for (int i = 0; i < temp2 * blockSize; i++)
         {
            if (d[index].filename == dataf[i])
            {
               int *ptr = d[c].data;
               while (*ptr != 0)
               {
                  *ptr++;
                  size++;
               }
            }
         }
      }
   }
   int t1 = 0, t2 = 0, t3 = 0,t4 = 1;
   for (int i = 0; i < temp2 * blockSize; i++)
   {
      if (d[index].filename == dataf[i])
      {
         t1 = dataf[i];
         t2 = startLoc[i];
         t3 = endLoc[i];
         break;
      }
   }
   printf("Data in %d",t1);
   for (int i = t2 * blockSize; i < (t2 * blockSize)+blockSize; i++)
   {
      if(dataf[i]>100){
         printf(".%d.",dataf[i]);
      }else{
         for(int k = dataf[i]*blockSize;k<dataf[i]*blockSize+blockSize;k++){
            printf("..%d..",dataf[k]);
         }
      }
   }



   // int *ptr = d[index].data;              
   // int size = 0, counter = 0, timesToRun = 0;
   // while (*ptr != 0)
   // {
   //    *ptr++;
   //    size++;
   // }
   // for (int i = 0; i < temp2 * blockSize - 1; i++)
   // { 
   //    if (dataf[i] == d[index].filename)
   //    { 
   //       timesToRun = endLoc[i] - startLoc[i] + 1;
   //       printf("----------Index block----------\n");
   //       printf("|  Index     Block      Entry  |\n");
   //       for (int k = 0; k < blockSize * timesToRun; k++)
   //       {
   //          if (dataf[readCount + blockSize * temp2] != -1)
   //          {
   //             printf("|   %d         %d         %d     |\n", indexf[blockSize * temp2 + readCount], block[blockSize * temp2 + readCount], dataf[blockSize * temp2 + readCount]);
   //          }
   //          readCount++;
   //       }
   //       printf("---------------------------------\n");
   //    }
   // }

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void deleteHMethod(int index)
{ //
   int size = 0;
   for (int c = 0; c < index; c++)
   {
      if (d[index].filename == d[c].filename)
      {
         for (int i = 0; i < temp2 * blockSize; i++)
         {
            if (d[index].filename == dataf[i])
            {
               int *ptr = d[c].data;
               while (*ptr != 0)
               {
                  *ptr++;
                  size++;
               }
            }
         }
      }
   }
   int t1 = 0, t2 = 0, t3 = 0;
   for (int i = 0; i < temp2 * blockSize; i++)
   {
      if (d[index].filename == dataf[i])
      {
         printf("File : %d \tStart: %d \tEnd: %d\n", dataf[i], startLoc[i], endLoc[i]);
         t1 = dataf[i];
         t2 = startLoc[i];
         t3 = endLoc[i];
         dataf[i] = -1;
         startLoc[i] = -1;
         endLoc[i] = -1;
         break;
      }
   }
   printf("Deleting:");
   for (int i = t2 * blockSize; i < (t2 * blockSize)+blockSize; i++)
   {
      if(dataf[i]>100){
         printf(".%d.",dataf[i]);
         dataf[i] = -1;
         startLoc[i] = -1;
         for(int j = t2;j<=t3; j++){
            bitmap[j] = 1;
         }
      }else{
         for(int k = dataf[i]*blockSize;k<dataf[i]*blockSize+blockSize;k++){
            printf("..%d..",dataf[k]);
            dataf[k] = -1;
            startLoc[k] = -1;
         }
         bitmap[k] = 1;
      }
   }
   
   // int checkIfV = 1;
   // int size = 0;
   // for (int c = 0; c < index; c++)
   // {
   //    if (d[index].filename == d[c].filename)
   //    {
   //       checkIfV = 0; // check if the data for value or not
   //       int *ptr = d[c].data;
   //       while (*ptr != 0)
   //       {
   //          checkIfV = 2;
   //          *ptr++;
   //          size++;
   //       }
   //    }
   // }
   // int t1 = 0, t2 = 0, t3 = 0, count = 0;
   // int t4[MAX];

   // for (int i = 0; i < temp2 * blockSize; i++)
   // { // get the value
   //    printf("filename %d \n", d[index].filename);
   //    if (d[index].filename == dataf[i])
   //    {
   //       printf("File : %d \tStart: %d \tEnd: %d\n", dataf[i], startLoc[i], endLoc[i]);
   //       t1 = dataf[i];
   //       t2 = startLoc[i];
   //       t3 = endLoc[i];

   //       dataf[i] = -1;
   //       startLoc[i] = -1;
   //       endLoc[i] = -1;
   //       break;
   //    }
   // }

   // int indexUsed = ((t3 - t2) + 1) * blockSize; // + 1 in order to count itself
   // printf("----------Index block be removed----------\n");
   // printf("|  Index     Block      Entry  |\n");
   // //printf("Print the indexUsed %d \n" , indexUsed);
   // for (int i = t2 * blockSize; i < (t2 * blockSize) + indexUsed; i++)
   // {
   //    if (dataf[i] != -1)
   //    {
   //       printf("|   %d         %d         %d     |\n", indexf[i], block[i], dataf[i]);
   //    }
   //    // printf(".%d.", dataf[i]);
   //    dataf[i] = -1;
   //    startLoc[i] = -1;
   // }
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
   else if (countbitmap1 < (blocksRequired))
   {
      return 1; //return 0 or false
   }
   else
   {
      return 0;
   }
}

int freespaceHMethod(int index)
{
   int count = 0; //counter
   if (ifFull())
   {            //run ifFull
      return 1; //if ifFull() is full le return 1 or true to add func
   }
   else
   { //if ifFull() is not full continue run
      
      if (blocksRequired == 0)
      {
         
         return 1;
      }
      else if (blocksRequired > noOfBlock)
      {
         
         return 1;
      }
      else
      {
         for (int i = 0; i < noOfBlock; i++)
         {
            if (count == blocksRequired)
            {
               printf("reached 5");
               break;
            }
            if (count < blocksRequired && bitmap[i] == 1)
            {
               
               freed[count] = i;
               count++;
               // totalavailspace ++;
            }
            else
            {
               printf("reached 7");
               for (int j = 0; j < blocksRequired; j++)
               {
                  freed[j] = 0;
               }
               count = 0;
            }
            if (i == noOfBlock - 1)
            {
               printf("Reach here");
               blocksRequired++;
               indexfreespace(index);
            }
            // else{totalavailspace >= blocksRequired}{
            //    indexfreespace();
            // }
            return 0;
         }
      }
   }
}

int indexfreespace(int index)
{
   int count = 0;
   for (int i = 0; i < blocksRequired + 1; i++)
   {
      freed[i] = 0;
   }
   for (int i = 0; i < noOfBlock; i++)
   { //scan the noOfblocks in the storage structure(basically 43)B22- B64//# for some cases where like if data input is 5 cuz its contiguous alloc so need ceiling it ceil(5/2) = 3
      if (count == blocksRequired)
      {
         addIndex(index);
      }
      if (count < blocksRequired && bitmap[i] == 1)
      {                    //eg. if count(0) less than blocksRequired(3) and bitmap of block 0 is free to use, freed[0] = block no(i)
         freed[count] = i; //freed[count] stores the blockno its currently adding for example freed[0] = 4, 5 or 6
         count++;
      }
   }
   printf(" found free ");
   for (int i = 0; i < blocksRequired; i++)
   {                                     //if found 3 space for blockrequired(3)
      printf("-B%d-", freed[i] + temp2); //print which block is free
   }
   printf("BitMap");
   for (int i = 0; i < noOfBlock; i++)
   {
      printf("%d", bitmap[i]);
   }
}

//    for (int i = 0; i < noOfBlock; i++)
//    { //scan the noOfblocks in the storage structure(basically 43)B22- B64//# for some cases where like if data input is 5 cuz its contiguous alloc so need ceiling it ceil(5/2) = 3
//       if (count == (blocksRequired + indexRequiredBlock))
//       {
//          break;
//       }
//       if (count < (blocksRequired + indexRequiredBlock) && bitmap[i] == 1)
//       {                    //eg. if count(0) less than blocksRequired(3) and bitmap of block 0 is free to use, freed[0] = block no(i)
//          freed[count] = i; //freed[count] stores the blockno its currently adding for example freed[0] = 4, 5 or 6
//                            //  printf("starting of freedcount %d , and i %d\n", freed[count], i);
//          count++;
//       }
//    }
//    printf(" found free ");
//    for (int i = 0; i < (blocksRequired + indexRequiredBlock); i++)
//    {                                     //if found 3 space for blockrequired(3)
//       printf("-B%d-", freed[i] + temp2); //print which block is free
//    }
//    printf("\n");
//    return 0; //then return 0 or false # i might have messed up whether 0 is true or false but basically return it to the add function
