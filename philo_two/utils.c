
#include "philo.h"

void				ft_putstr(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

int					ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int					ft_atoi(char *str)
{
	char	*s;
	int		sign;
	int		n;

	s = (char*)str;
	sign = 1;
	n = 0;
	while (*s == ' ' || *s == '\t'
			|| *s == '\n' || *s == '\r' || *s == '\v' || *s == '\f')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		n = n * 10 + (*s++ - '0');
	return (sign * n);
}

size_t				get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}

void				ft_putnbr_fd(size_t n)
{
	char	str[13];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(1, &str[length--], 1);
}
