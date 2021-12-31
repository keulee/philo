#include "includes/philo.h"

void	ft_usleep(long long time, t_info *info)
{
	long long	time_gap;

	pthread_mutex_lock(&(info->block_ptime));
	time_gap = get_time();
	pthread_mutex_unlock(&(info->block_ptime));
	while ((get_time() - time_gap) < time)
	{
		if (info->num_philo < 50)
			usleep(100);
		else
			usleep(1000);
	}
}
