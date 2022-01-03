/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_thread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:15:41 by keulee            #+#    #+#             */
/*   Updated: 2022/01/03 22:15:43 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
