
#include "minitalk.h"

void    send_char(int pid, char c)
{
    int shift;
    int i;

    i = 7;
    while (i >= 0)
    {
        shift = 1 << (i);
        if (shift & c)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(500);
        i--;
    }
    
}

int main(int ac, char **av)
{
    int i ;

    pid_t pid;

    if (ac != 3)
        return(ft_putstr("Enter a valid ARGS"), 0);
    pid = ft_atoi(av[1]);
    if (pid == 0)
        return(ft_putstr("Invalid PID:\n"), 0);
    i = 0;
    while (av[2][i])
    {
        send_char(pid, av[2][i]);
        i++;
    }
    
    send_char(pid, '\0');
    
    return 0;
}
