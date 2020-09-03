
#include "philo.h"

int			exit_error(int ret)
{
	if (ret == -1)
		ft_putstr("philo : error arguments\n");
	if (ret == -2)
		ft_putstr("philo : error malloc\n");
	if (ret == -3)
		ft_putstr("philo : too many or too few arguments\n");
	if (ret == -4)
		ft_putstr("philo : error malloc philosophers\n");
	return (0);
}

char		*get_message(int type)
{
	if (type == TYPE_EAT)
		return (" \033[31m is eating \033[0m\n");
	else if (type == TYPE_SLEEP)
		return (" \033[32m is sleeping \033[0m\n");
	else if (type == TYPE_FORK)
		return (" \033[34m has taken a fork \033[0m\n");
	else if (type == TYPE_THINK)
		return (" \033[33m is thinking \033[0m\n");
	else if (type == TYPE_OVER)
		return ("must eat count reached\n");
	return (" died\n");
}

int			display_message(t_philo *philo, int type)
{
	static int	done = 0;
	int			ret;

	if (sem_wait(philo->state->mu->write_m) != 0)
		return (1);
	ret = 1;
	if (!done)
	{
		ft_putnbr_fd(get_time() - philo->state->mu->start);
		write(1, "m", 1);
		write(1, "s", 1);
		write(1, "\t", 1);
		if (type != TYPE_OVER)
			ft_putnbr_fd(philo->position + 1);
		if (type >= TYPE_DIED)
			done = 1;
		write(1, get_message(type), ft_strlen(get_message(type)));
		ret = 0;
	}
	if (sem_post(philo->state->mu->write_m))
		return (1);
	return (ret);
}
