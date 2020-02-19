#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int volumecontrol1[] = {0}; 
int volumecontrol2[] = {0};
int indexf[130], block[130], dataf[130];

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
		dataf[i] = 0;
	}

}

void printDirectory(){
	
	printf("\n|  Index    Block    Entry\n");
	for(int i = 0;i < 130; i++){
		printf("|    %d        %d        %d  \n", indexf[i],block[i],dataf[i]);
		
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

initArray();
printDirectory();
printVolumeControlBlock();


}