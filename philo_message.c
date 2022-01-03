/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:16:19 by keulee            #+#    #+#             */
/*   Updated: 2022/01/03 22:16:20 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	philo_message(t_info *info, int index, char *message)
{
	pthread_mutex_lock(&(info->message));
	pthread_mutex_lock(&info->block_die);
	if (!info->die)
		printf("%lld %d %s\n", get_time() - info->s_time, index + 1, message);
	pthread_mutex_unlock(&info->block_die);
	pthread_mutex_unlock(&(info->message));
}
