#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILESIZE 1000
FILE *fp;
typedef struct{
      char func[6];//to read add, read, delete based on first letter
      int filename;
      int data[FILESIZE];
}data;
data d[10];//basically able to read 10 lines so got 10 different set of data
int i = 0,pos = 0,Table[FILESIZE],r,a,b, fsize;
int readFile();
void add();
void read();
void delete();
int freeMem();

int readFile(){

   char file_name[25];
   char *token;
   char buff[1024];

   printf("Please Enter your desired csv file\n");
   gets(file_name);

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
void main()
{
   printf("\n Contiguous File Allocation \n\n");
   readFile();
   for(int c= 0; c < i;c++){
      char *function = d[c].func;//d[1].func
      switch(*function){
         case 'a':
         case 'A':
            printf("\naddpart1\n");
            fsize = d[0].filename + FILESIZE;
            add(c);
            break;
         case 'r':
         case 'R':
            printf("\nreadpart1\n");
            read(c);
            break;
         case 'd':
         case 'D':
            printf("\ndeletepart1\n");
            delete(c);
            break;
         default:
            printf("whycometildefault");
            break;
      }
   }
}
void add(int index){
   printf("%d",d[index].filename);
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
   printf("\n--went into read function--");
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
      if(strcmp("read",d[c].func)!=0 && d[c].filename != 0){
         printf("\nFilename: %d Data: ", d[c].filename);
         for(int k = 0; k < size; k++){
            printf("%d,",d[c].data[k]);
         }
      }
   }
   printf("--went into delete function--");
}
int freeMem(){
    return 0;
}