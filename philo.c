#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (!parse_init(ac, av, &info))
		return (1);
	if (!philo_init(&info))
		return (1);
	if (!mutex_init(&info))
		return (1);
	if (info.num_philo == 1)
		return (one_philo(&info));
	if (!create_pthread_philo(&info))
		return (1);
	monitor_thread(&info);
	free_thread(&info);
	if (!info.die)
		printf("All philo miam miam at least %d times\n", \
		info.max_eatcount);
	if (info.philo)
		free(info.philo);
	if (info.fork)
		free(info.fork);
	return (0);
}
