/*************************************************************************
 > File Name: pingpongtest.c
 > Author: Catkin 
 > Created Time: Sun Jun 11 14:50:05 2023
 ************************************************************************/

#include "kernel/types.h" 
#include "kernel/stat.h" 
#include "user/user.h"
#define R 0
#define W 1
int main(int argc, char* argv[])
{
    char buf = 'P';
    int fdctop[2];
    int fdptoc[2];
    pipe(fdctop);
    pipe(fdptoc);
    int pid = fork();
    if(pid == 0)//child process
    {
        close(fdctop[R]);
        close(fdptoc[W]);
        read(fdptoc[R],&buf,1);
        printf("%d: received ping\n",getpid());
        sleep(1);
        write(fdctop[W],&buf,1);
        close(fdctop[W]);
        close(fdptoc[R]);
    }
    else if (pid > 0)//parent process
    {
        close(fdptoc[R]);
        close(fdctop[W]);
        write(fdptoc[W],&buf,1);
        read(fdctop[R],&buf,1);
        printf("%d: received pong\n",getpid());
        close(fdctop[R]);
        close(fdptoc[W]);
    }
    return 0;
}
