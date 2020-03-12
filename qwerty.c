#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>// for ceiling function

#define MAX 130//define max size of data able to store
FILE *fp;
typedef struct{ //Struct created to read in function require, filename, data able to hold
      char func[6];//to read add, read, delete based on first letter
      int filename;
      int data[MAX];
}data;
data d[MAX];//130 set of data able to read

int readFile();//i have lost track of how many functions i had might have some that was redudant
int freespace();
void add();
void read();
void delete();
void initArray();
void initFreespace();
void printStorage();
void printDirectory();

int i = 0,pos = 0,temp2 = 0,noOfBlock = 0,blocksRequired,blockAvail,c = 0,amtofFunccollected = 0;//dk which nvr used need to clear it when i make the code look pretty
int volumecontrol1[] = {0}; //nvr used
int volumecontrol2[] = {0}; //nvr used dk what is volume control need recap abt it
int indexf[MAX], block[MAX], dataf[MAX],startLoc[MAX],endLoc[MAX],bitmap[MAX], freed[MAX];//here de all got used  
int blockSize, excessBlock, dirBlocks,k;//excess and dir block havent used need rmb to make it remove redudant blocks but if no time do jiu suan le
int choice,anotherdirblock ;
int count1;

void initArray(){//init array
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
   int temp3 = noOfBlock;
   while(temp3>(temp2 * blockSize)){//this is the cool shit which calculate the blocksize for directory and blocksize for storage temp is directory end block,temp2 is storage start block
      temp3 -= 1;
      temp2 += 1;
      
   }
   printf("*-------------Directory Section--------------*");
	printf("\n|  Index    Block    FileData   Start    End\n");
	for(int i = 0;i < (temp2 * blockSize); i++){
      	printf("|   %d         %d         %d         %d       %d |\n",indexf[i],block[i],dataf[i],startLoc[i],endLoc[i]);
   }
   printf("*----------------------------------------------*\n");
   
}
void printStorage(){

   printf("*---------------Storage Section----------------*");
   printf("\n|  Index    Block    Entry\n");
	for(int i = (temp2 * blockSize);i < MAX; i++){// need include something to push up the list if i decide to add a new file in it will appear at the bottom uh...
      	printf("|   %d         %d         %d                    |\n",indexf[i],block[i],dataf[i]);//i add startLoc[] in this which reflects the start block of each file
   }
   printf("*-----------------------------------------------*\n");
   
   noOfBlock = noOfBlock-temp2;
   initFreespace();
}
int readFile(){//read csv and store everything into struct d[]

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
      strcpy(d[i].func,token);
      token = strtok(NULL,",");
      d[i].filename = atoi(token);
      token = strtok(NULL,",");
      while(token != NULL){   
         d[i].data[j]= atoi(token);
         token = strtok(NULL,",");
         j++;
      }
      i++;
      amtofFunccollected++;
   } 
   
   fclose(fp);//close the file
   return 0;
}
void main()
{
   initArray();//initialize array
   printDirectory();//print the empty one out once
   printStorage();
   readFile();//read csv file
    for(int c= 0; c < amtofFunccollected;c++){//interestingly enuf a readfile function i go put in here that after every func add, read or delete i go add immediately
      char *function = d[c].func;//d[1].func
      switch(*function){
         case 'a'://read until character a or A means add la, r or R means read, d or D means delete
         case 'A':
            printf("\nEntered Add Function\n");
            //add(c);
            break;
         case 'r':
         case 'R':
            printf("\nEntered Read Function\n");
           // read(c);
            break;
         case 'd':
         case 'D':
            printf("\nEntered Delete Function\n");
            //delete(c);
            break;
         default:
            printf("Reached Default");//dk what to type in default should i even have a default here idk help me
            break;
      } 
    }
   printDirectory();//after running everything print the directory and storage structure again

}
void add(int index){
    int *ptr = d[index].data; //get the length of file data inthe struct which stored in readfile()
   int size = 0;
   while(*ptr !=0){
      *ptr++;
      size++;//eg. if file is 100 data is 101-106 size or filelength is 6
   }
   double blocksRequired = ceil((double)size/blockSize-1);

    if(freespace()){
        printf("Not allocated due to full Storage\n");
    }
    else
    {
        
    }
    

}

void initFreespace(){//initialize a freespace bitmap based of the total noofblocks available in storage structure 
   for(int i = 0; i < noOfBlock; i++){
      bitmap[i] = 1;//initiate all into 1 so that all is free (1 = free, 0 = used).
   }
}
int ifFull(){//runs thru the who block to check if bitmap[] reaches all 0 #for bitmap[] it stores a value of 0 or 1 to indicate each block in storage structure is used or not used
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
int freespace(){

   int count = 0;//counter
   if(ifFull()){//run ifFull
      return 1;//if ifFull() is full le return 1 or true to add func
   }
   else{  //if ifFull() is not full continue run

      for(int i = 0; i < noOfBlock; i++){//scan the noOfblocks in the storage structure(basically 43)B22- B64//# for some cases where like if data input is 5 cuz its contiguous alloc so need ceiling it ceil(5/2) = 3
         if(count < blocksRequired && bitmap[i] == 1){//eg. if count(0) less than blocksRequired(3) and bitmap of block 0 is free to use, freed[0] = block no(i)
            freed[count] = i;//freed[count] stores the blockno its currently adding for example freed[0] = 4, 5 or 6
            count++;
         }
         printf("%d",freed[count]);
      }
      printf(" found free ");
      for(int i = 0; i < blocksRequired; i++){//if found 3 space for blockrequired(3)
         printf("-B%d-",freed[i]+temp2);//print which block is free
      }
      printf("\n");
      return 0;//then return 0 or false # i might have messed up whether 0 is true or false but basically return it to the add function
   }
}