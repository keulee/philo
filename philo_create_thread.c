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
	while (!(info->test))
	{
		pthread_mutex_lock(&(info->message));
		printf("philo %d hihi\n", philo->index);
		usleep(1000 * 1000);
		pthread_mutex_unlock(&(info->message));
		info->philo[philo->index].eat_count++;
		pthread_mutex_lock(&(info->message));
		printf("philo[%d] eat count = %d\n", philo->index,info->philo[philo->index].eat_count);
		pthread_mutex_unlock(&(info->message));
		if (info->eat)
			return (NULL);
	}
	return (NULL);
}