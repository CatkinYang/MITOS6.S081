/*************************************************************************
 > File Name: ping-pong.c
 > Author: Catkin 
 > Created Time: Wed Mar 15 21:36:55 2023
 ************************************************************************/

#include "kernel/types.h" 
#include "kernel/stat.h" 
#include "user/user.h"
#define RD 0
#define WR 1

int main(int argc, char* argv[])
{
    int fd[2];//parent write to child
    pipe(fd);
    char buf = 'P';
    int pid = fork();
    if(pid == 0)//child
    {
        close(fd[WR]);
        read(fd[RD],&buf,1);
        fprintf(2,"%d: received ping\n",getpid());
        close(fd[RD]);
    }
    else//parent
    {
        close(fd[RD]);
        write(fd[WR],&buf,1);
        sleep(1);
        fprintf(2,"%d: received pong\n",getpid());
        close(fd[WR]);
    }
    return 0;
}
