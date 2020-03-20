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

int i = 0,pos = 0,temp2 = 0,noOfBlock = 0,blocksRequired,blockAvail,c = 0;//dk which nvr used need to clear it when i make the code look pretty
int volumecontrol1[] = {0}; //nvr used
int volumecontrol2[] = {0}; //nvr used dk what is volume control need recap abt it
int indexf[MAX], block[MAX], dataf[MAX],startLoc[MAX],endLoc[MAX],bitmap[MAX], freed[MAX];//here de all got used  
int blockSize, excessBlock, dirBlocks,k;//excess and dir block havent used need rmb to make it remove redudant blocks but if no time do jiu suan le

void initArray(){//init array
   do{
      printf("Enter block size between(2-43): ");
	   scanf("%d", &blockSize);  
   }while(blockSize < 2 || blockSize > 43);//why blocksize must be 2 to 43 is cuz when u calculate right per block we have we need an index to store the added block de start and end
   //so like if we put block size 1 we need like 130 index to fill in out file info into directory so means its impossible de so can only start from 2 as to why its until 43
   //cuz if we used 44 so we will have we only have 2 pathetic blocks of size 44 then funny thing is use gonna need to throw away 42 block space cuz redudant 
   //then 1 for directory 1 for storage which wont make sense uh u use such a big space of index 44
   //to store 1 goddamn file info... anw this can edit de if u got better de lets follow it!!!!

      //excessBlock = 130%blockSize; dk how use this
	   //dirBlocks = (130-excessBlock)/blockSize; same for this dk how use
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
      noOfBlock = blockNum;//total block no.
}
void printDirectory(){//print directory
   int temp[MAX];

   while(temp[MAX]>(temp2 * blockSize)){//this is the cool shit which calculate the blocksize for directory and blocksize for storage temp is directory end block,temp2 is storage start block
      temp[MAX] -= 1;
      temp2 += 1;
   }
   printf("*-------------Directory Section--------------*");
	printf("\n|  Index    Block    FileData   Start    End|\n");
	for(int i = 0;i < (temp2 * blockSize); i++){
      	printf("|   %d         %d         %d         %d       %d |\n",indexf[i],block[i],dataf[i],startLoc[i],endLoc[i]);
   }
   printf("*----------------------------------------------*\n");
   printStorage();
}
void printStorage(){

   printf("*---------------Storage Section----------------*");
   printf("\n|  Index    Block    Entry|\n");
	for(int i = (temp2 * blockSize);i < MAX; i++){// need include something to push up the list if i decide to add a new file in it will appear at the bottom uh...
      	printf("|   %d         %d         %d                    |\n",indexf[i],block[i],dataf[i]);//i add startLoc[] in this which reflects the start block of each file
   }
   printf("*-----------------------------------------------*\n");
   noOfBlock = noOfBlock-temp2;
   initFreespace();
}
void printVolumeControlBlock(){//nvr used at all dk how to use
	int arrayLength = sizeof(volumecontrol1)/sizeof(volumecontrol1[0]);
	printf("|  Index    File data  \n");
	for(int i = 0; i< arrayLength;i++){
		printf("|    %d       %d    \n", volumecontrol1[i],volumecontrol2[i]);
	}
}//pls teach me how to use it
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
   } 
   for(int c= 0; c < i;c++){//interestingly enuf a readfile function i go put in here that after every func add, read or delete i go add immediately
      char *function = d[c].func;//d[1].func
      switch(*function){
         case 'a'://read until character a or A means add la, r or R means read, d or D means delete
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
            printf("Reached Default");
            break;
      } 
   }
   fclose(fp);//close the file
   return 0;
}
void main()
{
    initArray();//initialize array
    printDirectory();//print the empty one out once
    readFile();//read csv file
    printDirectory();
}
void add(int index){
}
void read(int index){ 
}
void delete(int index){
}
void initFreespace(){
   for(int i = 0; i < noOfBlock; i++){
      bitmap[i] = 1;//initiate all into 1 so that all is free (1 = free, 0 = used).
   }
}
int ifFull(){
   int count4bit =   0;
   for(int i = 0; i < noOfBlock; i++){
      if(bitmap[i] == 0){
         count4bit++;
      }
   }
   if(count4bit>=noOfBlock){
      return 1;
   }else{
      return 0;
   }
}
int freespace(){
   int count = 0;
   if(ifFull()){
      return 1;
   }
   else{
      for(int i = 0; i < noOfBlock; i++){
         if(count == blocksRequired){
            break;
         }
         if(count < blocksRequired && bitmap[i] == 1){
            freed[count] = i;
            count++;
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