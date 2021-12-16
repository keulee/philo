#include "includes/philo.h"

void	ft_debug(t_info *info)
{
	printf("\033[38;5;30m = DEBUG Line ==============\n");
	printf("num_philo	| %d\n", info->num_philo);
	printf("time_to_die	| %d\n", info->time_to_die);
	printf("time_to_eat	| %d\n", info->time_to_eat);
	printf("time_to_sleep	| %d\n", info->time_to_sleep);
	printf("max_eattime	| %d\n", info->max_eattime);
	printf("===========================\033[0m\n");
}
