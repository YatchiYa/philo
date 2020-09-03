
#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# define TYPE_EAT 			0
# define TYPE_SLEEP 		1
# define TYPE_FORK 			2
# define TYPE_THINK			3
# define TYPE_DIED 			4
# define TYPE_OVER 			5
# define WRONG_ARG 			-1
# define WRONG_MALLOC 		-2
# define TOO_MANY_ARGS 		-3
# define WRONG_MALLOC_PHILO -4
# define WRONG_ARG_EAT 		-5
# define SEMAPHORE_FORK		"SemaphoreFork"
# define SEMAPHORE_WRITE	"SemaphoreWrite"
# define SEMAPHORE_DEAD		"SemaphoreDead"
# define SEMAPHORE_PHILO	"SemaphorePhilo"
# define SEMAPHORE_PHILOEAT	"SemaphorePhiloEat"
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
	sem_t			*fork;
	size_t			nb_last;
}					t_fork;

typedef struct		s_sem
{
	size_t			start;
	int				over;
	sem_t			*forks_m;
	sem_t			*write_m;
	sem_t			*somebody_dead_m;
}					t_sem;

typedef struct		s_philo
{
	int				position;
	int				eat_count;
	size_t	        limit;
	int				is_eating;
	size_t			last_eat;
	int				left_fork;
	int				right_fork;
    t_paramettre	*par;
	struct s_state	*state;
	sem_t			*mutex;
	sem_t			*eat_m;
}					t_philo;


typedef struct		s_state
{
    t_paramettre	*par;
	t_philo			*philo;
	t_sem			*mu;
}					t_state;

int					ft_atoi(char *str);
int					ft_strlen(char *str);
void				ft_putstr(char *str);
int					init_param(t_state *state, int argc, char **argv);
int					init_philos(t_state *state);
int					clear_param(t_state *state);
int					clear_philo(t_state *state);
int					clear_semaphores(t_state *state);
int					init_semaphores(t_state *state);
size_t				get_time(void);
int					exit_error(int ret);
char				*get_message(int type);
void				ft_putnbr_fd(size_t n);
int					start_threads(t_state *state);
int					display_message(t_philo *philo, int type);
int					take_forks(t_philo *philo);
int					clean_forks(t_philo *philo);
int					eat(t_philo *philo);
char				*make_semaphore_name(char const *base, char *buffer, int position);
sem_t				*ft_sem_open(char const *name, int value);

#endif
