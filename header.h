#include <stdio.h>
#include <stdlib.h>
#ifndef MAIN_H
#define MAIN_H

#define MAX 130//define max size of data able to store
struct data{ //Struct created to read in function require, filename, data able to hold
      char func[6];//to read add, read, delete based on first letter
      int filename;
      int data[MAX];
}d[MAX];

int indexf[MAX], block[MAX], dataf[MAX],startLoc[MAX],endLoc[MAX] , bitmap[MAX], freed[MAX];
int count1;
int noOfBlock = 0 , temp2 = 0;
#endif
//extern data d;//130 set of data able to read

