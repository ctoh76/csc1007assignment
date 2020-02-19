#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILESIZE 1000
#define MAX 130
FILE *fp;
typedef struct{
      char func[6];//to read add, read, delete based on first letter
      int filename;
      int data[FILESIZE];
}data;
data d[10];//basically able to read 10 lines so got 10 different set of data

int readFile();
void add();
void read();
void delete();
int freeMem();

int i = 0,pos = 0,Table[FILESIZE],r,a,b, fsize;
int volumecontrol1[] = {0}; 
int volumecontrol2[] = {0};
int indexf[MAX], block[MAX], dataf[MAX];

int blockSize, excessBlock, dirBlocks,k;
void initArray(){

	int temp[MAX];
	int counter = 0;
	int blockNum = 1;

	for(int a = 0; a<MAX;a++){
		counter = counter + 1;
		temp[a] = blockNum;
		if(counter == blockSize){
			counter = 0;
			blockNum = blockNum +1;
		}
	}

	for(int i = 0;i < MAX; i++){
		indexf[i] = i;
		block[i] = temp[i];
		dataf[i] = 0;
	}

}

void printDirectory(){
	
	printf("\n|  Index    Block    Entry\n");
	for(int i = 0;i < MAX; i++){
		printf("|    %d        %d        %d  \n", indexf[i],block[i],dataf[i]);
		
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
         printf("%d,",d[i].data[j]);//so they do scan in the values to be removed sooner or later cuz not required to printf
         token = strtok(NULL,",");
         j++;
      }
      i++;
   } 
   for(int c= 0; c < i;c++){
      printf("\nFunction: %s Filename: %d",d[c].func,d[c].filename);
      int *ptr = d[c].data;
      int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
      }
      if(size != 0){
         printf(" Data: ");
         for(int k = 0; k < size; k++){//2 instead of size idk le la i fked up
         printf("-%d-",d[c].data[k]);
         }
      }
      
   }
   
   fclose(fp);

   return 0;
}
void printVolumeControlBlock(){
	int arrayLength = sizeof(volumecontrol1)/sizeof(volumecontrol1[0]);
	printf("|  Index    File data  \n");
	for(int i = 0; i< arrayLength;i++){
		printf("|    %d       %d    \n", volumecontrol1[i],volumecontrol2[i]);
	}
}
void main()
{
   printf("\n Contiguous File Allocation \n\n");

   printf("Enter block size: ");
	scanf("%d", &blockSize);
	excessBlock = 130%blockSize;
	dirBlocks = (130-excessBlock)/blockSize;

   initArray();
   printDirectory();
   printVolumeControlBlock();
   readFile();
   for(int c= 0; c < i;c++){
      char *function = d[c].func;//d[1].func
      switch(*function){
         case 'a':
         case 'A':
            printf("\nEntered Add Function\n");
            //fsize = d[0].filename + FILESIZE;
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
}
void add(int index){
   printf("To Add Filename: %d",d[index].filename);
   a= 0;
   b=d[index].filename;
   if(freeMem()){
      pos--;
      printf("\n\nNot Enough Free Space Available \n");
      return;
   }
   int *ptr = d[index].data;
   int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
   }
   while(1){
       if(b+size-1>FILESIZE){
           continue;
       }
       if(Table[b]==0){
           for(a = b + 1;a<b+size;a++){
               if(Table[a]==1){
                   break;
               }
           }
       }
       if(a==b+size){
           break;
       }
   }
   for(a = b;a<b+size;a++){
       
       Table[a]=1;
   }
   printf("\nFile Allocation Table\n");
   printf("\nFileName\tLength\n");
    printf("\n%d\t\t%d",b,size);
    printf("\n");

}
void read(int index){
   printf("Read: %d\n",d[index].filename);
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
int freeMem(){
    int i,j=0;
    for(i=0;i<MAX;i++)
        if (dataf[i]>0)
        {
            j++;
        }
    if(i>j)
        return 0;
    else
        return 1;
}