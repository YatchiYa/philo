
#include "philo_one.h"

void	unmake_pairs(t_philo_one *phi)
{
	t_philosopher	*temp;
	t_philosopher	*ptr;
	t_philosopher	*odd;
	t_philosopher	*even;

	ptr = phi->philosophers;
	odd = phi->philosophers;
	temp = phi->philosophers->next;
	even = phi->philosophers->next;
	while (ptr)
	{
		if (ptr->nb % 2 && ptr->nb != 1)
		{
			odd->next = ptr;
			odd = odd->next;
		}
		else if (!(ptr->nb % 2) && ptr->nb != 2)
		{
			even->next = ptr;
			even = even->next;
		}
		ptr = ptr->next;
	}
	odd->next = temp;
	even->next = NULL;
}

int		wait_philosophers(t_philo_one *phi)
{
	int				c;
	size_t			nb;
	t_philosopher	*ptr;

	nb = phi->parameters->number_of_time_each_philosophers_must_eat;
	ptr = phi->philosophers;
	while (ptr && !usleep(1000) && (c = (ptr->nb_eat < nb) ? 0 : c + 1) > -2)
		if (!ptr->time_last_meal || !ptr->next)
			ptr = (ptr->time_last_meal &&
			c < phi->parameters->number_of_philosophers) ? phi->philosophers : NULL;
		else
			ptr = ptr->next;
	c = 0;
	ptr = phi->philosophers;
	while (c < phi->parameters->number_of_philosophers)
	{
		if (pthread_mutex_lock(ptr->lock_last_meal))
			return (ERROR_MUTEX);
		c += (!ptr->time_last_meal) ? 1 : !!(ptr->time_last_meal = NULL) + 0;
		if (pthread_mutex_unlock(ptr->lock_last_meal))
			return (ERROR_MUTEX);
		if (!(ptr = ptr->next) && c != phi->parameters->number_of_philosophers)
			ptr = !(c *= 0) ? phi->philosophers : NULL;
	}
	return (0);
}

int		launch_philosophers(t_philo_one *phi)
{
	t_philosopher *ptr;

	if (!(phi->parameters->time_start = malloc(sizeof(struct timeval))))
		return (ERROR_MALLOC);
	gettimeofday(phi->parameters->time_start, NULL);
	ptr = phi->philosophers;
	while (ptr && !(ptr->left_fork->nb_last = 0))
	{
		ptr->right_fork->nb_last = 0;
		if (!(ptr->time_last_meal = malloc(sizeof(struct timeval))))
			return (ERROR_MALLOC);
		ptr->time_last_meal->tv_sec = phi->parameters->time_start->tv_sec;
		ptr->time_last_meal->tv_usec = phi->parameters->time_start->tv_usec;
		ptr->nb_eat = 0;
		ptr->parameters = copy_parameters(phi->parameters);
		if (!(ptr->lock_last_meal = malloc(sizeof(pthread_mutex_t))))
			return (ERROR_MALLOC);
		if (pthread_mutex_init(ptr->lock_last_meal, NULL))
			return (ERROR_MUTEX);
		if (pthread_create(ptr->thread, NULL, &alive, ptr))
			return (ERROR_PTHREAD);
		ptr = ptr->next;
	}
	return ((wait_philosophers(phi) ? ERROR_MUTEX : 0) + usleep(100000));
}
