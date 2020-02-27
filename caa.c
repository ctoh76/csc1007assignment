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
int freespace();
void initArray();
void initFreespace();
void printStorage();
void printDirectory();

int i = 0,pos = 0,temp2 = 0,noOfBlock = 0,blocksRequired,blockAvail,c = 0;
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
   printVolumeControlBlock();*/
   readFile();
   printDirectory();
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
   int *ptr = d[index].data; 
   int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
   }
   double value = ceil((double)size/blockSize);
   blocksRequired = value;//get amount of blocksrequired to place in storage structure.
   //freespace();
   printf("\nAdding File %d and",d[index].filename);
   if(freespace()){
      printf("Not allocated due to full Storage\n");
   }else{
      /*if(size != 0){
         printf(" Data: ");
         for(int k = 0; k < size; k++){
            printf("-%d-",d[index].data[k]);
         }
      }*/   
   //but have not put data into block
   //                        0     +   22  *    2     +   6 = 50
   //to incement index = (freed[j] + temp2)*blockSize + length
   //List of array able to use bitmap[](consist of 0s and 1s)|freed[](consist of the empty block no.)|d[].data[](consist of the real data)
   //data is in d[index].data[k]
      int k = 0;
      int q = (freed[0] + temp2) * blockSize;
      for(int i = q,k = 0;i <(q + size) && k<size;i++,k++){//fill data into dataf
         dataf[i] = d[index].data[k];
      }
      //required to fill filename and start and end
      //run via index run 1 time per function need to noe the jump to the next index
      //done adding into directory structure
      if(c == temp2 * blockSize){
         printf("Exceeded Directory allocated");
      }else{
         dataf[c] = d[index].filename;
         startLoc[c] = freed[0] + temp2;
         endLoc[c] = freed[0] + temp2 + (value -1);
         c++;
      }
      int l = 0;
      for(int j = 0; j<blocksRequired; j++){//allocated into freespace
         l = freed[j];
         bitmap[l] = 0;
      } 
   }                        
   
}
void read(int index){
   //as when we read file the data stored is based on the index so like d[0].filename = 100 cuz we add 100 first then d[1].filename = 200 cuz we add 200 next
   int size = 0;//so d[0].data is the data in d[0].filename which is 101-106, i basically count the length of it cuz idk why but i cant use sizeof 
   for(int c= 0; c < index;c++){  
      if(d[index].filename == d[c].filename)
      {
         int *ptr = d[c].data;
         while(*ptr !=0){//to count the size of data basically is like len(data)
            *ptr++;
            size++;
         }
      }
   }
   int t1 = 0, t2 = 0,t3 = 0;//created 3 temp int to store the dataf[i] startLoc[i] endLoc[i]
   for(int i = 0; i<temp2*blockSize; i++){//this for loop run based on the directory structure cuz it runs from blk 0 to 21,lets say for blocksize 2 it runs from index 0 to index 43
      if(d[index].filename == dataf[i]){//if the filename from the struct which store the readfile meaning like read 200 filename is 200 compare with the directory structure to find 200
         printf("File : %d Start: %d End: %d", dataf[i],startLoc[i],endLoc[i]);//gets its file name which is 200 just to cfm de la then get its startLoc and endLoc which is like 25 and 27
         t1 = dataf[i];//filename
         t2 = startLoc[i];//if we  alr added 200 to block 25- block 27 and we read filename 200 should appear blk 25 
         t3 = endLoc[i]; // should appear block 27
      }
   }
   //havent go add function() for if read de file is not anyof the file added
   printf("\nData in %d:",t1);//filename which should be 200 but will varies depend on what we read
   for(int i = t2*blockSize;i<((t2*blockSize)+size);i++){//for loop from index(blk 25 * blocksize 2)start block of the file to index(blk 25 * blocksize + length of the data inside(6))
      printf(".%d.",dataf[i]);//print the data
   }
   printf("\n");
   
   printf("\nExiting Read Function\n");
}
void delete(int index){
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
   double value = ceil((double)size/blockSize);
   blocksRequired = value;
   int t1 = 0, t2 = 0,t3 = 0;
   for(int i = 0; i<temp2*blockSize; i++){
      if(d[index].filename == dataf[i]){
         printf("File : %d Start: %d End: %d", dataf[i],startLoc[i],endLoc[i]);
         t1 = dataf[i];
         t2 = startLoc[i];
         t3 = endLoc[i];
         dataf[i] = 0;
         startLoc[i] = 0;
         endLoc[i] = 0;
      }
   }
   printf("\nData in %d:",t1);
   for(int i = t2*blockSize;i< (t2*blockSize+size);i++){
      printf("Deleting data : %d",dataf[i]);
      dataf[i] = 0;
   }
   printf("\n");
   for(int i = t2 - temp2; i< t3-temp2; i++){
      bitmap[i] = 1;
   }
}
void initFreespace(){//initialize a freespace bitmap based of the total noofblocks available in storage structure 
   for(int i = 0; i < noOfBlock; i++){
      bitmap[i] = 1;//initiate all into 1 so that all is free (1 = free, 0 = used).
   }
}
int ifFull(){//runs thru the who block to check if bitmap[] reaches all 0 #for bitmap[] it stores a value of 0 or 1 to indicate each block in storage structure is used or not used
   int count4bit = 0;//counter
   for(int i = 0; i < noOfBlock; i++){//run the whole block eg. if block size 2, total storage block got 43(B22 - B64)
      if(bitmap[i] == 0){//checks eg. if block size 2, B22 - B64 is all 0s 0= used, 1=free to use
         count4bit++;//increment per 0 in bitmap
      }
   }
   if(count4bit>=noOfBlock){ //if counter bigger than or equal to total storage block(43) means fully used
      return 1; //return 1 or true
   }else{
      return 0; //return 0 or false
   }
}
int freespace()
{ 
   int count = 0;//counter
   if(ifFull()){//run ifFull
      return 1;//if ifFull() is full le return 1 or true to add func
   }
   else{  //if ifFull() is not full continue run
      for(int i = 0; i < noOfBlock; i++){//scan the noOfblocks in the storage structure(basically 43)B22- B64
         if(count == blocksRequired){//blocksrequired is calculated based on size or length of data in add divide by blocksize typed by user
            break;// eg. if user type blocksize 2 and add file de data length is 6  6/2 = 3 if 3 == 3 break 
         }//# for some cases where like if data input is 5 cuz its contiguous alloc so need ceiling it ceil(5/2) = 3
         if(count < blocksRequired && bitmap[i] == 1){//eg. if count(0) less than blocksRequired(3) and bitmap of block 0 is free to use, freed[0] = block no(i)
            freed[count] = i;//freed[count] stores the blockno its currently adding for example freed[0] = 4, 5 or 6
            count++;
         }
         else{//else there isnt 3 space avail for blockrequired(3) clear counter and clear the freed[] basically reset it
            for(int j = 0; j<blocksRequired;j++){//clear freed[] array 
               freed[j] = 0;
            }
            count = 0;//clear counter
         }
      }
      printf(" found free ");
      for(int i = 0; i < blocksRequired; i++){//if found 3 space for blockrequired(3)
         printf("-B%d-",freed[i]+temp2);//print which block is free
      }
      printf("\n");
      return 0;//then return 0 or false # i might have messed up whether 0 is true or false but basically return it to the add function
   }
    
}