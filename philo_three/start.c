
#include "philo.h"

void			*monitor_count(void *state_v)
{
	t_state *state;
	int		i;

	state = (t_state*)state_v;
	while (state->par->cur_eat_count < state->par->must_eat_count)
	{
		i = 0;
		while (i < state->par->amount)
			if (sem_wait(state->philo[i++].eat_m))
				return ((void*)0);
		state->par->cur_eat_count++;
	}
	if (display_message(&state->philo[0], TYPE_OVER))
		return ((void*)0);
	if (sem_post(state->mu->somebody_dead_m))
		return ((void*)0);
	return ((void*)0);
}

void			*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		if (sem_wait(philo->mutex) != 0)
			return ((void*)0);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			if (display_message(philo, TYPE_DIED))
				return ((void*)0);
			if (sem_post(philo->mutex))
				return ((void*)0);
			if (sem_post(philo->state->mu->somebody_dead_m))
				return ((void*)0);
			return ((void*)0);
		}
		if (sem_post(philo->mutex))
			return ((void*)0);
	}
	return ((void*)0);
}

void			*routine(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;
	int			should_end;

	philo = (t_philo*)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->par->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, philo_v) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		if (take_forks(philo))
			return ((void*)0);
		should_end = eat(philo);
		if (clean_forks(philo))
			return ((void*)0);
		if (should_end)
			return ((void*)0);
		if (display_message(philo, TYPE_THINK))
			return ((void*)0);
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
		state->philo[i].pid = fork();
		if (state->philo[i].pid < 0)
			return (1);
		else if (state->philo[i].pid == 0)
		{
			routine(&state->philo[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}
