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
int blockSize;
int excessBlock, dirBlocks,k;//excess and dir block havent used need rmb to make it remove redudant blocks but if no time do jiu suan le
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
            readLink(c);
            break;
         case 'd':
         case 'D':
            printf("\nEntered Delete Function\n");
            deleteLink(c);
            break;
         default:
            printf("Reached Default");//dk what to type in default should i even have a default here idk help me
            break;
      } 
   }

   return 0;
}
void addLink(int index){
   int count2;
   int *ptr = d[index].data; //get the data length of file data inthe struct which stored in readfile()
   int size = 0;
   while(*ptr !=0){
      *ptr++;
      size++;//eg. if file is 100 data is 101-106 size or filelength is 6
   }
   //get the blockSize
   double value1 = ceil((double)size/(blockSize-1));
   blocksRequired = value1;
   printf("\nAdding File %d and",d[index].filename);//print filename
   
   int j = 0;
   if(freespaceLink()){//run freespace to check got space or not
      printf("Not allocated due to full Storage\n");
   }else{
      for(int i = freed[0]; i < (freed[0] + blocksRequired); i++){  //if the i=freed[0]=0 ,i less than 0+2(block require),i++
         bitmap[i] = 0;//bitmap 0 =used
      }
      for(int i = 0; i < blocksRequired; i++){ 
         for(int k = ((freed[i]+temp2)*blockSize);k<(freed[i]+temp2)*blockSize + blockSize;k++){   //position freed[i]+temp=22*2=index 44,the first index,K is less than 44+2,46,K++   --> we know that we need 2 block each time for each data 
            if(k == (freed[i]+temp2)*blockSize + blockSize - 1){  //44=2=46-1 =45 index
               dataf[k] = (freed[i+1] + temp2);  //44 = 0+1+22 =23 ,index 45 store 23 ,Node
               if(dataf[k] == freed[i]+temp2){  //44 ==22
                  dataf[k] = -1;   
               }
            }else{
               dataf[k]=d[index].data[j]; //insert the data
               j++;
            }
         }
      }
if(c == temp2 * blockSize - 1){//create a counter for directory struct so if counter reaches the max block of directory struct which is 21 means full le by right shouldnt reach here will be damn weird
         printf("Exceeded Directory allocated");
      }else{
         dataf[c] = d[index].filename;//add per add file into directory struct
         startLoc[c] = freed[0] + temp2;//add where it start into directory struct
         endLoc[c] = freed[0] + temp2 + (value1 -1);//add where it end into directory struct
         c++;
      }

   }
}

int ifFullLink(){//runs thru the who block to check if bitmap[] reaches all 0 #for bitmap[] it stores a value of 0 or 1 to indicate each block in storage structure is used or not used
   int countbitmap = 0;//counter
   int countbitmap1 = noOfBlock;
   for(int i = 0; i < noOfBlock; i++){//run the whole block eg. if block size 2, total storage block got 43(B22 - B64)
      if(bitmap[i] == 0){//checks eg. if block size 2, B22 - B64 is all 0s 0= used, 1=free to use
         countbitmap++;//increment per 0 in bitmap
         countbitmap1--;
      }
   }
   if(countbitmap>=noOfBlock){ //if counter bigger than or equal to total storage block(43) means fully used
      return 1; //return 1 or true
   }else if(countbitmap1 < blocksRequired){
      return 1; //return 0 or false
   }else{
      return 0;
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


void readLink(int index){
   //as when we read file the data stored is based on the index so like d[0].filename = 100 cuz we add 100 first then d[1].filename = 200 cuz we add 200 next
   int size = 0;//so d[0].data is the data in d[0].filename which is 101-106, i basically count the length of it cuz idk why but i cant use sizeof 
   for(int c= 0; c < index;c++){//cuz read 200 which is d[i].filename = 200 got no data!!! so need to look back into the filename 200 containing the data
      if(d[index].filename == d[c].filename)//compare and find the damn size
      {
         int *ptr = d[c].data;
         while(*ptr !=0){//to count the size of data basically is like len(data)
            *ptr++;
            size++;
         }
      }
   }
   int t1 = 0, t2 = 0,t3 = 0,t4 = 0;//created 3 temp int to store the dataf[i] startLoc[i] endLoc[i]
   for(int i = 0; i<temp2*blockSize; i++){//this for loop run based on the directory structure cuz it runs from blk 0 to 21,lets say for blocksize 2 it runs from index 0 to index 43
      if(d[index].filename == dataf[i]){//if the filename from the struct which store the readfile meaning like read 200 filename is 200 compare with the directory structure to find 200
         printf("File : %d Start: %d End: %d", dataf[i],startLoc[i],endLoc[i]);//gets its file name which is 200 just to cfm de la then get its startLoc and endLoc which is like 25 and 27
         t1 = dataf[i];//filename
         t2 = startLoc[i];//if we  alr added 200 to block 25- block 27 and we read filename 200 should appear blk 25 
         t3 = endLoc[i]; // should appear block 27
         t4 = 1;
      }
   }
    for(int i = (temp2*blockSize); i<MAX; i++){//if user wanna find file data #for loop to run thru the storage struct
      if(d[index].filename == dataf[i]){//if filename = file data 
         printf("File : %d",startLoc[i]);
         t1 = dataf[i];//file data eg read 1401 t1 = 1401 t1=300 store the file name
         t2 = startLoc[i];//file start block t2 =39 start
         t3 = (i/blockSize);//file block location of the data t3 =44 end 
         t4 = 2;//condition t4 =1 
         
      }

   }
   if(t1 != d[index].filename){//just to say if nosuch file it will be 0
      printf("No such file as %d",d[index].filename);
   }else if(t4 == 1){
      printf("\nData in %d:",t1);//filename which should be 200 but will varies depend on what we read
   }else if(t4 == 2){
      printf("\nRead file %d(%d) from B%d",t2,t1,t3);
   }

   for(int i =t2*blockSize;i<((t2*blockSize)+(size*2));i++){//for loop from index(blk 22* blocksize 2 =44)i=44(start index),i<(44+6(length))50 i++ ,get the data in this range 
     printf("%.d.",dataf[i]);//print the data
   }
   printf("\n");
   for(int i = 0;i < temp2; i++){
         if(dataf[i] == -1 && startLoc[i] == -1 && endLoc[i] == -1){
            for(int j = i;j < temp2; j++){
               dataf[j] = dataf[j + 1];
               startLoc[j] = startLoc[j + 1];
               endLoc[j] = endLoc[j + 1];
            }

         }
          
      }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void deleteLink(int index){//
   int size = 0;
   for(int c= 0; c < index;c++){  
      if(d[index].filename == d[c].filename)//just to find the data's size
      {
         int *ptr = d[c].data;
         while(*ptr !=0){
            *ptr++;
            size++;
         }
      }
   }
   int t1 = 0, t2 = 0,t3 = 0;
   for(int i = 0; i<temp2*blockSize; i++){
      if(d[index].filename == dataf[i]){//compare to find the file info in directory struct
         printf("File : %d Start: %d End: %d", dataf[i],startLoc[i],endLoc[i]);//start from where and end where
         t1 = dataf[i];//allocate into t1 to use
         t2 = startLoc[i];//allocate into t2 to use
         t3 = endLoc[i];//allocate into t3 to use
         dataf[i] = -1;//set it to 0 cuz its been "deleted"
         startLoc[i] = -1;//set it to 0 cuz its been "deleted"
         endLoc[i] = -1;//set it to 0 cuz its been "deleted"
      }
   }
   printf("\nData in %d:",t1);
   for(int i = t2*blockSize;i< (t2*blockSize+size*2);i++){//set dataf[] inthe storage struct into 0 so can use //*2 because each 6 data need 12 block 
      printf(".%d.",dataf[i]);
      dataf[i] = -1;
      startLoc[i] = -1;
   }
   printf("Has been deleted");
   printf("\n");
   for(int i = t2 - temp2; i< t3-temp2; i++){//set bitmap back to 1 so its free but mainly is this bitmap cuz dataf nvr set 0 it oso can be overwrite
      bitmap[i] = 1;
   }

   for(int i = 0;i < temp2; i++){
         if(dataf[i] == -1 && startLoc[i] == -1 && endLoc[i] == -1){
            for(int j = i;j < temp2; j++){
               dataf[j] = dataf[j + 1];
               startLoc[j] = startLoc[j + 1];
               endLoc[j] = endLoc[j + 1];
            }
         }
      }
}