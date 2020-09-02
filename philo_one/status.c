
#include "philo.h"

void			eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->par->time_to_die;
	display_message(philo, TYPE_EAT);
	usleep(philo->par->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat_m);
}

void			take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->mu->forks_m[philo->left_fork]);
	display_message(philo, TYPE_FORK);
	pthread_mutex_lock(&philo->state->mu->forks_m[philo->right_fork]);
	display_message(philo, TYPE_FORK);
}

void			clean_forks(t_philo *philo)
{
	display_message(philo, TYPE_SLEEP);
	pthread_mutex_unlock(&philo->state->mu->forks_m[philo->left_fork]);
	pthread_mutex_unlock(&philo->state->mu->forks_m[philo->right_fork]);
	usleep(philo->par->time_to_sleep * 1000);
}
