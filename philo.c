#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (!ft_parse_init(ac, av, &info))
		return (1);
	if (info.num_philo == 1)
		return (one_philo(&info));
	if (!philo_init(&info))
		return (1);
	if (!mutex_init(&info))
		return (1);
	if (!create_pthread_philo(&info))
		return (1);
	monitor_thread(&info);
	if (!info.die)
		printf("all philo miam miam\n");

	int i = 0;
	while (i < info.num_philo)
	{
		pthread_join(info.philo[i].id, NULL);
		pthread_mutex_destroy(&(info.fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(info.message));
	// pthread_mutex_destroy(&(info.block_ptime));
	// pthread_mutex_destroy(&(info.philo->block_letime));
	// ft_debug(&info);
	return (0);
}
