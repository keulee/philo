#include "includes/philo.h"

void	*philo_engine(void *ptr)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)ptr;
	info = philo->info;
	// if (info->num_philo % 2 == 0) //철학자가 짝수명일때
	// {
		if (philo->index % 2) //짝수번째 철학자일때
		{
			//thinking 먼저하기
			philo_message(info, philo->index, "is thinking");
			ft_usleep(info->eating_time / 1.333, philo);
			// usleep(15000);
		}
	// }
	pthread_mutex_lock(&info->block_die);
	philo_loop(info, philo);
	pthread_mutex_unlock(&info->block_die);
	return (NULL);
}

void	*philo_loop(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (!info->die) //die flag가 0일때. (die flag가 없을때)
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
