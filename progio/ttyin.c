#include "ttyin.h"

void print(FILE *fp, int pagesize)
{
    static int lines = 0;
    char buf[BUFSIZ];

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        if (++lines < pagesize)
            fputs(buf, stdout);
        else
        {
            buf[strlen(buf) - 1] = '\0';
            fputs(buf, stdout);
            fflush(stdout);
            ttyin();
            lines = 0;
        }
    }
}

FILE *efopen(char *file, char *mode)
{
    FILE *fp;
    extern char *progname;

    if ((fp = fopen(file, mode)) != NULL)
        return fp;
    fprintf(stderr, "%s: can't open file %s mode %s\n", progname, file, mode);
    exit(1);
}

char ttyin() /* process response from /dev/tty (version 1) */
{
    char buf[BUFSIZ];
    static FILE *tty = NULL;

    if (tty == NULL)
        tty = efopen("/dev/tty", "r");
    if (fgets(buf, BUFSIZ, tty) == NULL || buf[0] == 'q')
        exit(0);
    else /* ordinary line */
        return buf[0];
}