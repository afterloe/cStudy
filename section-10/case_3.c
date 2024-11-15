#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid, ppid, pgid;

    pid = getpid();

    ppid = getppid();

    pgid = getpgrp();

    printf("pid = %d \n", pid);
    printf("ppid = %d \n", ppid);
    printf("pgid = %d \n", pgid);

    return 0;
}