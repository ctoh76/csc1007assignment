#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>// for ceiling function
#include "header.h"
#define MAX 130//define max size of data able to store




int freespaceIndex();
void addIndexM();
void readIndex();
void deleteIndex();
int checkFuncIndex();


int pos = 0,blockAvail,indexCounter = 0,deleteCount=0;//dk which nvr used need to clear it when i make the code look pretty
int store[MAX]={0};//here de all got used  
int  excessBlock, dirBlocks,k;//excess and dir block havent used need rmb to make it remove redudant blocks but if no time do jiu suan le
int choice,anotherdirblock , count1;


//WC:
//VCB is to contains information of the disk
//It should store total no of block, no of used block, no of freed block and bitmap
//VCB should always take up the dataf[0] slot then directory will start from dataf[1]
//So your VCB is a string. To properly store it, should use a #define delimiter
//E.g ("%d%s%d%s%d%s", noOfBlock, delimiter, noOfUsedBlock, delimiter, noOfFreeBlock, delimiter, bitmap)



int checkFuncIndex()
{ 
   for (int c = 0; c < e; c++)
   {                              
      char *function = d[c].func;
      switch (*function)
      {
      case 'a':
      case 'A':
         printf("Reached add Func"); //1
         addIndexM(c);
         break;
      case 'r':
      case 'R':
         printf("\nEntered Read Function\n");
         readIndex(c);
         break;
      case 'd':
      case 'D':
         printf("\nEntered Delete Function\n");
         deleteIndex(c);
         break;
      }
   }

   return 0;
}
void addIndexM(int index){
   int *ptr = d[index].data; //get the length of file data in the struct which stored in readfile()
   int size = 0;//, indexed=1;
      while(*ptr !=0){
         *ptr++;
         size++;//eg. if file is 100 data is 101-106 size or filelength is 6
   }
   if (size % blockSize == 0) {//calculate total number of blks required the file
        blocksRequired = size / blockSize + 1;
   } else {
        blocksRequired = size / blockSize + 2;
   }
   //printf("Block required = %d",blocksRequired);

   if(freespaceIndex())   //check for free space
      printf("\nNot allocated due to full storage");
   else{
     
         int startIndex = 0, counter = 0, temp = 0;
         startIndex = (freed[0] + temp2) * blockSize;
         printf("\nAdding file%d and found free ",d[index].filename);

         for(int c = 0; c <blockSize;c++){   //just for printing
            if(freed[c+1]==0)
            break;
            else
            printf("B%d  ",freed[c+1]+temp2);
         }

         for (int a = 0; a < blockSize; a++) {
            
            bitmap[freed[a]] = 0;
            if (freed[a + 1] == 0) {
               break;
            }
            
            dataf[startIndex++] = freed[a + 1] + temp2;
            counter = (freed[a + 1] + temp2) * blockSize;
            printf("\nAdded file%d at B%d ( ",d[index].filename,freed[a+1]+temp2);
            for (int b = 0; b < blockSize; b++) {
               if (d[index].data[temp] == 0) {
                  break;
               }
               printf("%d ",d[index].data[temp]);
               dataf[counter++] = d[index].data[temp++];
            }
            printf(")");
         }
      }
      //update Directory structure
      dataf[DirCount] = d[index].filename; 
      startLoc[DirCount] = freed[0] + temp2;
      endLoc[DirCount] = freed[0] + temp2;
      DirCount++;
}

void readIndex(int index){
   int *ptr = d[index].data; //get the length of file data inthe struct which stored in readfile()
   int size = 0, timesToRun =0, entry = 0, blkCounter = 0, blk = 0;//, indexed=1;
   int checkFileName = d[index].filename-(d[index].filename%100), mod =0;
      while(*ptr !=0){
         *ptr++;
         size++;//eg. if file is 100 data is 101-106 size or filelength is 6
   }
   //For reading of data, we do not know if we are reading file name or file data. Hence we need to calculate.
   //file name mod 100, if result is 0 means file name, if its not 0 means its file data
   mod = d[index].filename%100;
   if (mod ==0){     //if mod is 0, means it's reading file name
   //Read file 
      for(int i = 0; i < temp2*blockSize; i++){ //loop directory 
      if (dataf[i] == d[index].filename) {   //if data is same as filename in directory
         entry = startLoc[i];                //save start location to entry
         //printf("\nRead file %d\n",d[index].filename);  //print data that matches
         for(int j = 0; j<blockSize ;j++){      //first for loop is to index block
            if(dataf[entry*blockSize] ==  -1){      //break if data in index block = -1
            //printf("break fufilled");
            break;
            }
            else{ 
            blk= dataf[entry*blockSize+j];            //We need to get the storage block from the index block
            for(k = 0;k < blockSize; k++){
                  if(dataf[blk*blockSize+k] == 0 || dataf[blk*blockSize+k] == -1 )
                     break;
                  else
                     printf("%d...",dataf[blk*blockSize+k]);
                  }
               }
            }  
         }  
      }
   }
   else{
   //Read data, will print index block, data block
   for(int i = 0; i< temp2*blockSize; i++){ 
   if (checkFileName == dataf[i]){
         entry = startLoc[i];
         for(int j = 0; j<blockSize ;j++){      //first for loop is to index block
            if(dataf[entry*blockSize] ==  -1 || dataf[entry*blockSize] ==  0){      //break if data in index block = -1 or 0
            break;
            }
            else{ 
            blk= dataf[entry*blockSize+j];            //We need to get the storage block from the index block
            for(k = 0;k < blockSize; k++){
                  if(dataf[blk*blockSize+k] == d[index].filename )
                     printf("\nRead file%d(%d) in block %d , index block is block %d.",dataf[i],dataf[blk*blockSize+k],dataf[entry*blockSize+j],entry); 
                     //Read filename(data) in block # , index block is #
                  }
               }  
            }
         }
      }
   }
}
void deleteIndex(int index){
 int *ptr = d[index].data; //get the length of file data inthe struct which stored in readfile()
   int size = 0, counter=0 , timesToRun =0;//, indexed=1;
      while(*ptr !=0){
         *ptr++;
         size++;//eg. if file is 100 data is 101-106 size or filelength is 6
   }
   int entry = 0, blkCounter = 0, blk = 0;
   for(int i = 0; i < temp2*blockSize; i++){
      if (dataf[i] == d[index].filename) {
         printf("\nDelete file%d and freed indexB%d( ",dataf[i],startLoc[i]); 
         entry = startLoc[i];
         dataf[i] = -1;
         startLoc[i] = -1;
         endLoc[i] = -1;  
         break;
      }    
   }
   bitmap[entry - temp2] = 1;
   blkCounter = entry * blockSize;

   for (int a = 0; a < blockSize; a++) {
      bitmap[dataf[blkCounter] - temp2] = 1;
      blk = dataf[blkCounter] * blockSize;
      printf("B%d ",dataf[blkCounter]);
      dataf[blkCounter] = -1;
      
      for (int b = 0; b < blockSize; b++) {
         dataf[blk++] = -1;
      }

      blkCounter++;
      if (dataf[blkCounter] == -1) {
         break;
      }
   }
   printf(")");
}




int ifFullIndex(){
   int counter = 0;//counter
   for(int i = 0; i < noOfBlock; i++){//run the whole block eg. if block size 2, total storage block got 43(B22 - B64)
      if(bitmap[i] == 0){//checks eg. if block size 2, B22 - B64 is all 0s 0= used, 1=free to use
         counter++;//increment per 0 in bitmap
      }
   }

   if(counter>=noOfBlock){ //if counter bigger than or equal to total storage block(43) means fully used
      return 1; //return 1 or true
   }else{
      return 0; //return 0 or false
   }
}

int freespaceIndex(){///##TO EDIT CUZ DIFF ALLOCATION DIFF WAYS
   int count = 0,bitCount=0;//counter
   if(ifFullIndex()){//run ifFull
      return 1;//if ifFull() is full le return 1 or true to add func
   }
   else{
      memset(freed, 0, sizeof(freed));
      for(int i = 0; i < noOfBlock; i++){//scan the noOfblocks in the storage structure(basically 43)B22- B64
         //# for some cases where like if data input is 5 cuz its contiguous alloc so need ceiling it ceil(5/2) = 3
         //eg. if count(0) less than blocksRequired(3) and bitmap of block 0 is free to use, freed[0] = block no(i)
           if(count < blocksRequired){
              if(bitmap[i]==0){
                  //printf("\nBlock %d is used",i);
               }
               else{
                     freed[count] = i;//freed[count] stores the blockno its currently adding for example freed[0] = 4, 5 or 6
                     count++;
               }
         }
      }
   }
  // printf(" found free ");
 for(int i =0; i < blocksRequired+1; i++){
      store[i]=0;
   }
   for(int i = 0; i < blocksRequired; i++){//if found 3 space for blockrequired(3)
        // printf("-B%d-",freed[i]+temp2);//print which block is free
         store[i]=freed[i];
         //printf("Store[i] = %d",store[i]);
      }
      printf("\n");
      return 0;//then return 0 or false # i might have messed up whether 0 is true or false but basically return it to the add function


//gets its file name which is 200 just to cfm de la then get its startLoc and endLoc which is like 25 and 27
}