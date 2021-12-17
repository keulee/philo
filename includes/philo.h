#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

typedef	struct s_philo {
	struct s_info	*info;
	int				philo_index;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	long long		last_eat_time;
	long long		present_time;
	pthread_t 		id;
}				t_philo;

typedef struct s_info {
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eattime;
	int				start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t message;
}				t_info;

void	ft_debug(t_info *info);

int		argument_check(char *str);
int		ft_only_digit(char *str);
int		ft_digit(char c);

int		ft_parse_init(int ac, char **av, t_info *info);
int		parsing_arg(int ac, char **av, int *i, t_info *info);
int		philo_init(t_info *info);
int		mutex_init(t_info *info);

int		one_philo(t_info *info);
void	*test(void *test);

#endif
