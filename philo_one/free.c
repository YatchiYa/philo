
#include "philo.h"

int			clear_param(t_state *state)
{
	if (state->par)
		free(state->par);
	return (1);
}

int			clear_mutexes(t_state *state)
{
	int			i;

	if (state->mu->forks_m)
	{
		i = 0;
		while (i < state->par->amount)
			pthread_mutex_destroy(&state->mu->forks_m[i++]);
		free(state->mu->forks_m);
	}
	pthread_mutex_destroy(&state->mu->write_m);
	pthread_mutex_destroy(&state->mu->somebody_dead_m);
	clear_philo(state);
	clear_param(state);
	return (1);
}

int			clear_philo(t_state *state)
{
	int			i;

	i = 0;
	if (state->philo)
	{
		while (i < state->par->amount)
		{
			pthread_mutex_destroy(&state->philo[i].mutex);
			pthread_mutex_destroy(&state->philo[i].eat_m);
			i++;
		}
		if (state->philo)
			free(state->philo);
	}
	return (clear_param(state));	
}