#include <stdio.h>
#define PAGESIZE 22
char *progname; /* program name for error message */

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
    FILE *efopen();
    static FILE *tty = NULL;

    if (tty == NULL)
        tty = efopen("/dev/tty", "r");
    if (fgets(buf, BUFSIZ, tty) == NULL || buf[0] == 'q')
        exit(0);
    else /* ordinary line */
        return buf[0];
}

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

int main(int argc, char *argv[])
{
    int i, pagesize = PAGESIZE;
    FILE *fp, *efopen();

    printf("arg cnt : %d, first arg : %s \n", argc, argv[1]);
    progname = argv[0];
    if (argc > 1 && argv[1][0] == '-') /* p -n ... */
    { /* print input in chunks (version 2) */
        pagesize = atoi(&argv[1][1]);
        printf(">>> page size : %d\n", pagesize);
        argc--;
        argv++;
    }

    if (argc == 1)
    {
        print(stdin, pagesize);
    }
    else
    {
        for (i = 1; i < argc; i++)
        {
            fp = efopen(argv[i], "r");
            print(fp, pagesize);
            fclose(fp);
        }
    }

    exit(0);
}