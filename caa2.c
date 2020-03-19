#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"
#define MAX 130

void addCont();
void readCont();
void deleteCont();
int checkFunc();
int freespaceCont();

int blockAvail;
int volumecontrol1[] = {0}; 
int volumecontrol2[] = {0}; 

int blockSize, excessBlock, dirBlocks,k;
int choice,anotherdirblock ;

int checkFunc(){

   for(int c= 0; c < e;c++){
      char *function = d[c].func;
      switch(*function){
         case 'a':
         case 'A':
            addCont(c);
            break;
         case 'r':
         case 'R':
            readCont(c);
            break;
         case 'd':
         case 'D':
            deleteCont(c);
            break;
         default:
            printf("Reached Default");
            break;
      } 
   }

   return 0;
}

void addCont(int index){
   int *ptr = d[index].data; 
   int size = 0;
   while(*ptr !=0){
      *ptr++;
      size++;
   }
   double value = ceil((double)size/blockSize);
   blocksRequired = value;
   printf("\nAdding File %d and",d[index].filename);
   if(freespaceCont()){
      printf("Not allocated due to full Storage\n");
   }else{  
      int k = 0;
      int q = (freed[0] + temp2) * blockSize;
      for(int i = q,k = 0;i <(q + size) && k<size;i++,k++){
         dataf[i] = d[index].data[k];
         startLoc[i] = d[index].filename;
      }
      // if(c == temp2 * blockSize - 1){
      //    printf("Exceeded Directory allocated");
      // }else{
      //    dataf[c] = d[index].filename;//add per add file into directory struct
      //    startLoc[c] = freed[0] + temp2;//add where it start into directory struct
      //    endLoc[c] = freed[0] + temp2 + (value -1);//add where it end into directory struct
      //    c++;
      // }
      for(int i = 0; i < temp2 * blockSize; i++){
         if(dataf[i] == -1) {
            dataf[i] = d[index].filename;
            startLoc[i] = freed[0] + temp2;
            endLoc[i] = freed[0] + temp2 + (value -1);
            break;
         }
      }

      int l = 0;
      for(int j = 0; j<blocksRequired; j++){
         l = freed[j];
         bitmap[l] = 0;
      }
      /*for(int i = 0;i < temp2; i++){
         if(dataf[i] == -1 && startLoc[i] == -1 && endLoc[i] == -1){
            for(int j = i;j < temp2; j++){
               dataf[j] = dataf[j + 1];
               startLoc[j] = startLoc[j + 1];
               endLoc[j] = endLoc[j + 1];
            }
         }
      }*/
   }
}

void readCont(int index){
   int size = 0;
   for(int c= 0; c < index;c++){
      if(d[index].filename == d[c].filename)
      {
         int *ptr = d[c].data;
         while(*ptr !=0){
            *ptr++;
            size++;
         }
      }
   }
   int t1 = 0, t2 = 0,t3 = 0,t4 = 0;
   for(int i = 0; i<temp2*blockSize; i++){
      if(d[index].filename == dataf[i]){
         printf("File : %d \tStart: %d \tEnd: %d", dataf[i],startLoc[i],endLoc[i]);
         t1 = dataf[i];
         t2 = startLoc[i]; 
         t3 = endLoc[i];
         t4 = 1;
      }
   }
   for(int i = (temp2*blockSize); i<(noOfBlock+temp2)*blockSize; i++){
      if(d[index].filename == dataf[i]){
         t1 = dataf[i];
         t2 = startLoc[i];
         t3 = (i/blockSize);
         t4 = 2;
      }
   }
   if(t1 != d[index].filename){
      printf("No such file as %d",d[index].filename);
   }else if(t4 == 1){
      printf("\nData in %d:",t1);
   }else if(t4 == 2){
      printf("\nRead file %d(%d) from B%d",t2,t1,t3);
   }
   for(int i = t2*blockSize;i<((t2*blockSize)+size);i++){
      printf(".%d.",dataf[i]);
   }
   printf("\n");
}


void deleteCont(int index){
   int size = 0;
   for(int c= 0; c < index;c++){  
      if(d[index].filename == d[c].filename)
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
      if(d[index].filename == dataf[i]){
         printf("File : %d Start: %d End: %d", dataf[i],startLoc[i],endLoc[i]);
         t1 = dataf[i];
         t2 = startLoc[i];
         t3 = endLoc[i];
         dataf[i] = -1;
         startLoc[i] = -1;
         endLoc[i] = -1;
         break;
      }
   }
   printf("\nData in %d:",t1);
   for(int i = t2*blockSize;i< (t2*blockSize+size);i++){
      printf(".%d.",dataf[i]);
      dataf[i] = -1;
      startLoc[i] = -1;
   }
   printf("Has been deleted");
   printf("\n");
   for(int i = t2; i<=t3; i++){
      printf("Freeing %d",i);
      bitmap[i] = 1;
   }
   
}

int ifFullCont(){
   int countbitmap = 0;
   for(int i = 0; i < noOfBlock; i++){
      if(bitmap[i] == 0){
         countbitmap++;
         printf("blocks left %d", noOfBlock-countbitmap);
      }
   }
   if(countbitmap>=noOfBlock){ 
      return 1;
   }else{ 
     return 0;
   }
}
int freespaceCont(){
   int count = 0;
   if(ifFullCont()){
      return 1;
   }
   else{  
      if(blocksRequired == 0){
         return 1;
      }else if(blocksRequired>noOfBlock){
         return 1;
      }else{
         for(int i = 0; i < noOfBlock; i++){
            if(count == blocksRequired){
               break;
            }
            if(count < blocksRequired && bitmap[i] == 1){
               freed[count] = i;
               printf("Current Free[] %d", freed[count]);
               count++;
            }
            else{
               for(int j = 0; j<blocksRequired;j++){
                  freed[j] = 0;
               }
               count = 0;
            }
         }
      }
      printf(" found free ");
      for(int i = 0; i < blocksRequired; i++){
         printf("-B%d-",freed[i]+temp2);
      }
      printf("\n");
      return 0;
   }
}
