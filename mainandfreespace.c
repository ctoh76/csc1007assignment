#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 130

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

    printf("Do you want to display free space? input 1 for yes and 0 for no");
    scanf("%d",&k);
    if (k==1)
    {
        freespace();
    }
    else
    {
        return 0;
    }
    



}

//FREE SPACE MANAGEMENT//

int IfFull()
{
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
void freespace()
{
    int i,j=0;
    if (IfFull())
    {
        printf("There is not space left");
    }
    else
    {
        for(i=0;i<MAX;i++)
        {
            if(dataf[i]>0)
            {
                printf("Index   %d     0\n",i);
            }
            else 
            {
                printf("Index    %d     1\n",i);
                j++;
            }
        }
        printf("Number of free space %d",j);
    }
}