
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TYPE_EAT 	0
# define TYPE_SLEEP 1
# define TYPE_FORK 	2
# define TYPE_THINK	3
# define TYPE_DIED 	4
# define TYPE_OVER 	5

struct s_state;

typedef struct		s_paramettre
{
	int				amount;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat_count;
}					t_paramettre;

typedef struct		s_fork
{
	pthread_mutex_t	*fork;
	size_t			nb_last;
}					t_fork;

typedef struct		s_philosopher
{
	size_t			position;
	int				eat_count;
	t_paramettre	*parameters;
	size_t			limit;
	size_t			last_eat;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;
	pthread_mutex_t	somebody_dead_m;
	pthread_mutex_t	write_m;
}					t_philosopher;

typedef struct		s_philo_one
{
	t_paramettre	*parameters;
	t_philosopher	*philos;
	pthread_mutex_t	somebody_dead_m;
	pthread_mutex_t	write_m;
	size_t			start;
}					t_philo_one;



int					ft_strlen(char const *str);

int					ft_atoi(char *str);

void				ft_putnbr_fd(size_t n, int fd);

size_t				get_time(void);

int					clear_state(t_philo_one *state);

int					exit_error(char const *str);


#endif
