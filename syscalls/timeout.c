#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "err.h"

int pid; /* child process id */
char *progname;

void onalarm() /* kill child when alarm arrived */
{
    printf(">>> onalarm : kill process\n");
    kill(pid, SIGKILL);
}

int main(int argc, char const *argv[])
{
    int sec = 10, status;

    progname = argv[0];
    if (argc > 1 && argv[1][0] == '-')
    {
        sec = atoi(&argv[1][1]);
        argc--;
        argv++;
    }
    if (argc < 2)
        error("Usage : %s [-10] command ", progname);
    if ((pid = fork()) == 0)
    {
        // sleep(12);

        execvp(argv[1], &argv[1]);
        error("Couldn't start %s", argv[1]);
    }
    signal(SIGALRM, onalarm);
    alarm(sec);

    if (wait(&status) == -1 || (status & 0177) != 0)
    {
        error("%s killed", argv[1]);
    }

    return ((status >> 8) & 0377);
}
