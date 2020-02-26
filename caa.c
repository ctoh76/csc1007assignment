#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 130//define max size of data able to store
FILE *fp;
typedef struct{ //Struct created to read in function require, filename, data able to hold
      char func[6];//to read add, read, delete based on first letter
      int filename;
      int data[MAX];
}data;
data d[MAX];//130 set of data able to read

int readFile();
void add();
void read();
void delete();
void freespace();
void initArray();
void initFreespace();
void printStorage();
void printDirectory();

int i = 0,pos = 0,temp2 = 0,noOfBlock = 0,r,a,b,blocksRequired,blockAvail;
int volumecontrol1[] = {0}; 
int volumecontrol2[] = {0};
int indexf[MAX], block[MAX], dataf[MAX],startLoc[MAX],endLoc[MAX],bitmap[MAX], freed[MAX]; 
int blockSize, excessBlock, dirBlocks,k;

void initArray(){
   do{
      printf("Enter block size between(2-43): ");
	   scanf("%d", &blockSize);  
   }while(blockSize < 2 || blockSize > 43);//to be explained by clarence

      //excessBlock = 130%blockSize;
	   //dirBlocks = (130-excessBlock)/blockSize;
      int temp[MAX];
	   int counter = 0;
      int blockNum = 0;

	   for(int a = 0; a<MAX;a++){//get no. of blocks
		   counter = counter + 1;
		   temp[a] = blockNum;
		   if(counter == blockSize){
			   counter = 0;
			   blockNum = blockNum +1;
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
      noOfBlock = blockNum;
}
void printDirectory(){
   int temp[MAX];

   while(temp[MAX]>(temp2 * blockSize)){
      temp[MAX] -= 1;
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
   int temp[MAX];

   printf("*---------------Storage Section----------------*");
   printf("\n|  Index    Block    Entry\n");
	for(int i = (temp2 * blockSize);i < MAX; i++){//
      	printf("|   %d         %d         %d                     |\n",indexf[i],block[i],dataf[i]);
   }
   printf("*-----------------------------------------------*\n");
   noOfBlock = noOfBlock-temp2;
   initFreespace();
}
void printVolumeControlBlock(){
	int arrayLength = sizeof(volumecontrol1)/sizeof(volumecontrol1[0]);
	printf("|  Index    File data  \n");
	for(int i = 0; i< arrayLength;i++){
		printf("|    %d       %d    \n", volumecontrol1[i],volumecontrol2[i]);
	}
}
int readFile(){

   char file_name[25];
   char *token;
   char buff[1024];

   printf("Please Enter your desired csv file\n");
   scanf("%s",&file_name);

   fp = fopen(file_name, "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");//if file does not exist
      exit(EXIT_FAILURE);
   }
   while(fgets(buff,sizeof(buff),fp)){
      int j = 0;
      token = strtok(buff,",");
      strcpy(d[i].func,token);
      token = strtok(NULL,",");
      d[i].filename = atoi(token);
      token = strtok(NULL,",");
      while(token != NULL){   
         d[i].data[j]= atoi(token);
         //printf("%d,",d[i].data[j]);//so they do scan in the values to be removed sooner or later cuz not required to printf
         token = strtok(NULL,",");
         j++;
      }
      i++;
   } 
   for(int c= 0; c < i;c++){
      char *function = d[c].func;//d[1].func
      switch(*function){
         case 'a':
         case 'A':
            add(c);
            break;
         case 'r':
         case 'R':
            printf("\nEntered Read Function\n");
            read(c);
            break;
         case 'd':
         case 'D':
            printf("\nEntered Delete Function\n");
            delete(c);
            break;
         default:
            printf("Reached Default");//dk what to type in default
            break;
      } 
   }
   
   fclose(fp);

   return 0;
}

void main()
{
   initArray();
   printDirectory();
   /*printf("\n Contiguous File Allocation \n\n");

   printf("Enter block size: ");
	scanf("%d", &blockSize);
	excessBlock = 130%blockSize;
	dirBlocks = (130-excessBlock)/blockSize;


   initArray();
   printDirectory();
   printVolumeControlBlock();
   */
   readFile();
   printStorage();
   /*for(int c= 0; c < i;c++){
      char *function = d[c].func;//d[1].func
      switch(*function){
         case 'a':
         case 'A':
            printf("\nEntered Add Function1\n");
            //fsize = d[0].filename + FILESIZE;
            //add(c);
            break;
         case 'r':
         case 'R':
            printf("\nEntered Read Function\n");
            read(c);
            break;
         case 'd':
         case 'D':
            printf("\nEntered Delete Function\n");
            delete(c);
            break;
         default:
            printf("Reached Default");//dk what to type in default
            break;
      }
   }*/

}
void add(int index){
   printf("Adding File %d\n",d[index].filename);
   int *ptr = d[index].data;
   int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
   }
   double value = ceil((double)size/blockSize);
   blocksRequired = value;
   freespace();
   
   if(size != 0){
      printf(" Data: ");
      for(int k = 0; k < size; k++){
         printf("-%d-",d[index].data[k]);
      }
   }
   int l = 0;
   for(int j = 0; j<blocksRequired; j++){//allocated into freespace
         l = freed[j];
         bitmap[l] = 0;
   }    
   printf("TTTTTT:%d",temp2*blockSize);                                            
   //but have not put data into block
   for(int i = (temp2 * blockSize);i < MAX; i++){

   }

}
void read(int index){
   printf("Reading: %d\n",d[index].filename);//read whatever is stored in struct
   for(int c= 0; c < index;c++){
      int *ptr = d[c].data;
      int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
      }
      if(d[index].filename == d[c].filename)
      {
          printf("Display File: %d Data:",d[c].filename);
          for(int k = 0; k < size; k++){
             printf("..%d",d[c].data[k]);
          }
      }
      for(int k = 0; k < size; k++){
         if(d[index].filename == d[c].data[k]){
             printf("Display Data: %d",d[c].data[k]);
         }
      }
   }
   printf("\nExiting Read Function");
}
void delete(int index){
   printf("Deleted: %d\n",d[index].filename);
   for(int c= 0; c < index;c++){
      int *ptr = d[c].data;
      int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
      }
      if(d[index].filename == d[c].filename)
      {
          d[c].filename = 0;
          for(int k = 0; k < size; k++){
             d[c].data[k] = 0;
          }
      }
      for(int k = 0; k < size; k++){
         if(d[index].filename == d[c].data[k]){
            d[c].data[k] = 0;
            size = size -1;
         }
         printf("Filename: %d ,Data inside: %d \n", d[c].filename,d[c].data[k]); //to print what is left in the code
      }
   }
   for(int c= 0; c < index;c++){
      int *ptr = d[c].data;
      int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
      }
      if(strcmp("read",d[c].func) !=0 && d[c].filename != 0){
         printf("\nFilename: %d Data: ", d[c].filename); // whats left
         for(int k = 0; k < size; k++){
            printf("%d,",d[c].data[k]);
         }
      }
   }
   printf("Exiting Delete Function");
}
void initFreespace(){
   for(int i = 0; i < noOfBlock; i++){
      bitmap[i] = 1;
   }
}
void freespace()
{ 
   printf("Blocks required :%d || No. of Blocks :%d \n", blocksRequired,noOfBlock);
   int k = 0;
   for(int i = 0; i < noOfBlock; i++){//scan the noOfblocks in the directory
      if(k == blocksRequired){//if 3 == 3 break
         break;
      }
      if(k < blocksRequired && bitmap[i] == 1){//if 0 < 3 && bitmap[0] == 1 ,freed[0] = block no(i)
         freed[k] = i;
         k++;
      }
      else{
         for(int j = 0; j<blocksRequired;j++){
            freed[j] = 0;
         }
         k = 0;
      }
   }
   //have not done the if overload how condition
   printf("Found free: ");
   for(int i = 0; i < blocksRequired; i++){
      printf(" B%d,",freed[i]+temp2);
   }
   printf("\n");

   // int *ptr = d[index].data;
   // int size = 0;
   //    while(*ptr !=0){
   //       *ptr++;
   //       size++;
   // }//size of data
   // int b = ceill((double)size/blockSize);//1
   // int count = 0;  
   // for(int i = temp2; i<floor((double)MAX/blockSize); i++){
   //    if(bitmap[i] == 0 && count < b){
   //       freed[count] = i; 
   //       bitmap[i] = 1;
   //       printf("Block %d is free\t", freed[count]);
   //       count++;  
   //    }
   // }
}