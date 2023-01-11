#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

void _ls(const char *dir, int op_a, int op_l)
{
    struct dirent *d;
    DIR *dh = opendir(dir);
    if (!dh)
    {
        if (errno == ENOENT)
        {
            perror("Directory doesn't exist");
        }
        else
        {
            perror("Unable to read directory");
        }
        exit (EXIT_FAILURE) ;
    }
    while ((d = readdir(dh)) != NULL)
    {
        if (!op_a && d->d_name[0] =='.')
            continue;
        printf("%s ", d->d_name);
        if(op_l) printf ("\n");
    }
}


int main(void)
{
    _ls(".",0,1);
    return 0;
}
