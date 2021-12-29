#include "includes/philo.h"

void	free_thread(t_info *info)
{
	int i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philo[i].id, NULL);
		pthread_mutex_destroy(&(info->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(info->message));
	pthread_mutex_destroy(&(info->block_ptime));
	pthread_mutex_destroy(&(info->philo->block_letime));
	pthread_mutex_destroy(&(info->block_die));
	pthread_mutex_destroy(&(info->block_eat));
	pthread_mutex_destroy(&(info->block_eatcount));
}