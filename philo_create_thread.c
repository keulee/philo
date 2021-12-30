#include "includes/philo.h"

int	create_pthread_philo(t_info *info)
{
	int i;

	i = 0;
	info->s_time = get_time();
	while(i < info->num_philo)
	{
		if (pthread_create(&(info->philo[i].id), NULL, &philo_engine, (void *)&(info->philo[i])))
		{
			printf("Error: create thread failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

// void	*philo_engine(void *ptr)
// {
// 	t_philo *philo;
// 	t_info *info;

// 	philo = ptr;
// 	info = philo->info;
// 	if (philo->index % 2 == 1) // when the index of philo is odd (1, 3, ... 2n - 1)
// 	// thinking first, let the even number philo eat first //짝수번째 철학자는 우선 생각부터 하기
// 	{
// 		philo_message(info, philo->index, "is thinking");
// 		// usleep(info->living_time / 0.333);
// 		usleep(15000);
// 	}
// 	// }
// 	// pthread_mutex_lock(&(info->block_die));
// 	while (!info->die)
// 	{
// 		if (info->num_philo % 2 == 0) //number of philo is even 철학자 수가 짝수이면
// 		{
// 			if (philo->index % 2 == 0) //index of philo is even (odd order of philo) 홀수번째 철학자는 왼쪽 포크부터 잡는다.
// 				pthread_mutex_lock(&(info->fork[philo->l_fork]));
// 			else // 짝수번째 철학자는 오른쪽 포크부터 잡는다.
// 				pthread_mutex_lock(&(info->fork[philo->r_fork]));
// 			philo_message(info, philo->index, "has taken a fork");
// 			if (philo->l_fork == philo->r_fork) //잡은 포크가 같은 포크라면 => 함수 탈출
// 			{
// 				// if (philo->index % 2 == 0)
// 				// 	pthread_mutex_unlock(&(info->fork[philo->l_fork]));
// 				// else
// 				// 	pthread_mutex_unlock(&(info->fork[philo->r_fork]));
// 				ft_usleep(info->living_time * 2, info);
// 				return (NULL);
// 			}
// 			if (philo->index % 2 == 0) //index of philo is even (odd order of philo) 이후 홀수번째 철학자가 오른쪽포크를 마저 잡음.
// 				pthread_mutex_lock(&(info->fork[philo->r_fork]));
// 			else //이후 짝수번째 철학자가 왼쪽 포크를 마저 잡음
// 				pthread_mutex_lock(&(info->fork[philo->l_fork]));
// 			philo_message(info, philo->index, "has taken a fork"); //철학자가 두 포크를 다 잡은 상태
// 			philo_message(info, philo->index, "is eating"); //철학자 식사
// 			pthread_mutex_lock(&(philo->block_letime));
// 			philo->last_eat_time = get_time(); //마지막 식사타임 체크
// 			pthread_mutex_unlock(&(philo->block_letime));
// 			// pthread_mutex_lock(&info->block_eat);
// 			philo->eat_count++; //식사 횟수 체크
// 			// pthread_mutex_unlock(&info->block_eat);
// 			ft_usleep(info->eating_time, info); //식사 시간만큼 딜레이
// 			pthread_mutex_unlock(&(info->fork[philo->l_fork])); //포크 뮤텍스 언락
// 			pthread_mutex_unlock(&(info->fork[philo->r_fork])); //포크 뮤텍스 언락
// 		}
// 		else //number of philo is odd 철학자 수가 홀수이면
// 		{
// 			pthread_mutex_lock(&(info->fork[philo->l_fork]));
// 			philo_message(info, philo->index, "has taken a fork");
// 			pthread_mutex_lock(&(info->fork[philo->r_fork]));
// 			if (philo->l_fork == philo->r_fork)
// 			{
// 				// pthread_mutex_unlock(&(info->fork[philo->l_fork]));
// 				// pthread_mutex_unlock(&(info->fork[philo->r_fork]));
// 				ft_usleep(info->living_time * 2, info);
// 				return (NULL);
// 			}
// 			philo_message(info, philo->index, "has taken a fork");
// 			philo_message(info, philo->index, "is eating");
// 			pthread_mutex_lock(&(philo->block_letime));
// 			philo->last_eat_time = get_time();
// 			pthread_mutex_unlock(&(philo->block_letime));
// 			// pthread_mutex_lock(&info->block_eatcount);
// 			philo->eat_count++;
// 			// pthread_mutex_unlock(&info->block_eatcount);
// 			ft_usleep(info->eating_time, info);
// 			pthread_mutex_unlock(&(info->fork[philo->l_fork]));
// 			pthread_mutex_unlock(&(info->fork[philo->r_fork]));			
// 		}
// 		// pthread_mutex_lock(&(info->block_eat));
// 		if (info->eat)
// 		{
// 			// pthread_mutex_unlock(&(info->block_eat));
// 			break ;
// 		}
// 		// pthread_mutex_unlock(&(info->block_eat));
// 		philo_message(info, philo->index, "is sleeping");
// 		ft_usleep(info->sleeping_time, info);
// 		philo_message(info, philo->index, "is thinking");
// 	}
// 	// pthread_mutex_unlock(&(info->block_die));
// 	return (NULL);
// }

int		philo_eat_first(t_philo *philo, int loop_index)
{
	int i;

	i = 0;
	if (philo->info->num_philo % 2 == 0)
	{
		// if (philo->index % 2 == 1)
			// return (0);
		return (1);
	}
	loop_index = loop_index % philo->info->num_philo;
	while (i < philo->info->num_philo)
	{
		if (philo->index == (loop_index + i * 2) % philo->info->num_philo)
			return (1);
		i++;
	}
	return (0);
}

void	*philo_engine(void *ptr)
{
	t_philo *philo;
	t_info *info;
	int i;

	philo = ptr;
	info = philo->info;
	i = 0;
	if (info->num_philo % 2 == 0) //철학자가 짝수명일때
	{
		if (philo->index % 2) //홀수번째 철학자일때
		{
			//thinking 먼저하기
			philo_message(info, philo->index, "is thinking");
			ft_usleep(info->eating_time / 1.333, info);
		}
	}
	while (!info->die) //die flag가 0일때. (die flag가 없을때)
	{
		if (!philo_eat_first(philo, i))
		{
			philo_message(info, philo->index, "is thinking");
			ft_usleep(info->eating_time, info);
		}
		else
		{
			pthread_mutex_lock(&(info->fork[philo->l_fork]));
			philo_message(info, philo->index, "has taken a fork");
			pthread_mutex_lock(&(info->fork[philo->r_fork]));
			philo_message(info, philo->index, "has taken a fork");
			philo_message(info, philo->index, "is eating");
			philo->last_eat_time = get_time();
			philo->eat_count++;
			ft_usleep(info->eating_time, info);
			pthread_mutex_unlock(&(info->fork[philo->l_fork]));
			pthread_mutex_unlock(&(info->fork[philo->r_fork]));
			philo_message(info, philo->index, "is sleeping");
			ft_usleep(info->sleeping_time, info);
			philo_message(info, philo->index, "is thinking");
			i++;
		}
		if (info->eat)
			return (NULL);
		i++;
	}
	return (NULL);
}