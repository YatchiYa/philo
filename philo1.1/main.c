
#include "philo_one.h"

int		set_philo_paramettre(t_philo_one *philos, int i, t_philosopher **tmp_philo,
t_fork **tmp_fork)
{
	if (!((*tmp_philo)->thread = malloc(sizeof(pthread_t))))
		return (ERROR_MALLOC);
	(*tmp_philo)->right_fork = (i == philos->parameters->number_of_philosophers) ?
philos->philosophers->left_fork : malloc(sizeof(t_fork));
	if (!((*tmp_fork) = (*tmp_philo)->right_fork) ||
((i != philos->parameters->number_of_philosophers) &&
!((*tmp_philo)->right_fork->fork = malloc(sizeof(pthread_mutex_t)))))
		return (ERROR_MALLOC);
	if (pthread_mutex_init((*tmp_fork)->fork, NULL))
		return (ERROR_MUTEX);
	if (i != philos->parameters->number_of_philosophers &&
!((*tmp_philo)->next = malloc(sizeof(t_philosopher))))
		return (ERROR_MALLOC);
	else if (i == philos->parameters->number_of_philosophers)
		(*tmp_philo)->next = NULL;
	return (0);
}

int		init_philosophers(t_philo_one *philos)
{
	int				ret;
	int				i;
	t_philosopher	*tmp_philo;
	t_fork			*tmp_fork;

	if (!(philos->philosophers = malloc(sizeof(t_philosopher))) ||
		!(tmp_fork = malloc(sizeof(t_fork))) ||
		!(tmp_fork->fork = malloc(sizeof(pthread_mutex_t))))
		return (ERROR_MALLOC);
	if (!(i = 0) && pthread_mutex_init(tmp_fork->fork, NULL))
		return (ERROR_MUTEX);
	tmp_philo = philos->philosophers;
	while (tmp_philo &&
			i++ < philos->parameters->number_of_philosophers)
	{
		tmp_philo->nb = i;
		tmp_philo->left_fork = tmp_fork;
		if ((ret = set_philo_paramettre(philos, i, &tmp_philo, &tmp_fork)))
			return (ret);
		tmp_philo = tmp_philo->next;
	}
	return (0);
}

int		init_paramettre(int argc, char *argv[], t_philo_one *philos)
{
	if (!(philos->parameters = malloc(sizeof(t_parameters))))
		return (ERROR_MALLOC);
	philos->parameters->time_start = NULL;
	if ((philos->parameters->number_of_philosophers = ft_atoi(argv[1])) < 2)
		return (WRONG_ARG);
	if ((philos->parameters->time_to_die = ft_atoi(argv[2])) == -1)
		return (WRONG_ARG);
	if ((philos->parameters->time_to_eat = ft_atoi(argv[3])) == -1)
		return (WRONG_ARG);
	if ((philos->parameters->time_to_sleep = ft_atoi(argv[4])) == -1)
		return (WRONG_ARG);
	if (argc == 6 && (philos->parameters->number_of_time_each_philosophers_must_eat = ft_atoi(argv[5])) == -1)
		return (WRONG_ARG);
	else if (argc == 5)
		philos->parameters->number_of_time_each_philosophers_must_eat = -1;
	return (0);
}

int		main(int argc, char *argv[])
{
	int				ret;
	t_philo_one		philos;

	philos.philosophers = NULL;
	if (argc < 5 || argc > 6)
		return (throw_error(WRONG_ARG));
	if ((ret = init_paramettre(argc, argv, &philos)))
		return (throw_error(ret) + clean_all(&philos));
	if (philos.parameters->number_of_time_each_philosophers_must_eat == -1)
		return (clean_all(&philos));
	
	if ((ret = init_philosophers(&philos)))
		return (throw_error(ret) + clean_all(&philos));
		
	unmake_pairs(&philos);
	if ((ret = launch_philosophers(&philos)))
		return (throw_error(ret) + clean_all(&philos));
	if (usleep((philos.parameters->time_to_eat +
philos.parameters->time_to_sleep) * 1000))
		throw_error(ERROR_SLEEP);
	clean_all(&philos);
}
