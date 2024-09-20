#include "minitalk.h"

void    signal_handler(int sig)
{
    static int bits_receved;
    static char c;

    bits_receved++;
    c = c << 1;
    if (sig == SIGUSR1)
        c = c | 1 ;
    if (bits_receved == 8 )
    {
        ft_putchar(c);
        bits_receved = 0;
        c = 0;
    }
    


}

int main(void)
{
    pid_t pid;

    pid = getpid();
    ft_putstr("Serveur PID :");
    ft_putnbr((long)pid);
    ft_putstr("\n");
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    while (1)
    {
        pause();
    }
    

    return 0;
}
