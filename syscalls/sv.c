#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "err.h"

char *progname;

void sv(char *file, char *dir)
{
    struct stat sti, sto;
    int fin, fout, n;
    char target[BUFSIZ], buf[BUFSIZ];

    sprintf(target, "%s/%s", dir, file);
    if (strchr(file, '/') != NULL)
        error("won't handle /'s in %s", file);
    if (stat(file, &sti) == -1)
        error("can't stat %s", file);
    if (stat(target, &sto) == -1) /* target not present */
    {
        struct timespec ts;
        ts.tv_nsec = 0;
        ts.tv_sec = 0;

        sto.st_mtimespec = ts; /* so make it look old */
    }
    if (sti.st_mtimespec.tv_sec < sto.st_mtimespec.tv_sec) /* target is newer */
        fprintf(stderr, "%s : %s not copied\n", progname, file);
    else if ((fin = open(file, 0)) == -1)
        error("can't open file %s", file);
    else if ((fout = creat(target, sti.st_mode)) == -1)
        error("can't create %s", target);
    else
    {
        while ((n = read(fin, buf, sizeof(buf))) > 0)
        {
            if (write(fout, buf, n) != n)
                error("error writing %s", target);
        }
    }
    close(fin);
    close(fout);
}

int main(int argc, char const *argv[])
{
    int i;
    struct stat stbuf;
    char *dir = argv[argc - 1];
    progname = argv[0];

    if (argc <= 2)
        error("Usage : %s files ... dir", progname);
    if (stat(dir, &stbuf) == -1)
        error("can't access directory %s", dir);
    if ((stbuf.st_mode & S_IFMT) != S_IFDIR)
        error("%s is not a directory", dir);

    for (i = 1; i < argc - 1; i++)
        sv(argv[i], dir);

    return 0;
}
