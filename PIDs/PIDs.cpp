#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

void print_pid_ppid()
{
    std::cout << getpid() << "\n" << getppid() << "\n";
}

void equal_action()
{
    int a=0;
    fork();
    a++;
    std::cout << getpid() << "\n" << getppid() << "\n" << a << "\n";
}

void diff_action()
{
    if (fork()==0)
    {
        std::cout << "Child process\n" << getpid() << "\n" << getppid() << "\n";
    }
    else
    {
        std::cout << "Parent process\n" << getpid() << "\n" << getppid() << "\n";
    }
}

void print_vars_args(int argc, char *argv[], char *envp[])
{
    int i=0;
    while (argv[i])
    {
        std::cout << argv[i] << " ";
        i++;
    }
    std::cout << "\n";
    i=0;
    while (envp[i])
    {
        std::cout << envp[i] << "\n";
        i++;
    }
}

void child_start(char *envp[])
{
    if (fork()==0)
    {
        std::cout << "Child process\n" << getpid() << "\n" << getppid() << "\n";
        execle("/home/polym/Desktop/2", "2", (char *)NULL, envp);
    }
    else
    {
        std::cout << "Parent process\n" << getpid() << "\n" << getppid() << "\n";
    }
}

void parent_sync(char *envp[])
{
    int sync=1;
    if (fork()==0)
    {
        execle("/home/polym/Desktop/2", "2", (char *)NULL, envp);
    }
    else
    {
        if (sync)
        {
            wait(0);
            std::cout << "Parent process\n" << getpid() << "\n" << getppid() << "\n";
        }
    }
}

int main(int argc, char *argv[], char *envp[])
{
    int x;
    std::cout << "Choose num:\n";
    point:
    std::cout << "1: Print PID/PPID\n2: Do equal action\n3: Do different action\n4: Print vars & args\n5: Child starts a programm\n6: Parent synchronization\n";
    std::cin >> x;
    switch (x)
    {
        case 1: std::cout << "\n"; print_pid_ppid(); std::cout << "\n"; goto point;
        case 2: std::cout << "\n"; equal_action(); std::cout << "\n"; goto point;
        case 3: std::cout << "\n"; diff_action(); std::cout << "\n"; goto point;
        case 4: std::cout << "\n"; print_vars_args(argc, argv, envp); std::cout << "\n"; goto point;
        case 5: std::cout << "\n"; child_start(envp); std::cout << "\n"; goto point;
        case 6: std::cout << "\n"; parent_sync(envp); std::cout << "\n"; goto point;
        case 0: exit(0);
        default: goto point;
    }
}
