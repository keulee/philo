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
