/* cat : minimal version */
#define SIZE 512
#include <stdio.h>
#include <unistd.h>

int main()
{
    char buf[SIZE];
    int n;

    while ((n = read(0, buf, sizeof(buf)) > 0))
    {
        write(1, buf, n);
    }

    return 0;
}
