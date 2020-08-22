#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "err.h"

char *progname;

int main(int argc, char const *argv[])
{
    int fd;
    struct stat stbuf;
    time_t old_time = 0;
    progname = argv[0];

    if (argc < 2)
        error("can't open %s", argv[1]);
    fstat(fd, &stbuf);
    while (stbuf.st_mtimespec.tv_sec != old_time)
    {
        old_time = stbuf.st_mtimespec.tv_sec;
        sleep(60);
        fstat(fd, &stbuf);
    }
    if (argc == 2)
    { 
        /* copy file */
        execlp("cat", "cat", argv[1], (char*) 0);
        error("can't execute cat %s", argv[1]);
    } else {
        execvp(argv[2], &argv[2]);
        error("can't execute cat %s", argv[2]);
    }

    return 0;
}
