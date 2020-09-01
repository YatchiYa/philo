
#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define TOO_MANY_ARGS -3
# define WRONG_ARG -4
# define ERROR_MALLOC -5
# define ERROR_MUTEX -6
# define ERROR_PTHREAD -7
# define ERROR_SLEEP -8
# define ERROR_TIMEOFDAY -9

int		throw_error(int error);
void	ft_usleep(unsigned int n);
int		logs(struct timeval *st, struct timeval *tv, size_t number, char *msg);

typedef struct		s_parameters
{
	int				number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_time_each_philosophers_must_eat;
	struct timeval	*time_start;
}					t_parameters;

typedef struct		s_fork
{
	pthread_mutex_t	*fork;
	size_t			nb_last;
}					t_fork;

typedef struct		s_philosopher
{
	size_t			nb;
	size_t			nb_eat;
	t_parameters	*parameters;
	pthread_t		*thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t *lock_last_meal;
	struct timeval	*time_last_meal;
	void			*next;
}					t_philosopher;

typedef struct		s_philo_one
{
	char			*name;
	t_parameters	*parameters;
	t_philosopher	*philosophers;
}					t_philo_one;

void				unmake_pairs(t_philo_one *phi);
int					launch_philosophers(t_philo_one *phi);
int					setup_philosopher(t_philo_one *phi, int i,
t_philosopher **ptr, t_fork **r_fork);
int					init_philosophers(t_philo_one *phi);
void	*alive(void *ptr);
t_parameters		*copy_parameters(t_parameters *parameters);
void				fill_msg(char *msg, char **ptr);
void				fill_nbr(size_t nbr, char **timestamp);
size_t				ft_strlen(const char *s);
int					ft_atos(char *str, size_t *nb);


#endif
