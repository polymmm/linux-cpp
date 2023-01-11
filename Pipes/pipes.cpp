#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <sys/stat.h>

void file_output()
{
    std::ifstream file("/home/polym/Desktop/myfile.txt");
    std::string buff;
    while (std::getline(file, buff))
    {
        std::cout << buff << "\n";
    }
}

void child_ifstr_switch()
{
    if (fork()==0)
    {
        dup2(open("/home/polym/Desktop/myfile1.txt",O_WRONLY | O_CREAT,0666),1);
        std::cout << "Hello world!\n";
    }
    else
    {
        std::cout << "Hello world!\n";
    }
}

void pipe_test()
{
    int fd[2];
    char string[14];
    pipe(fd);
    if (fork())
    {
        close(fd[0]);
        write(fd[1], "ABCDE", 6);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        execl("/home/polym/Desktop/3","3", (char *)NULL);
    }
}

void two_pipes()
{
    int fd1[2], fd2[2];
    char string1[14];
    char string2[14];
    pipe(fd1);
    pipe(fd2);
    if (fork())
    {
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1], "Hello, world!",14);
        close(fd1[1]);
        read(fd2[0],string2,14);
        std::cout << string2 << "\n";
        close(fd2[0]);
    }
    else
    {
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0],string1,14);
        std::cout << string1 << "\n";
        close(fd1[0]);
        write(fd2[1],"Hello, dlrow!",14);
        close(fd2[1]);
    }
}

void conv(char *argv[]) {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        if (fork()) {
            close(fd[1]);
            dup2(fd[0], 0);
            execl("/bin/wc", argv[2], (char *) NULL);
        } else {
            close(fd[0]);
            dup2(fd[1], 1);
            execl("/bin/ls", argv[1], (char *) NULL);
        }
    }
}

void make_fifo()
    {
        mknod("fifo",S_IFIFO|0666,0);
        write(open("fifo",O_WRONLY), "Hello, world!",14);
    }

    int main(int argc, char *argv[])
    {
        //###UNCOMMENT FUNCTION YOU NEED###
        //file_output();
        //child_ifstr_switch();
        //pipe_test();
        //two_pipes();
        //conv(argv);
        //make_fifo();
    }