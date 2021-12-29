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
	free_thread(&info);
	if (!info.die)
		printf("all philo miam miam\n");

	// ft_debug(&info);
	return (0);
}
