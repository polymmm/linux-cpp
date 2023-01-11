#include <signal.h>
#include <unistd.h>

void my_handler(int nsig)
{
    if (nsig==2)
    {
        write(STDOUT_FILENO, "Receive signal 2, CTRL-C pressed\n", 34);
    }
    else
    {
        write(STDOUT_FILENO, "Receive signal 4, CTRL-4 pressed\n", 34);
    }
}

int main(void)
{
    (void) signal (SIGINT, my_handler);
    (void) signal (SIGQUIT, my_handler);
    while(1);
    return 0;
}