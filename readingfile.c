#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILESIZE 100
FILE *fp;
typedef struct{
      char func[6];//to read add, read, delete based on first letter
      int filename;
      int data[FILESIZE];
}data;

int readFile();
void main()
{
/////////////////////////////////////////////////////////////////
   readFile();/*
   int listLength = 1;
   while((num = fgetc(fp))!= EOF){
      if(num =='\n'){
         listLength++;
      }
   }
   struct data *dt;
   if(dt == NULL){
      printf("Error when allocation mem");
      exit(EXIT_FAILURE);
   }
   int i = 0;
   while(fscanf(fp,"%c %d %d",(dt + i)->func,&(dt + i)->filename,&(dt + i)->data)!= EOF){
      i++;
   }
   printf("%c %d %d \n",(dt)->func,(dt)->filename,(dt)->data);*/
}

int readFile(){

   char file_name[25];
   int i = 0;
   data d[10];//basically able to read 10 lines so got 10 different set of data
   char *token;
   char buff[1024];

   printf("Enter name of a file you wish to see\n");
   gets(file_name);

   fp = fopen(file_name, "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");//if file does not exist
      exit(EXIT_FAILURE);
   }
   while (fgets(buff, sizeof(buff), fp))
   {
      int j = 0;
      token = strtok(buff, ",");
      strcpy(d[i].func, token);
      token = strtok(NULL, ",");
      d[i].filename = atoi(token);
      token = strtok(NULL, ",");
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

   for(int c= 0; c < i;c++){
      printf("\nFunction:--%s--Filename:--%d--Data:",d[c].func,d[c].filename);
      int *ptr = d[c].data;
      int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
      }
      for(int k = 0; k < size; k++){//2 instead of size idk le la i fked up
         printf("%d,",d[c].data[k]);
      }
   }
   
   fclose(fp);

   return 0;

}
