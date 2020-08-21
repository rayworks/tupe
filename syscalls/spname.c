#include <sys/types.h>
#include <sys/dir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <dirent.h>

#include "../progio/ttyin.h"

#define EQ(s, t) (strcmp(s, t) == 0)
#define DIR_SIZE 255
#define PAGESIZE 22

char *progname;

int spdist(char *s, char *t)
{
    while (*s++ == *t)
        if (*t++ == '\0')
            return 0; /* exact match */
    if (*--s)
    {
        if (*t)
        {
            if (s[1] && t[1] && *s == t[1] && *t == s[1] && EQ(s + 2, t + 2))
                return 1; /* transposition */

            if (EQ(s + 1, t + 1))
                return 2; /* 1 char mismatch */
        }
        if (EQ(s + 1, t))
            return 2; /* extra character */
    }
    if (*t && EQ(s, t + 1))
        return 2; /* missing character */
    return 3;
}

int mindist(char *dir, char *guess, char *best)
{
    /* Set best, return distance 0..3 */
    int d, nd, fd;
    if (dir[0] == '\0')
    {
        dir = ".";
    }
    d = 3; // minimum distance

    // reimplemented according to AUPE 3e
    struct dirent *dirp;
    DIR *pd = opendir(dir);
    if (pd != NULL)
    {
        while ((dirp = readdir(pd)) != NULL)
        {
            if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 || strcmp(dirp->d_name, ".DS_Store") == 0)
                continue;

            dirp->d_name[dirp->d_namlen + 1] = '\0';
            printf(">>> dir name : %s\n", dirp->d_name);

            nd = spdist(dirp->d_name, guess);
            if (nd <= d && nd != 3)
            {
                strcpy(best, dirp->d_name);

                d = nd;
                if (d == 0) // exact match
                    break;
            }
        }

        closedir(pd);
    }

    return d;
}

int spname(char *oldname, char *newname)
{
    char *p, guess[DIR_SIZE + 1], best[DIR_SIZE + 1];
    char *new = newname, *old = oldname;

    for (;;)
    {
        printf(" >>> old starts with %c \n", *old);
        while ((*old) == '/')
            *new ++ = *old++;
        *new = '\0';
        if (*old == '\0')
        {
            return strcmp(oldname, newname) != 0;
        }
        p = guess;
        for (; *old != '/' && *old != '\0'; old++)
        {
            if (p < guess + DIR_SIZE)
                *p++ = *old;
        }
        *p = '\0';

        printf(">>> input newname : %s, guess : %s, best: %s\n", newname, guess, best);
        if (mindist(newname, guess, best) >= 3)
        {
            printf("best : %s\n", best);
            return -1;
        }
        printf("best rest: %s\n", best);

        for (p = best; *new = *p++;) /* add to end of newname */
            new ++;
    }
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    int i, pagesize = PAGESIZE;
    char *p, buf[BUFSIZ];

    progname = argv[0];
    if ((p = getenv("PAGESIZE")) != NULL)
        pagesize = atoi(p);

    if (argc > 1 && argv[1][0] == '-')
    {
        pagesize = atoi(&argv[1][1]);
        argc--;
        argv++;
    }
    if (argc == 1)
        print(stdin, pagesize);
    else
        for (i = 1; i < argc; i++)
        {
            printf(">>> target file : %s\n", argv[i]);

            int r = spname(argv[i], buf);
            printf(">>> spname returns %d\n", r);
            switch (r)
            {
            case -1: /* no match possible */
                fp = efopen(argv[i], "r");
                print(fp, pagesize);
                fclose(fp);
                break;
            case 1: /* correct */
                fprintf(stderr, "\"%s\"? ", buf);
                if (ttyin() == "n")
                    break;
                argv[i] = buf;
                /* fall through ... */
            case 0:
                fp = efopen(argv[i], "r");
                print(fp, pagesize);
                fclose(fp);
            }
        }

    return 0;
}