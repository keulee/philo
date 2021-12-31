#include "includes/philo.h"

void	philo_die_monitor(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo && !(info->die))
	{
		pthread_mutex_unlock(&(info->block_die));
		pthread_mutex_lock(&(info->philo[i].block_letime));
		if (get_time() - info->philo[i].last_eat_time > info->living_time)
		{
			pthread_mutex_unlock(&(info->philo[i].block_letime));
			philo_message(info, info->philo[i].index, "died");
			pthread_mutex_lock(&(info->block_die));
			info->die = 1;
			pthread_mutex_unlock(&(info->block_die));
		}
		pthread_mutex_unlock(&(info->philo[i].block_letime));
		pthread_mutex_lock(&(info->block_die));
		i++;
	}
}

void	philo_eat_monitor(t_info *info, int *eat_count)
{
	int	i;

	i = 0;
	while (i < info->num_philo && info->max_eatcount != 0)
	{
		pthread_mutex_lock(&info->block_eatcount);
		if (info->philo[i].eat_count >= info->max_eatcount)
		{
			(*eat_count)++;
		}
		pthread_mutex_unlock(&info->block_eatcount);
		i++;
	}
	pthread_mutex_lock(&(info->block_eat));
	if (*eat_count == info->num_philo)
		info->eat = 1;
	pthread_mutex_unlock(&(info->block_eat));
}

void	monitor_thread(t_info *info)
{
	int	i;
	int	eat_c;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_lock(&(info->philo[i].block_letime));
		info->philo[i].last_eat_time = get_time();
		pthread_mutex_unlock(&(info->philo[i].block_letime));
		i++;
	}
	while (!(info->eat))
	{
		eat_c = 0;
		pthread_mutex_lock(&(info->block_die));
		philo_die_monitor(info);
		pthread_mutex_unlock(&(info->block_die));
		if (info->die == 1)
			break ;
		philo_eat_monitor(info, &eat_c);
	}
}
