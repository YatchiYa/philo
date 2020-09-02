
#include "philo.h"

int			main(int argc, char **argv)
{
	int				ret;
	t_state			state;

	state.philo = NULL;
	if ((ret = init_param(&state, argc, argv)) != 0)
		return (exit_error(ret) && clear_param(&state));
	if (state.par->must_eat_count == -1)
		return (exit_error(WRONG_ARG) && clear_param(&state));
	if ((ret = init_philos(&state)) != 0)
		return (exit_error(ret) && clear_philo(&state));
	if ((ret = init_mutexes(&state)) != 0)
		return (exit_error(ret) && clear_mutexes(&state));
	if ((ret = start_threads(&state)))
		return (clear_mutexes(&state) && exit_error(ret));
	pthread_mutex_lock(&state.mu->somebody_dead_m);
	pthread_mutex_unlock(&state.mu->somebody_dead_m);
	clear_mutexes(&state);
	return (0);
}