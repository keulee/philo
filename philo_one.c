#include "includes/philo.h"

int	one_philo(t_info *info)
{
	printf("0 1 has taken a fork\n");
	usleep(info->living_time * 1000);
	printf("%d 1 died\n", info->living_time + 1);
	return (1);
}
