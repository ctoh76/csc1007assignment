#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TB 100
#define FILESIZE 100
FILE *fp;
typedef struct{
      char func[6];//to read add, read, delete based on first letter
      int filename;
      int data[FILESIZE];
}data;

int readFile(); 
void allocate();
void deallocate();
void display();
int BFull();
struct Link
{
    char n[30];
    int len;
    int st;
    struct node
    {
        int index;
        struct node *next;
    }*Start,*current,*newnode,*temp;
}F[30];
int Table[TB+1],pos=0,r,i,j,ch,B=0;
char fn[30];
int i = 0;
data d[10];//basically able to read 10 lines so got 10 different set of data
//Reading file 
int readFile(){

   char file_name[25];
  
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

   //Function: add -> func
   //FileName:100 -> filename
   //Data: The length of the data ->data
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


int main()
{
     printf("\n Linked File Allocation \n\n");
     readFile();
     for(int c= 0; c < i;c++){
     char *function = d[c].func;
     switch(*function)
     {
                case 'a':
                    printf("\nChoice add");
                    allocate(c);
                    break;

                case 'd':
                    printf("\nChoice delete");
                    deallocate(c);
                    break;

                case 'r':
                    printf("\nChoice display");
                    display(c);
                    break;

                default:
                    printf("\nInvalid Choice");
        }
     }

}

//add
void allocate(int index)
{
   printf("\nFilename:%d:",d[index].filename);
  // printf("\nFile Length : ");
  //scanf("%d",&(F[pos].n));
   //scanf("%d",&(F[pos].len));
   for(int c= 0; c < i;c++){
  int *ptr = d[index].data;
      int size = 0;
      while(*ptr !=0){
         *ptr++;
         size++;
      }
       printf("\nFileLength:%d",d[index].data[size]);
   }
   F[pos].Start=NULL;
   if(BFull())
   {
        pos--;
       printf("\n\nNo Enough Free Space Available \n");
       return;
   }

   for(i=1;i<=F[pos].len;i++)
   {
        F[pos].newnode=(struct node *)malloc(sizeof(struct node));

        while(1)
        {

            r=rand()%TB+1;
            if(Table[r]==0)
            {
                    F[pos].newnode->index =r;
                    F[pos].newnode->next=NULL;
                    if(F[pos].Start==NULL)
                    {
                        F[pos].Start=F[pos].newnode;
                        F[pos].current=F[pos].newnode;
                    }
                    else
                    {
                        F[pos].current->next=F[pos].newnode;
                        F[pos].current=F[pos].newnode;
                    }

                    Table[r]=1;
                    break;
            }
        }
    }
    F[pos].st=F[pos].Start->index;
    for(i=r;i<r+F[pos].len;i++)
        Table[i]=1;
    printf("\n\tFile Allocation Table\n");
    printf("\nFileName\tStart\tEnd\tLength\n");
    for(i=1;i<=pos;i++)
    {
        printf("\n%s\t\t%d\t%d\t%d",F[i].n,F[i].st,F[pos].current->index,F[i].len);
        printf("\n");
    }

}
//delete
void deallocate()
{
   printf("\nEnter The File Name : ");
   scanf("%s",&fn);
   for(i=1;i<=pos;i++)
   {
            if(strcmp(F[i].n,fn)==0)
            {
                F[i].current=F[i].Start;
                while(F[i].current)
                {
                    Table[F[i].current->index]=0;
                    F[i].temp=F[i].current;
                    F[i].current=F[i].current->next;
                    free(F[i].temp);
                }

                strcpy(F[i].n,"NULL");
                F[i].st=0;
                F[i].len=0;
                printf("\nFile (%s) Deleted Successfully \n",fn);
                break;
            }
            else
                printf("\nDeletion Unsuccessful\n");
    }
    printf("\n\t\tFile Allocation Table\n");
    printf("\nFileName\tStart\tLength\n");
    for(i=1;i<=pos;i++)
    {
        printf("\n%s\t\t%d\t%d",F[i].n,F[i].st,F[i].len);
        printf("\n");
    }
}
//read
void display()
{
    printf("\nEnter The File Name : ");
    scanf("%s",fn);
    printf("\nBlocks Allocated Are : ");
    for(i=1;i<=pos;i++)
    {
        if(strcmp(F[i].n,fn)==0)
        {
            F[i].current=F[i].Start;
            while(F[i].current)
            {
               printf(">--%d-->",F[i].current->index);
               F[i].current=F[i].current->next;
            }
            break;
        }
    }
    if(i==pos+1)
    {
        printf("\n\nNo File Found\n");
    }
}
int BFull()
{
    for(i=1,B=0;i<=pos;i++)
        B=B+F[i].len;
    if(B>TB)
        return 1;
    else
        return 0;
}