/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:16:37 by keulee            #+#    #+#             */
/*   Updated: 2022/01/03 22:16:38 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	time_gap;

	pthread_mutex_lock(&(philo->info->block_ptime));
	time_gap = get_time();
	pthread_mutex_unlock(&(philo->info->block_ptime));
	while ((get_time() - time_gap) < time)
	{
		if (philo->info->num_philo < 50)
			usleep(100);
		else
			usleep(1000);
	}
}
