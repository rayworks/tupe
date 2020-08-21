#include <stdio.h>
#include <stdlib.h>

#include "ttyin.h"

#define PAGESIZE 22
char *progname; /* program name for error message */

int main(int argc, char *argv[])
{
    int i, pagesize = PAGESIZE;
    FILE *fp, *efopen();

    printf("arg cnt : %d, first arg : %s \n", argc, argv[1]);
    progname = argv[0];
    if (argc > 1 && argv[1][0] == '-') /* p -n ... */
    {                                  /* print input in chunks (version 2) */
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