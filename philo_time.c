#include "includes/philo.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	time_gap;

	pthread_mutex_lock(&(philo->info->block_ptime));
	time_gap = get_time();
	pthread_mutex_unlock(&(philo->info->block_ptime));
	while ((get_time() - time_gap) < time)
	{
		if (philo->info->num_philo < 50)
			usleep(100);
		else
			usleep(1000);
	}
}
