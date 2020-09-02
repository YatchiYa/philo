
#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TYPE_EAT 	0
# define TYPE_SLEEP 1
# define TYPE_FORK 	2
# define TYPE_THINK	3
# define TYPE_DIED 	4
# define TYPE_OVER 	5
# define WRONG_ARG -1
# define WRONG_MALLOC -2
# define TOO_MANY_ARGS -3
# define WRONG_MALLOC_PHILO -4

struct s_state;	

typedef struct		s_paramettre
{
	int				amount;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat_count;
    struct timeval	*time_start;
}					t_paramettre;

typedef struct		s_fork
{
	pthread_mutex_t	*fork;
	size_t			nb_last;
}					t_fork;

typedef struct		s_mutexes
{
	size_t			start;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_dead_m;
}					t_mutexes;

typedef struct		s_philo
{
	int				position;
	int				eat_count;
	size_t	        limit;
	int				is_eating;
	size_t			last_eat;
	pthread_t		*thread;
	int				left_fork;
	int				right_fork;
    t_paramettre	*par;
	//t_mutexes		*mu;
	struct s_state	*state;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;
}					t_philo;


typedef struct		s_state
{
    t_paramettre	*par;
	t_philo			*philo;
	t_mutexes		*mu;
}					t_state;

int					ft_atoi(char *str);
int					ft_strlen(char *str);
void				ft_putstr(char *str);
int					init_param(t_state *state, int argc, char **argv);
int					init_philos(t_state *state);
int					clear_param(t_state *state);
int					clear_philo(t_state *state);
int					clear_mutexes(t_state *state);
int					init_mutexes(t_state *state);
size_t				get_time(void);
int					exit_error(int ret);
char				*get_message(int type);
void				ft_putnbr_fd(size_t n);
int					start_threads(t_state *state);
void				display_message(t_philo *philo, int type);
void				take_forks(t_philo *philo);
void				clean_forks(t_philo *philo);
void				eat(t_philo *philo);

#endif
