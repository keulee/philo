#include "includes/philo.h"

int	one_philo(t_info *info)
{
	printf("0 1 has taken a fork\n");
	usleep(info->time_to_die * 1000);
	printf("%d 1 died\n", info->time_to_die + 1);
	return (1);
}
