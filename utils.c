#include "minitalk.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		ft_putchar(*s);
		s++;
	}
}

long	ft_atoi(char *str)
{
	int	m;
	long	nmb;

	m = 1;
	nmb = 0;
	if (*str == '-')
	{
		m *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nmb = nmb * 10;
		nmb += *str - '0';
		str++;
	}
	nmb = nmb * m;
	return (nmb);
}

void	ft_putnbr(long n)
{
	if (n < 0)
	{
		n = n * -1;
		ft_putchar('-');
		ft_putnbr(n);
	}
	else if (n >= 0 && n <= 9)
	{
		ft_putchar((n + 48));
		return ;
	}
	else if (n > 9)
	{
		ft_putnbr((n / 10));
		ft_putchar((48 + n % 10));
	}
}