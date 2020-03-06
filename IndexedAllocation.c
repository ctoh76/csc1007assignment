#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int block = 26;
int blockSize = 5;
int dirBlock = 5;
int strBlock = 21;
int blkIndex = 0;
int entries = 8;
int blkReq = 0;
int indexCounter = 0;
int counter = 0;
int temp = 0;

int data[10] = {101, 102, 103, 104, 105, 106, 107, 108};

int disk[130];
int blk[10];

int main()
{
    if (entries % blockSize == 0) {//calculate total number of blks required the file
        blkReq = entries / blockSize + 1;
    } else {
        blkReq = entries / blockSize + 2;
    }

    for (int i = 0; i < blkReq; i++) {//store free block index
        blk[i] = i + dirBlock;
        printf("%i", blk[i]);
    }

    int startBlk = blk[0];
    indexCounter = startBlk * blockSize;

    for (int i = 0; i < blockSize; i++) {
        if (blk[i+1] == 0) {    //store pointers into the first free block
            break;
        }
        disk[indexCounter++] = blk[i+1];
        counter = blk[i+1] * blockSize;
        for (int j = 0; j < blockSize; j++) {
            if (data[temp] == 0) {  //store data into the free blocks
                break;
            }
            disk[counter++] = data[temp++];
        }
    }

    for (int i = 0; i < 130; i++) {
        blkIndex = i/blockSize;
        if (i == dirBlock*blockSize) { //print disk
            printf("\n");
        }
        printf("\nindex: %i | block: %i | data: %i ", i, blkIndex, disk[i]);
    }

    return 0;
}