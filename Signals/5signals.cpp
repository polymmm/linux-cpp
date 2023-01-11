#include <signal.h>
#include <unistd.h>

int i_sigint=0;
int i_sigquit=0;

void my_handler(int nsig)
{
    if (nsig==2)
    {
        write(STDOUT_FILENO, "Receive signal 2, CTRL-C pressed\n", 34);
        i_sigint = i_sigint + 1;
        if (i_sigint == 5) (void) signal(SIGINT, SIG_DFL);
    }
    else
    {
        write(STDOUT_FILENO, "Receive signal 4, CTRL-4 pressed\n", 34);
        i_sigquit = i_sigquit + 1;
        if (i_sigquit == 2) (void) signal(SIGQUIT, SIG_DFL);
    }
}

int main(void)
{
    signal(SIGINT, my_handler);
    signal(SIGQUIT, my_handler);
    while(1);
    return 0;
}