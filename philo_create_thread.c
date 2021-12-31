#include "includes/philo.h"

int	create_pthread_philo(t_info *info)
{
	int	i;

	i = 0;
	info->s_time = get_time();
	while (i < info->num_philo)
	{
		if (pthread_create(&(info->philo[i].id), NULL, &philo_engine, \
		(void *)&(info->philo[i])))
		{
			printf("Error: create thread failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}
