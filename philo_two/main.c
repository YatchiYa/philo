
#include "philo.h"

int			main(int argc, char **argv)
{
	int				ret;
	t_state			state;

	state.philo = NULL;
	if ((ret = init_param(&state, argc, argv)) != 0)
		return (exit_error(ret) && clear_param(&state));
	if (state.par->must_eat_count == -1 ||
		state.par->must_eat_count == 0)
		return (exit_error(WRONG_ARG_EAT) && clear_param(&state));
	if ((ret = init_philos(&state)) != 0)
		return (exit_error(ret) && clear_philo(&state));
	if ((ret = init_semaphores(&state)) != 0)
		return (exit_error(ret) && clear_semaphores(&state));
	if ((ret = start_threads(&state)))
		return (clear_semaphores(&state) && exit_error(ret));
	sem_wait(state.mu->somebody_dead_m);
	clear_semaphores(&state);
	return (0);
}