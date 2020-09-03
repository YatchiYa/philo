
#include "philo.h"

int			clear_param(t_state *state)
{
	if (state->par)
		free(state->par);
	return (1);
}

int			clear_semaphores(t_state *state)
{
	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	if (state && state->mu)
		free(state->mu);
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
			sem_unlink(SEMAPHORE_PHILO);
			sem_unlink(SEMAPHORE_PHILOEAT);
			i++;
		}
		if (state->philo)
			free(state->philo);
	}
	return (clear_param(state));	
}