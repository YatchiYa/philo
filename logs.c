
#include "philo_one.h"

/*
** function: {msg_error}
**
** parameters:
** (char *){msg} - error's message (ex: malloc error)
**
** return (void)
**
** description:
** send an error in stderr_fileno
*/

void	ft_usleep(unsigned int n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
((size_t)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}

/*
** function: {logs}
**
** parameters:
** (timeval *){st} - timeval start of the program,
** (timeval *){tv} - actual timeval,
** (size_t){number} - philosopher's number,
** (char *){msg} - msg of the current philosopher
**
** return (int): no-null if error
**
** description:
** print on stdin the status of the {number} philosopher at a time {tv} like :
** "timestamp_in_ms number msg"
*/

int		logs(struct timeval *st, struct timeval *tv, size_t number, char *msg)
{
	char		*ptr;
	char		*log;
	size_t		size_nb;
	long long	temp;
	long long	time;

	temp = number * 10;
	size_nb = 4 + ft_strlen(msg);
	while (temp /= 10)
		size_nb++;
	time = (tv->tv_sec - st->tv_sec) * 1000 +
(tv->tv_usec - st->tv_usec) * 0.001;
	temp = time;
	while (temp /= 10)
		size_nb++;
	if (!(log = malloc(sizeof(char) * (size_nb))))
		return (ERROR_MALLOC);
	ptr = log;
	fill_nbr((size_t)time, &ptr);
	fill_msg("ms ", &ptr);
	fill_nbr(number, &ptr);
	fill_msg(msg, &ptr);
	write(STDOUT_FILENO, log, size_nb);
	free(log);
	return (0);
}
