#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILESIZE 100
FILE *fp;
typedef struct{
      char func[6];//to read add, read, delete based on first letter
      int filename;
      int data[FILESIZE];
}data;

int readFile();

int volumecontrol1[] = {0}; 
int volumecontrol2[] = {0};
int indexf[130], block[130], dataf[130][130];

int blockSize, excessBlock, dirBlocks; 
void initArray(){

	int temp[130];
	int counter = 0;
	int blockNum = 1;

	for(int a = 0; a<130;a++){
		counter = counter + 1;
		temp[a] = blockNum;
		if(counter == blockSize){
			counter = 0;
			blockNum = blockNum +1;
		}
	}

	for(int i = 0;i < 130; i++){
		indexf[i] = i;
		block[i] = temp[i];
		dataf[i][i] = 0;
	}

}

void printDirectory(){
	
	printf("\n|  Index    Block    Entry\n");
	for(int i = 0;i < 130; i++){
		printf("|    %d        %d        %d  \n", indexf[i],block[i],dataf[i][i]);
		
	}	
}
//add read delete not inside
void printVolumeControlBlock(){
	int arrayLength = sizeof(volumecontrol1)/sizeof(volumecontrol1[0]);
	printf("|  Index    File data  \n");
	for(int i = 0; i< arrayLength;i++){
		printf("|    %d       %d    \n", volumecontrol1[i],volumecontrol2[i]);
	}
}

int main(void)
{
	
//	int noOfEntries = 130, allocationType = 0, fileData[100];
	
	printf("Enter block size: ");
	scanf("%d", &blockSize);
	excessBlock = 130%blockSize;
	dirBlocks = (130-excessBlock)/blockSize;

	printf("Number of blocks : %d  Entries : %d Excess entry of %d on Block %d\n", dirBlocks+1,blockSize,excessBlock,dirBlocks+1);



char file_name[25];
   int i = 0;
   data d[10];//basically able to read 10 lines so got 10 different set of data
   char *token;
   char buff[1024];

   printf("Enter name of a file you wish to see\n");

   fp = fopen("c.csv", "r"); // read mode

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
 
   if (token != NULL)
      {
         while (token != NULL)
         {
            d[i].data[j] = atoi(token);
            // printf("%d,",d[i].data[j]);//so they do scan in the values
            token = strtok(NULL, ",");
            j++;
         }
      }
      else
      {
         d[i].data[j] = 0;
      }

      i++;
   } 

   int temp[130];
	int counter = 0;
	int blockNum = 1;

	for(int a = 0; a<130;a++){
		counter = counter + 1;
		temp[a] = blockNum;
		if(counter == blockSize){
			counter = 0;
			blockNum = blockNum +1;
		}
	}
   for(int c= 0; c < i;c++){
      printf("\nFunction:--%s--Filename:--%d--Data:",d[c].func,d[c].filename);
      int *ptr = d[c].data;
      int size = 0;
      while(*ptr !=0)
      {
         *ptr++;
         size++;
      }
      
      for(int k = 0; k < size; k++)
      {//2 instead of size idk le la i fked up
        for(int j = 0; j <size;j++)
         //dataf[j][k] =d[c].data[k];
         
         dataf[j][k] =  d[c].data[k];  
        //printf("%d,",d[c].data[k]);
        printf("%d,",dataf[i][k]);
      }
      for(int i = 0;i < 130; i++){
		indexf[i] = i;
		block[i] = temp[i];
		//dataf[i] = 0;
    //printf("%d", dataf[i]);
	}
      
   }
   

	

   fclose(fp);

//initArray();
printDirectory();
printVolumeControlBlock();
//readFile();
}
