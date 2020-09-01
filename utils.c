
#include "philo_one.h"

t_parameters	*copy_parameters(t_parameters *parameters)
{
	t_parameters	*copy;

	if (!(copy = malloc(sizeof(t_parameters))))
		return (NULL);
	copy->number_of_philosophers = parameters->number_of_philosophers;
	copy->time_to_die = parameters->time_to_die;
	copy->time_to_eat = parameters->time_to_eat;
	copy->time_to_sleep = parameters->time_to_sleep;
	copy->number_of_time_each_philosophers_must_eat =
parameters->number_of_time_each_philosophers_must_eat;
	if (!(copy->time_start = malloc(sizeof(struct timeval))))
	{
		free(copy);
		return (NULL);
	}
	copy->time_start->tv_sec = parameters->time_start->tv_sec;
	copy->time_start->tv_usec = parameters->time_start->tv_usec;
	return (copy);
}


void			fill_msg(char *msg, char **ptr)
{
	while (*msg)
		*(*ptr)++ = *msg++;
}

void			fill_nbr(size_t nbr, char **ptr)
{
	char			c;
	size_t			nnbr;
	long long int	pow;

	pow = 10;
	nnbr = nbr;
	while (nnbr /= 10)
		pow *= 10;
	while ((pow /= 10))
	{
		c = (nbr / pow) % 10 + '0';
		*(*ptr)++ = c;
	}
}

size_t			ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s && ++i)
		s++;
	return (i);
}

int				ft_atoi(char *str)
{
	int		nb;

	if (*str == '\0')
		return (-1);
	nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		nb = 10 * nb + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (nb);
}
