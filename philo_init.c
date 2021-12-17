#include "includes/philo.h"

int	parsing_arg(int ac, char **av, int *i, t_info *info)
{
	if (*i == 1)
	{
		info->num_philo = argument_check(av[*i]);
		if (info->num_philo > 200)
		{
			printf("Error: Number of philosopher must not be over 200\n");
			return (0);
		}
	}
	else if (*i == 2)
		info->time_to_die = argument_check(av[*i]);
	else if (*i == 3)
		info->time_to_eat = argument_check(av[*i]);
	else if (*i == 4)
		info->time_to_sleep = argument_check(av[*i]);
	if (ac == 6)
		info->max_eattime = argument_check(av[*i]);
	else
		info->max_eattime = 0;
	return (1);
}

int	ft_parse_init(int ac, char **av, t_info *info)
{
	int		i;

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
			if (!parsing_arg(ac, av, &i, info))
				return (0);
		}
		i++;
	}
	return (1);
}

/*
**void	*test(void *test)
**{
**	int i = 0;
**	t_philo *philo;
**
**	philo = (t_philo *)test;
**	printf("test\n");
**	return (NULL);
**}
*/

int	philo_init(t_info *info)
{
	int	i;

	i = 0;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philo)
	{
		printf("Error: Malloc fail - t_philo struct\n");
		return (0);
	}
	while (i < info->num_philo)
	{
		info->philo[i].philo_index = 0;
		info->philo[i].l_fork = i;
		info->philo[i].r_fork = (i + 1) % info->num_philo;
		info->philo[i].eat_count = 0;
		info->philo[i].last_eat_time = 0;
		info->philo[i].info = info;
		i++;
	}
	return (1);
}

int	mutex_init(t_info *info)
{
	int	i;

	i = 0;
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* info->num_philo);
	if (!info->fork)
	{
		printf("Error: Malloc fail - fork mutex\n");
		return (0);
	}
	while (i < info->num_philo)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL))
		{
			printf("Error: Fork mutex init fail\n");
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&(info->message), NULL))
	{
		printf("Error: Message mutex init fail\n");
		return (0);
	}
	return (1);
}
