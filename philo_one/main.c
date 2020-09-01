
#include "philosophers.h"
#include "stdio.h"


int			init(t_philo_one *state, int argc, char **argv)
{
	printf("debug \n");
	state->parameters->amount = ft_atoi(argv[1]);
	printf("debug \n");
	state->parameters->time_to_die = ft_atoi(argv[2]);
	state->parameters->time_to_eat = ft_atoi(argv[3]);
	state->parameters->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->parameters->must_eat_count = ft_atoi(argv[5]);
	else
		state->parameters->must_eat_count = 0;
	if (state->parameters->amount < 2 || state->parameters->amount > 200 || state->parameters->time_to_die < 60
		|| state->parameters->time_to_eat < 60 || state->parameters->time_to_sleep < 60
		|| state->parameters->must_eat_count < 0)
		return (1);
	// state->parameters->forks_m = NULL;
	state->philos = NULL;
	if (!(state->philos =
		(t_philosopher*)malloc(sizeof(*(state->philos)) * state->parameters->amount)))
		return (1);
	return (0);
}


int			main(int argc, char **argv)
{
	t_philo_one	*state;

	if (argc < 5 || argc > 6)
		return (exit_error("error: bad arguments\n"));
	state = (t_philo_one *)malloc(sizeof(t_philo_one));
	if (init(state, argc, argv))
		return (exit_error("error: bad arguments\n"));

	return (0);
}
