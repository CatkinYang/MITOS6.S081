/*************************************************************************
 > File Name: user/primes1.c
 > Author: Catkin 
 > Created Time: Wed Mar 22 15:29:57 2023
 ************************************************************************/

#include "kernel/types.h" 
#include "kernel/stat.h" 
#include "user/user.h"
#define RD 0
#define WR 1
//递归筛选出2-35的素数
//每次读到的数不能被当前进程负责筛选的整除就传给右邻居
//第一个不能被当前整除的就是素数并且创建一个新的子进程负责筛选他的倍数
//直接创建一个管道，用来输入2
//递归
void readAndWrite(int *readpipe)
{
    int num;
    close(readpipe[WR]);
    read(readpipe[RD],&num,sizeof(num));
    if(num == -1) exit(0);
    printf("prime %d\n",num);

    int npfd[2];
    pipe(npfd);

    int pid = fork();
    if(pid > 0)
    {
        close(npfd[RD]);
        close(readpipe[WR]);
        int temp;
        while(read(readpipe[RD],&temp,sizeof(int)))
        {
            if(temp%num!=0)
            {
                write(npfd[WR],&temp,sizeof(int));
            }
        }
        temp = -1;
        write(npfd[WR],&temp,sizeof(int));
        wait(0);
        exit(0);
    }
    else if (pid == 0)
    {
        close(npfd[WR]);
        readAndWrite(npfd);
    }

}
int main(int argc, char* argv[])
{
    int ffd[2];
    pipe(ffd);//the first pipe
    
    int pid = fork();
    if(pid == 0)//child
    {
        close(ffd[WR]);
        readAndWrite(ffd);
    }
    else if (pid > 0)
    {
        close(ffd[RD]);
        for(int i=2;i<=35;i++)
            write(ffd[WR],&i,sizeof(i));
        int i = -1;
        write(ffd[WR],&i,sizeof(int));
        close(ffd[WR]);
    }
    wait(0);
    return 0;
}
