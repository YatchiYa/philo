
#include "philo_one.h"

int		throw_error(int error)
{
	if (error == TOO_MANY_ARGS)
		msg_error("Error: Wrong number of arguments\n");
	else if (error == WRONG_ARG)
		msg_error("Error: Wrong argument\n");
	else if (error == ERROR_MALLOC)
		msg_error("Error: malloc error\n");
	else if (error == ERROR_MUTEX)
		msg_error("Error: mutex error\n");
	else if (error == ERROR_PTHREAD)
		msg_error("Error: pthread error\n");
	else if (error == ERROR_SLEEP)
		msg_error("Error: usleep error\n");
	else if (error == ERROR_TIMEOFDAY)
		msg_error("Error: gettimeofday error\n");
	return (error);
}

void	msg_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

int		clean_all(t_philo_one *philos)
{
	void			*tmp2;
	t_philosopher	*tmp;

	tmp = (philos) ? philos->philosophers : NULL;
	while (tmp)
	{
		tmp2 = tmp->next;
		clean_philosopher(tmp);
		tmp = tmp2;
	}
	if (philos && philos->parameters)
		free(philos->parameters->time_start);
	if (philos)
		free(philos->parameters);
	return (0);
}

void	clean_philosopher(t_philosopher *philos)
{
	if (philos->parameters)
		free(philos->parameters->time_start);
	free(philos->parameters);
	if (philos->left_fork && philos->left_fork->fork && pthread_mutex_destroy(philos->left_fork->fork))
		throw_error(ERROR_MUTEX);
	if (philos->left_fork)
		free(philos->left_fork->fork);
	free(philos->left_fork);
	if (philos->lock_last_meal && pthread_mutex_destroy(philos->lock_last_meal))
		throw_error(ERROR_MUTEX);
	free(philos->lock_last_meal);
	free(philos->thread);
	free(philos->time_last_meal);
	free(philos);
}

