
#include "philo.h"

void			*monitor_count(void *state_v)
{
	t_state *state;
	int		i;
	int		total;

	state = (t_state*)state_v;
	total = 0;
	while (total < state->par->must_eat_count)
	{
		i = 0;
		while (i < state->par->amount)
			pthread_mutex_lock(&state->philo[i++].eat_m);
		total++;
	}
	display_message(&state->philo[0], TYPE_OVER);
	pthread_mutex_unlock(&state->mu->somebody_dead_m);
	return ((void*)0);
}

void			*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			display_message(philo, TYPE_DIED);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->state->mu->somebody_dead_m);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}

void			*routine(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->par->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, philo_v) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		clean_forks(philo);
		display_message(philo, TYPE_THINK);
	}
	return ((void*)0);
}

int				start_threads(t_state *state)
{
	pthread_t	tid;
	int			i;
	void		*philos;

	state->mu->start = get_time();
	if (state->par->must_eat_count > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void*)state) != 0)
			return (1);
		pthread_detach(tid);
	}
	i = 0;
	while (i < state->par->amount)
	{
		philos = (void*)(&state->philo[i]);
		if (pthread_create(&tid, NULL, &routine, philos) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}
