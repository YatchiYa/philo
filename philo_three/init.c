
#include "philo.h"

int			init_param(t_state *state, int argc, char **argv)
{
	if (!(state->par = malloc(sizeof(t_paramettre))))
		return (WRONG_MALLOC);
	state->par->time_start = NULL;
	state->par->cur_eat_count = 0;
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
	char	semaphore[250];

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
		make_semaphore_name(SEMAPHORE_PHILO, (char*)semaphore, i);
		if ((state->philo[i].mutex = ft_sem_open(semaphore, 1)) < 0)
			return (1);
		make_semaphore_name(SEMAPHORE_PHILOEAT, (char*)semaphore, i);
		if ((state->philo[i].eat_m = ft_sem_open(semaphore, 0)) < 0)
			return (1);
		i++;
	}
	return (0);
}

int			init_semaphores(t_state *state)
{
	if (!(state->mu = (t_sem*)malloc(sizeof(t_sem))))
		return (WRONG_MALLOC_PHILO);
	if ((state->mu->forks_m = ft_sem_open(SEMAPHORE_FORK, state->par->amount)) < 0
		|| (state->mu->write_m = ft_sem_open(SEMAPHORE_WRITE, 1)) < 0
		|| (state->mu->somebody_dead_m = ft_sem_open(SEMAPHORE_DEAD, 0)) < 0)
		return (1);
	return (0);
}
