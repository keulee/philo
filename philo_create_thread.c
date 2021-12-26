#include "includes/philo.h"

int	create_pthread_philo(t_info *info)
{
	int i;

	i = 0;
	info->s_time = get_time();
	while(i < info->num_philo)
	{
		// if (pthread_create(&(info->philo[i].id), NULL, &philo_engine, (void *)&(info->philo[i])))
		if (pthread_create(&(info->philo[i].id), NULL, &philo_test, (void *)&(info->philo[i])))
		{
			printf("Error: create thread failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	*philo_test(void *ptr)
{
	t_philo *philo;
	t_info *info;

	philo = ptr;
	info = philo->info;
	if (philo->index % 2 == 1) // when the index of philo is odd (1, 3, ... 2n - 1)
	// thinking first, let the even number philo eat first
	{
		printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is thinking");
		usleep(15000);
	}
	// }
	while (!info->die)
	{
		if (info->num_philo % 2 == 0) //number of philo is even
		{
			pthread_mutex_lock(&(info->fork[philo->l_fork]));
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			pthread_mutex_lock(&(info->fork[philo->r_fork]));
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is eating");
			philo->last_eat_time = get_time();
			philo->eat_count++;
			usleep(info->eating_time * 1000);
			pthread_mutex_unlock(&(info->fork[philo->l_fork]));
			pthread_mutex_unlock(&(info->fork[philo->r_fork]));
		}
		else //number of philo is odd
		{
			if (philo->index % 2 == 0) //index of philo is even (odd order of philo)
				pthread_mutex_lock(&(info->fork[philo->l_fork]));
			else
				pthread_mutex_lock(&(info->fork[philo->r_fork]));
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			if (philo->index % 2 == 0) //index of philo is even (odd order of philo)
				pthread_mutex_lock(&(info->fork[philo->r_fork]));
			else
				pthread_mutex_lock(&(info->fork[philo->l_fork]));
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is eating");
			philo->last_eat_time = get_time();
			philo->eat_count++;
			usleep(info->eating_time * 1000);
			pthread_mutex_unlock(&(info->fork[philo->l_fork]));
			pthread_mutex_unlock(&(info->fork[philo->r_fork]));
			
		}
		printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is sleeping");
		usleep(info->sleeping_time * 1000);
		printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is thinking");
		usleep(15000);
	}
	return (NULL);
}