
#include "philosophers.h"

int			clear_state(t_philo_one *state)
{
	int	i;

	if (state->philos)
	{
		i = 0;
		while (i < state->parameters->amount)
		{
			pthread_mutex_destroy(&state->philos[i].mutex);
			pthread_mutex_destroy(&state->philos[i++].eat_m);
		}
		free(state->philos);
	}
	pthread_mutex_destroy(&state->write_m);
	pthread_mutex_destroy(&state->somebody_dead_m);
	return (1);
}

int			exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}
