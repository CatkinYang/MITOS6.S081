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
    int fdptoc[2];//parent write to child
    int fdctop[2];//child write to parent
    pipe(fdptoc);
    pipe(fdctop);
    char buf = 'P';
    int pid = fork();
    if(pid == 0)//child
    {
        close(fdctop[RD]);
        close(fdptoc[WR]);
        write(fdctop[WR],&buf,1);
        fprintf(2,"%d: received ping\n",getpid());
        close(fdptoc[RD]);
        close(fdctop[WR]);
    }
    else//parent
    {
        close(fdctop[WR]);
        close(fdptoc[RD]);
        write(fdptoc[WR],&buf,1);
        sleep(1);
        fprintf(2,"%d: received pong\n",getpid());
        close(fdptoc[WR]);
        close(fdctop[RD]);
    }
    return 0;
}
