#include "includes/philo.h"

void	monitor_thread(t_info *info)
{
	int i;
	int eat_c;

	i = 0;
	eat_c = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_lock(&(info->philo[i].block_letime));
		info->philo[i].last_eat_time = get_time();
		pthread_mutex_unlock(&(info->philo[i].block_letime));
		i++;
	}
	while (!(info->eat))
	{
		while (i < info->num_philo && !(info->die))
		{
			// pthread_mutex_lock(&(info->philo[i].block_letime));
			if (get_time() - info->philo[i].last_eat_time > info->living_time)
			{
				// pthread_mutex_unlock(&(info->philo[i].block_letime));
				philo_message(info, info->philo[i].index, "died");
				pthread_mutex_lock(&(info->block_die));
				info->die = 1;
				pthread_mutex_unlock(&(info->block_die));
			}
			// pthread_mutex_unlock(&(info->philo[i].block_letime));
			i++;
		}
		if (info->die == 1)
			break ;
		i = 0;
		while (i < info->num_philo && info->max_eatcount)
		{
			if (info->philo[i].eat_count >= info->max_eatcount)
				eat_c++;
			i++;
		}
		if (eat_c == info->num_philo)
			info->eat = 1;
	}
}