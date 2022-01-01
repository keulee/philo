#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo {
	struct s_info	*info;
	int				index;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	long long		last_eat_time;
	long long		present_time;
	pthread_t		id;
	pthread_mutex_t	block_letime;
}				t_philo;

typedef struct s_info {
	int				num_philo;
	int				living_time;
	int				eating_time;
	int				sleeping_time;
	int				max_eatcount;
	long long		s_time;
	int				die;
	int				eat;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	message;
	pthread_mutex_t	block_ptime;
	pthread_mutex_t	block_die;
	pthread_mutex_t	block_eat;
	pthread_mutex_t	block_eatcount;
}				t_info;

/*
philo_create_thread.c
*/
int			create_pthread_philo(t_info *info);

/*
philo_engine.c
*/
void		*philo_engine(void *ptr);
void		*philo_loop(t_info *info, t_philo *philo);
int			philo_eat_first(t_philo *philo, int loop_index);
void		philo_think_first(t_info *info, t_philo *philo);
void		philo_eat_sleep_think(t_philo *philo);

/*
philo_free_thread.c
*/
void		free_thread(t_info *info);

/*
philo_init.c
*/
int			parse_init(int ac, char **av, t_info *info);
void		init_rest(t_info *info);
int			philo_init(t_info *info);
int			mutex_init(t_info *info);
int			fork_mutex_init(t_info *info);

/*
philo_message.c
*/
void		philo_message(t_info *info, int index, char *message);

/*
philo_monitor.c
*/
void		monitor_thread(t_info *info);
void		philo_die_monitor(t_info *info);
void		philo_eat_monitor(t_info *info, int *eat_count);

/*
philo_one.c
*/
int			one_philo(t_info *info);

/*
philo_time.c
*/
long long	get_time(void);
void		ft_usleep(long long time, t_philo *philo);

/*
philo_utils.c
*/
int			parse_arg(int ac, char **av, int *i, t_info *info);
int			argument_check(char *str);
int			ft_only_digit(char *str);
int			ft_digit(char c);
int			rtn_err_msg(char *str);

#endif
