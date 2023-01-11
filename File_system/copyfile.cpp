#include <fcntl.h>
#include <unistd.h>

int main()
{
    int old_fd, new_fd;
    old_fd = open("copyfile.cpp", O_RDONLY);
    new_fd = creat("output.txt", 0666);
    char buf[271];
    read(old_fd, buf, 271);
    write(new_fd, buf, 271);
    close(old_fd);
    close(new_fd);
}