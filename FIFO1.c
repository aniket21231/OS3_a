#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

void genStr(char arr[50][11]){
    srand((unsigned int)(time(NULL)));
    char chars[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/,.-+=~`<>:";
    for(int i=0;i<50;i++){
        for(int j=0;j<11;j++){
            if(j==0){
                ar[i][j]=i;
            }
            arr[i][j]=chars[rand()%(sizeof(chars)-1)];
        }
    }
}


int main(){
    struct timespec start,end;
    long long int f1,f2;
    int indexlst=1;
    char * fifo_1,fifo_2;

    char str[50][11];
    
    fifo_1="FIFO_1";
    mkfifo(fifo_1,0666);
    char BUFFER[100];
    genStr(str);
   
    fifo_2="FIFO_2";
    mkfifo(fifo_2,0666);
    int temp;
    while(true){
        clock_gettime(CLOCK_REALTIME, &start);
        if(f1==-1){
            perror("Error occured in accessing FIFO_1");
            
        }
        for(int l=indexlst;l<indexlst+5;l++){
            f1=open(fifo_1,O_WRONLY);
            temp=write(f1,str[l],sizeof(str[l]+1));
            sleep(1);
            close(f1);

        }
        f2=open(fifo_2,O_RDONLY);
        temp=read(f2,BUFFER,100);
        close(f2);

        if(temp==-1){
            perror("Error in reading FIFO_2");
            return 1;

        }
        int indexf=atoi(BUFFER);
        indexlst=indexf+1;
        printf("Maximun ID received:%s \n",BUFFER);

    }
    clock_gettime(CLOCK_REALTIME, &end);
    double fifo_time=(((end.tv_sec - start.tv_sec) * 1000000000) +(end.tv_nsec - start.tv_nsec))/1000000000.0;
    prtinf("The time is %lf\n",fifo_time);
    return 0;

}

