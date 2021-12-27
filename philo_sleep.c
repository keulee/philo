#include "includes/philo.h"

void	ft_usleep(long long time)
{
	long long	time_cmp;

	time_cmp = get_time();
	while ((get_time() - time_cmp) < time)
		usleep(time / 10);
}