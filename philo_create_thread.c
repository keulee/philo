#include "includes/philo.h"

int	create_pthread_philo(t_info *info)
{
	int i;

	i = 0;
	info->s_time = get_time();
	while(i < info->num_philo)
	{
		if (pthread_create(&(info->philo[i].id), NULL, &philo_engine, (void *)&(info->philo[i])))
		{
			printf("Error: create thread failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	*philo_engine(void *ptr)
{
	t_philo *philo;
	t_info *info;

	philo = ptr;
	info = philo->info;
	if (philo->index % 2 == 1) // when the index of philo is odd (1, 3, ... 2n - 1)
	// thinking first, let the even number philo eat first
	{
		philo_message(info, philo, "is thinking");
		// pthread_mutex_lock(&(info->message));
		// if (!info->die)
		// 	printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is thinking");
		// pthread_mutex_unlock(&(info->message));
		// ft_usleep(info->eating_time / 1.333);
		usleep(15000);
	}
	// }
	while (!info->die)
	{
		if (info->num_philo % 2 == 0) //number of philo is even
		{
			if (philo->index % 2 == 0) //index of philo is even (odd order of philo)
				pthread_mutex_lock(&(info->fork[philo->l_fork]));
			else
				pthread_mutex_lock(&(info->fork[philo->r_fork]));
			if (!info->die)
				printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			if (philo->l_fork == philo->r_fork)
			{
				ft_usleep(info->living_time * 2, info);
				return (NULL);
			}
			if (philo->index % 2 == 0) //index of philo is even (odd order of philo)
				pthread_mutex_lock(&(info->fork[philo->r_fork]));
			else
				pthread_mutex_lock(&(info->fork[philo->l_fork]));
			if (!info->die)
				printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			pthread_mutex_lock(&(philo->block_letime));
			pthread_mutex_lock(&(info->message));
			if (!info->die)
				printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is eating");
			pthread_mutex_unlock(&(info->message));
			philo->last_eat_time = get_time();
			pthread_mutex_unlock(&(philo->block_letime));
			philo->eat_count++;
			ft_usleep(info->eating_time, info);
			pthread_mutex_unlock(&(info->fork[philo->l_fork]));
			pthread_mutex_unlock(&(info->fork[philo->r_fork]));
		}
		else //number of philo is odd
		{
			pthread_mutex_lock(&(info->fork[philo->l_fork]));
			if (!info->die)
				printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			pthread_mutex_lock(&(info->fork[philo->r_fork]));
			if (philo->l_fork == philo->r_fork)
			{
				ft_usleep(info->living_time * 2, info);
				return (NULL);
			}
			if (!info->die)
				printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			pthread_mutex_lock(&(philo->block_letime));
			pthread_mutex_lock(&(info->message));
			if (!info->die)
				printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is eating");
			pthread_mutex_unlock(&(info->message));
			philo->last_eat_time = get_time();
			pthread_mutex_unlock(&(philo->block_letime));
			philo->eat_count++;
			ft_usleep(info->eating_time, info);
			pthread_mutex_unlock(&(info->fork[philo->l_fork]));
			pthread_mutex_unlock(&(info->fork[philo->r_fork]));			
		}
		if (info->eat == 1)
			break ;
		pthread_mutex_lock(&(info->message));
		if (!info->die)
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is sleeping");
		pthread_mutex_unlock(&(info->message));
		ft_usleep(info->sleeping_time, info);
		pthread_mutex_lock(&(info->message));
		if (!info->die)
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is thinking");
		pthread_mutex_unlock(&(info->message));
	}
	return (NULL);
}