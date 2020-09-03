
#include "philo.h"

int				eat(t_philo *philo)
{
	if (sem_wait(philo->mutex) != 0)
		return (1);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->par->time_to_die;
	if (display_message(philo, TYPE_EAT))
		return (1);
	usleep(philo->par->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	if (sem_post(philo->mutex))
		return (1);
	if (sem_post(philo->eat_m))
		return (1);
}

int				take_forks(t_philo *philo)
{
	if (sem_wait(philo->state->mu->forks_m))
		return (1);
	if (display_message(philo, TYPE_FORK))
		return (1);
	if (sem_wait(philo->state->mu->forks_m))
		return (1);
	if (display_message(philo, TYPE_FORK))
		return (1);
}

int				clean_forks(t_philo *philo)
{
	if (display_message(philo, TYPE_SLEEP))
		return (1);
	if (sem_post(philo->state->mu->forks_m))
		return (1);
	if (sem_post(philo->state->mu->forks_m))
		return (1);
	usleep(philo->par->time_to_sleep * 1000);
}
