#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "ttyin.h"

char *progname;      /*programe name for error message */
char *ps = "ps -a"; /* system dependent */ // "ps -ag"

int strindex(char *s, char *t)
{
    int i, n;
    n = strlen(t);
    for (i = 0; s[i] != '\0'; i++)
        if (strncmp(s + i, t, n) == 0)
            return i;

    return -1;
}

int main(int argc, char *argv[])
{
    FILE *fin, *popen();
    char buf[BUFSIZ];
    int pid;

    progname = argv[0];
    if ((fin = popen(ps, "r")) == NULL)
    {
        fprintf(stderr, "%s: can't run %s\n", progname, ps);
        exit(1);
    }
    fgets(buf, sizeof(buf), fin); /* get header line */
    fprintf(stderr, "%s", buf);
    while (fgets(buf, sizeof(buf), fin) != NULL)
    {
        if (argc == 1 || strindex(buf, argv[1]) >= 0)
        {
            buf[strlen(buf) - 1] = '\0';
            fprintf(stderr, "%s? ", buf);
            if (ttyin() == 'y')
            {
                sscanf(buf, "%d", &pid);
                kill(pid, SIGKILL);
            }
        }
    }
    exit(0);
}
