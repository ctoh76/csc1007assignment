#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TB 100
#define FILESIZE 100
FILE *fp;
typedef struct{
      char func[6];//to read add, read, delete based on first letter -->n 
      int filename; //-->len
      int data[FILESIZE];
      int st;
    struct node
    {
        int index;
        struct node *next;
    }*Start,*current,*newnode,*temp;
}data;
data d[10];//basically able to read 10 lines so got 10 different set of data

int readFile(); 
void allocate();
void deallocate();
//void display();
int BFull();

int Table[TB+1],pos=0,r,i,j,ch,B=0;
char fn[30];


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
      printf("\n%d\n",size);
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
                    //display(c);
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
 
    int *ptr = d[index].data;
    int size = 0;
    while(*ptr !=0){
         *ptr++;
         size++;
      }
    printf("\nFileLength:%d",size);
     
    d[pos].Start=NULL;
    /*
   if(BFull())
   {
       pos--;
       printf("\n\nNo Enough Free Space Available \n");
       return;
   }
   */

   for(i=1;i<=size;i++)
   {
        d[pos].newnode=(struct node *)malloc(sizeof(struct node));

        while(1)
        {

            r=rand()%TB+1;
            if(Table[r]==0)
            {
                    d[pos].newnode->index =r;
                    d[pos].newnode->next=NULL;
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

                    Table[r]=1;
                    break;
            }
        }
    }
    d[pos].st=d[pos].Start->index;
    printf("\nHi :%d",d[pos].st);
    for(i=r;i<r+size;i++)
        Table[i]=1;
    printf("\n\tFile Allocation Table\n");
    printf("\nFileName\tStart\tEnd\tLength\n");
    printf("\n%d\t\t%d\t%d\t%d",d[index].filename,d[pos].st,d[pos].current->index,size);
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
void deallocate(int index)
{
   printf("\nFileName that to delete:",d[index].filename);
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
    }*/
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
        B=B+d[i].size;
    if(B>TB)
        return 1;
    else
        return 0;
}

