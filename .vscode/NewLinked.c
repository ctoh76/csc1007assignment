#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>

#define TB 100
#define MAX 130
FILE *fp;
typedef struct{
      char func[6];
      int filename; 
      int data[MAX];
      int st;
    struct node
    {
        int index;
        struct node *next;
    }*Start,*current,*newnode,*temp;
}data;
data d[MAX];

int readFile(); 
int freespace();
void allocate();
void display();
//void deallocate();
void initArray();
void initFreespace();
void printStorage();
void printDirectory();

int Table[TB+1],r,B=0;
int f[50];


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
	printf("\n|  Index    Block    FileData   Start    End\n");
	for(int i = 0;i < (temp2 * blockSize); i++){
      	printf("|   %d         %d         %d         %d       %d |\n",indexf[i],block[i],dataf[i],startLoc[i],endLoc[i]);
   }
   printf("*----------------------------------------------*\n");
   printStorage();
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

void printVolumeControlBlock(){//nvr used at all dk how to use
	int arrayLength = sizeof(volumecontrol1)/sizeof(volumecontrol1[0]);
	printf("|  Index    File data  \n");
	for(int i = 0; i< arrayLength;i++){
		printf("|    %d       %d    \n", volumecontrol1[i],volumecontrol2[i]);
	}
}

//Reading file 
int readFile(){

   char file_name[25];
   char *token;
   char buff[1024];

   printf("Enter name of a file you wish to see\n");
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
         printf("%d,",d[i].data[j]);//so they do scan in the values
         token = strtok(NULL,",");
         j++;
      }
      i++;
   } 

   for(int c= 0; c < i;c++){
     char *function = d[c].func;
     switch(*function)
     {
                case 'a':
                case 'A':
                    printf("\nChoice add");
                    allocate(c);
                    break;

                case 'd':
                case 'D':
                   printf("\nChoice delete");
                    //deallocate(c);
                    break;

                case 'r':
                case 'R':
                    printf("\nChoice display");
                    //display(c);
                    break;

                default:
                    printf("\nInvalid Choice");
        }
     }

   //Function: add -> func
   //FileName:100 -> filename
   //Data: The length of the data ->data
   /*for(int c= 0; c < i;c++){
      printf("\nFunction:--%s--Filename:--%d--Data:",d[c].func,d[c].filename);
      int *ptr = d[c].data;
      int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
      }
      printf("\n%d\n",size);
      for(int k = 0; k < size; k++){//2 instead of size idk le la i fked up
         printf("%d,",d[c].data[k]);
      }
   }*/

   
   fclose(fp);
   return 0;

}


void main()
{
   
     initArray();
     printDirectory();
     readFile();
     printDirectory();
}

//add
void allocate(int index)

//get the func,filename and data
{
    double value;
    int *ptr = d[index].data;
    int size = 0;
    while(*ptr !=0){
         *ptr++;
         size++;
      }
//get the blockszie require 
   if(blockSize<size){
      value = ceil(size/(blockSize-1));
      printf("lolol:%f",value);
   }else{
      value = 1;
   }
  blocksRequired = value;
  printf("\nFreee space require %d",blocksRequired);
  printf("\nAdd File %d and",d[index].filename);
//insert to see if got space

   if(freespace()){
     printf("Not allocated due to full Storage\n");
   }
   else{
         for(i=1;i<=size;i++){
        d[pos].newnode=(struct node *)malloc(sizeof(struct node));
        r=rand();
        f[i]=0;
      int st = (freed[i] + temp2) * blockSize;
      if (f[st] == 0){
        d[pos].newnode ->index =r
        d[pos].newnode ->next =NULL;
        if(d[pos].Start==NULL)
        {
             d[pos].Start=d[pos].newnode;
            d[pos].current=d[pos].newnode;
        }
        else
        {
            d[pos].current->next=d[pos].newnode;
            d[pos].current=d[pos].newnode;
        }
     else{

     }
   }
         }
       
      

      /*int k = 0;
      int q = (freed[0] + temp2) * blockSize;
      int w = (freed[blocksRequired-1]+ temp2)*blockSize;
      for(int i = q,k = 0;i <w && k<size;i++,k++){//fill data from struct into dataf[] from storage struct
         if(blocksRequired>1){
            dataf[i] = d[index].data[k];
            printf("\ndata inside File %d",d[index].data[k]);
            startLoc[i] = d[index].filename;
         }
         else{
            dataf[i] = d[index].data[k];
            printf("\ndata inside File %d",d[index].data[k]);
            startLoc[i] = d[index].filename;
         } 
      }*/

      //i swear go rmb what is temp2 cuz its everywhere so dumb for a temp int but i did this mess
      //temp2 is the starting block no. of the storage sturcture so if blocksize is 2 temp2 will be 22 if blocksize is 3 temp2 will be 11.
      if(c == temp2 * blockSize - 1){//create a counter for directory struct so if counter reaches the max block of directory struct which is 21 means full le by right shouldnt reach here will be damn weird
         printf("Exceeded Directory allocated");
      }else{
         
         dataf[c] = d[index].filename;//add per add file into directory struct
         startLoc[c] = freed[0] + temp2;//add where it start into directory struct
         endLoc[c] = freed[0] + temp2 + (value -1);
         c++;
      }
      int l = 0;//temp int
      for(int j = 0; j<blocksRequired; j++){//allocated into freespace
         l = freed[j];//freed[j] = block number to add in here very blurry cuz damn long do de
         bitmap[l] = 0;//put used(1) into the bitmap to show its used
      } 
      
   // printf("\n\tFile Allocation Table\n");
    
   
    //printf("\nFileName\tStart\tEnd\tLength\n");
    //printf("\n%d\t\t%d\t%d\t%d",d[index].filename,d[pos].st,d[pos].current->index,size);
    //printf("File : %d Start: %d End: %d", dataf[i],startLoc[i],endLoc[i]);
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
      for(int i = 0; i < noOfBlock; i++){//scan the noOfblocks in the storage structure(basically 43)B22- B64
         //# for some cases where like if data input is 5 cuz its contiguous alloc so need ceiling it ceil(5/2) = 3
         //eg. if count(0) less than blocksRequired(3) and bitmap of block 0 is free to use, freed[0] = block no(i)
           if(count < blocksRequired){
               freed[count] = i;//freed[count] stores the blockno its currently adding for example freed[0] = 4, 5 or 6
               count++;
           }  
      }
      printf(" found free ");
      
      for(int i = 0; i < blocksRequired; i++){//if found 3 space for blockrequired(3)
         printf("-B%d-",freed[i]+temp2);//print which block is free
      }
      printf("\n");
      return 0;//then return 0 or false # i might have messed up whether 0 is true or false but basically return it to the add function
   }

//gets its file name which is 200 just to cfm de la then get its startLoc and endLoc which is like 25 and 27
         
}



   /* for(i=1;i<=pos;i++)
    {
        printf("\nhi");
        printf("\n%s\t\t%d\t%d\t%d",d[i].func,d[i].st,d[pos].current->index,d[i].data);
        printf("\n");
    }
}  
*/
   
    
//delete
/*
void deallocate(int index)
{
   //printf("\nFileName that to delete:",d[index].filename);
    int *ptr = d[index].data;
    int size = 0;
    while(*ptr !=0){
         *ptr++;
         size++;
      }
      char fn = d[index].filename;
   for(i=1;i<=pos;i++)
   {
            if(strcmp(d[i].func,fn)==0)  //n-->function 
            {
                d[i].current=d[i].Start;
                while(d[i].current)
                {
                    Table[d[i].current->index]=0;
                    d[i].temp=d[i].current;
                    d[i].current=d[i].current->next;
                    free(d[i].temp);
                }

                strcpy(d[i].func,"NULL");
                d[i].st=0;
               
              
                printf("\nFile (%d) Deleted Successfully \n",fn);
                break;
            }
            else
                printf("\nDeletion Unsuccessful\n");
    }
    printf("\n\t\tFile Allocation Table\n");
    printf("\nFileName\tStart\tLength\n");
    printf("\n%d\t\t%d\t%d",d[i].filename,d[i].st,size);
    /*for(i=1;i<=pos;i++)
    {
        
        printf("\n");
    }
}
*/

//read

void display(int index)
{
    
    int size =0;
    for(int c= 0; c<index;c++)
    {
        if(d[index].filename== d[c].filename)
        {
            d[index].current=d[index].Start;
            while(d[index].current)
            {
               printf(">--%d-->",d[index].current->index);
               d[index].current=d[index].current->next;
            }
            break;
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
         t1 = dataf[i];//file data eg read 1401 t1 = 1401
         t2 = startLoc[i];//file start block 
         t3 = (i/blockSize);//file block location of the data
         t4 = 2;//condition
      }
   }
   if(t1 != d[index].filename){//just to say if nosuch file it will be 0
      printf("No such file as %d",d[index].filename);
   }else if(t4 == 1){
      printf("\nData in %d:",t1);//filename which should be 200 but will varies depend on what we read
   }else if(t4 == 2){
      printf("\nRead file %d(%d) from B%d",t2,t1,t3);
   }
   for(int i = t2*blockSize;i<((t2*blockSize)+size);i++){//for loop from index(blk 25 * blocksize 2)start block of the file to index(blk 25 * blocksize + length of the data inside(6))
      printf(".%d.",dataf[i]);//print the data
   }
   printf("\n");
printf(">--%d-->",d[index].current->index);
    
}





