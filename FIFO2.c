#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

void printer(char arr[100]){
    int no1=0;
    int no2=0;
    printf("String sent by P1-");
    for(int i=1;i<12;i++){
        printf("%c",arr[i]);
    }
    printf("\n");
}


int main(){
    
    long long int f1,f2;
    int max=0;
    int cur=0;
    char * fifo_1,fifo_2;

  
    
    fifo_1="FIFO_1";
    mkfifo(fifo_1,0666);
    char BUFFER[100];
    
   
    fifo_2="FIFO_2";
    mkfifo(fifo_2,0666);
    int temp;

    while(true){

        while(cur<max+5){
            f1=open(fifo_1,O_RDONLY);
            temp=read(f1,BUFFER,100);
            close(f1);
            if(temp==-1){
                perror("Error in reading FIFO_1");
                break;
            }
            
            printer(BUFFER);
            cur=BUFFER[0];
            sprintf(BUFFER,"%d",cur);
            printf("Max Index sent by P1: %s\n",BUFFER);


            
        }
        max=cur;
        f2=open(fifo_2, O_WRONLY);
        temp=write(f2,BUFFER,100);
        close(f2);
        if(max>49){
            break;
        }
    }
    return 0;

    
}