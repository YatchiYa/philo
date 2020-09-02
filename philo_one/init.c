
#include "philo.h"

int			init_param(t_state *state, int argc, char **argv)
{
	if (!(state->par = malloc(sizeof(t_paramettre))))
		return (WRONG_MALLOC);
	state->par->time_start = NULL;
	if (argc < 5 || argc > 6)
		return (TOO_MANY_ARGS);
	if ((state->par->amount = ft_atoi(argv[1])) < 2)
		return (WRONG_ARG);
	if ((state->par->time_to_die = ft_atoi(argv[2])) < 30)
		return (WRONG_ARG);
	if ((state->par->time_to_eat = ft_atoi(argv[3])) < 30)
		return (WRONG_ARG);
	if ((state->par->time_to_sleep = ft_atoi(argv[4])) < 30)
		return (WRONG_ARG);
	if (argc == 6 && (state->par->must_eat_count = ft_atoi(argv[5])) < 0)
		return (WRONG_ARG);
	else if (argc == 5)
		state->par->must_eat_count = -1;
	return (0);
}

int			init_philos(t_state *state)
{
	int		i;

	i = 0;
	if (!(state->philo =
		(t_philo*)malloc(sizeof(*(state->philo)) * state->par->amount)))
			return (WRONG_MALLOC_PHILO);
	while (i < state->par->amount)
	{
		state->philo[i].is_eating = 0;
		state->philo[i].position = i;
		state->philo[i].left_fork = i;
		state->philo[i].right_fork = (i + 1) % state->par->amount;
		state->philo[i].eat_count = 0;
		state->philo[i].state = state;
		state->philo[i].par = state->par;
		pthread_mutex_init(&state->philo[i].mutex, NULL);
		pthread_mutex_init(&state->philo[i].eat_m, NULL);
		pthread_mutex_lock(&state->philo[i].eat_m);
		i++;
	}
	return (0);
}

int			init_mutexes(t_state *state)
{
	int			i;

	if (!(state->mu = (t_mutexes*)malloc(sizeof(t_mutexes))))
		return (WRONG_MALLOC_PHILO);
	if (!(state->mu->forks_m =
		(pthread_mutex_t*)malloc(sizeof(*(state->mu->forks_m)) * state->par->amount)))
		return (WRONG_MALLOC_PHILO);
	pthread_mutex_init(&state->mu->write_m, NULL);
	pthread_mutex_init(&state->mu->somebody_dead_m, NULL);
	pthread_mutex_lock(&state->mu->somebody_dead_m);
	i = 0;
	while (i < state->par->amount)
		pthread_mutex_init(&state->mu->forks_m[i++], NULL);
	return (0);
}
