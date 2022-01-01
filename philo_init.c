#include "includes/philo.h"

int	parse_init(int ac, char **av, t_info *info)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Error: Number of Arguments should be 5 or 6\n");
		return (0);
	}
	while (av[i])
	{
		if (argument_check(av[i]) == -1)
		{
			printf("Error: Argument range (must be positive, only digit)\n");
			return (0);
		}
		else
		{
			if (!parse_arg(ac, av, &i, info))
				return (0);
		}
		i++;
	}
	init_rest(info);
	return (1);
}

void	init_rest(t_info *info)
{
	info->die = 0;
	info->eat = 0;
	info->s_time = 0;
	info->philo = NULL;
	info->fork = NULL;
}

int	philo_init(t_info *info)
{
	int	i;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philo)
	{
		printf("Error: Malloc fail - t_philo struct\n");
		return (0);
	}
	i = 0;
	while (i < info->num_philo)
	{
		info->philo[i].index = i;
		info->philo[i].l_fork = i;
		info->philo[i].r_fork = (i + 1) % info->num_philo;
		info->philo[i].eat_count = 0;
		info->philo[i].last_eat_time = 0;
		info->philo[i].info = info;
		if (pthread_mutex_init(&(info->philo[i].block_letime), NULL))
		{
			printf("Error: philo block_letime mutex init fail\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	mutex_init(t_info *info)
{
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* info->num_philo);
	if (!info->fork)
		return (rtn_err_msg("Error: Malloc failed - fork mutex"));
	if (!fork_mutex_init(info))
		return (rtn_err_msg("Error: Fork mutex init fail"));
	if (pthread_mutex_init(&(info->message), NULL))
		return (rtn_err_msg("Error: Message mutex init failed"));
	if (pthread_mutex_init(&(info->block_ptime), NULL))
		return (rtn_err_msg("Error: block_ptime mutex init failed"));
	if (pthread_mutex_init(&(info->philo->block_letime), NULL))
		return (rtn_err_msg("Error: block_letime mutex init failed"));
	if (pthread_mutex_init(&(info->block_die), NULL))
		return (rtn_err_msg("Error: block_die mutex init failed"));
	if (pthread_mutex_init(&(info->block_eat), NULL))
		return (rtn_err_msg("Error: block_eat mutex init failed"));
	if (pthread_mutex_init(&(info->block_eatcount), NULL))
		return (rtn_err_msg("Error: block_eatcount mutex init failed"));
	return (1);
}

int	fork_mutex_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL))
			return (0);
		i++;
	}
	return (1);
}
