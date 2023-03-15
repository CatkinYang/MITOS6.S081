/*************************************************************************
 > File Name: sleep.c
 > Author: Catkin 
 > Created Time: Wed Mar 15 20:33:00 2023
 ************************************************************************/

#include "kernel/types.h" 
#include "kernel/stat.h" 
#include "user/user.h"

int main(int argc, char* argv[])
{
    int i;
    if(argc < 2)
    {
        fprintf(2,"sleep for some time...\n");
        exit(1);
    }
    for(i=1;i<argc;i++)
    {
        int n = atoi(argv[1]);
        sleep(n);
        fprintf(2,"sleep for %d\n",n);
    }
    exit(0);
}
