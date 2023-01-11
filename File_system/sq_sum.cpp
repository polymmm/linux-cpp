#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int main()
{
    int fd;
    struct nums
    {
        long f;
        long f2;
    } *ptr, *tmp;
    long long sum;

    fd = open("mapped.dat", O_RDWR | O_CREAT, 0666);
    ftruncate(fd, 100000 * sizeof(struct nums));
    ptr = (struct nums *) mmap(NULL, 100000 * sizeof(struct nums), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    tmp = ptr;
    for (int i = 1; i < 100001; i++)
    {
        tmp->f = i;
        tmp->f2 = i * i;
        sum += tmp->f2;
        tmp++;
    }
    munmap((void *) ptr, 100000 * sizeof(struct nums));
    printf("%lld\n", sum);
}