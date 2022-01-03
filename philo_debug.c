/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:15:49 by keulee            #+#    #+#             */
/*   Updated: 2022/01/03 22:15:50 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_debug(t_info *info)
{
	printf("\033[38;5;30m = DEBUG Line ==============\n");
	printf("num_philo	| %d\n", info->num_philo);
	printf("time_to_die	| %d\n", info->living_time);
	printf("time_to_eat	| %d\n", info->eating_time);
	printf("time_to_sleep	| %d\n", info->sleeping_time);
	printf("max_eattime	| %d\n", info->max_eatcount);
	printf("===========================\033[0m\n");
}
