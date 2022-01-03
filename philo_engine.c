/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:15:57 by keulee            #+#    #+#             */
/*   Updated: 2022/01/03 22:15:59 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
1. 	먼저 짝수번째 철학자를 thinking을 먼저 주면서 eating에 holding을 걸어줌
2. 	philo_loop으로 들어가서 철학자의 수가 짝수 또는 홀수일때,
	철학자 순번이 짝수번일때 홀수번일때를 나눠 thinking/ eating-sleeping-thinking을 하게 해준다.
3.	info->eat (최소 eating 횟수가 존재하고, 철학자들 모두가 그만큼 식사를 했다는 flag)가
	1이 되면 philo_loop을 벗어남.
	그 외에는, 게속해서 philo_loop에서 eating-sleepling-thinking을 반복.
*/

/*
philo_engine 함수 안 철학자가 짝수일때 코드를 살릴지 아닐지 고민해야함.
 if (info->num_philo % 2 == 0) //철학자가 짝수명일때
 {
	if (philo->index % 2) //짝수번째 철학자일때
	{
		philo_message(info, philo->index, "is thinking");
		ft_usleep(info->eating_time / 1.333, philo);
	}
 }
*/

void	*philo_engine(void *ptr)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)ptr;
	info = philo->info;
	if (philo->index % 2)
	{
		philo_message(info, philo->index, "is thinking");
		ft_usleep(info->eating_time / 1.333, philo);
	}
	pthread_mutex_lock(&info->block_die);
	philo_loop(info, philo);
	pthread_mutex_unlock(&info->block_die);
	return (NULL);
}

void	*philo_loop(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (!info->die)
	{
		pthread_mutex_unlock(&info->block_die);
		if (!philo_eat_first(philo, i))
			philo_think_first(info, philo);
		else
		{
			philo_eat_sleep_think(philo);
			i++;
		}
		pthread_mutex_lock(&(info->block_eat));
		if (info->eat)
		{
			pthread_mutex_unlock(&(info->block_eat));
			return (NULL);
		}
		pthread_mutex_unlock(&(info->block_eat));
		i++;
		pthread_mutex_lock(&info->block_die);
	}
	return (NULL);
}

int	philo_eat_first(t_philo *philo, int loop_index)
{
	int	i;

	i = 0;
	if (philo->info->num_philo % 2 == 0)
		return (1);
	loop_index = loop_index % philo->info->num_philo;
	while (i < philo->info->num_philo)
	{
		if (philo->index == (loop_index + i * 2) % philo->info->num_philo)
			return (1);
		i++;
	}
	return (0);
}

void	philo_think_first(t_info *info, t_philo *philo)
{
	philo_message(info, philo->index, "is thinking");
	ft_usleep(info->eating_time, philo);
}

void	philo_eat_sleep_think(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&(info->fork[philo->l_fork]));
	philo_message(info, philo->index, "has taken a fork");
	pthread_mutex_lock(&(info->fork[philo->r_fork]));
	philo_message(info, philo->index, "has taken a fork");
	philo_message(info, philo->index, "is eating");
	pthread_mutex_lock(&(philo->block_letime));
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&(philo->block_letime));
	pthread_mutex_lock(&(info->block_eatcount));
	philo->eat_count++;
	pthread_mutex_unlock(&(info->block_eatcount));
	ft_usleep(info->eating_time, philo);
	pthread_mutex_unlock(&(info->fork[philo->l_fork]));
	pthread_mutex_unlock(&(info->fork[philo->r_fork]));
	philo_message(info, philo->index, "is sleeping");
	ft_usleep(info->sleeping_time, philo);
	philo_message(info, philo->index, "is thinking");
}
