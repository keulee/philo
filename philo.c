#include "includes/philo.h"

void	*philo_engine(void *arg_ptr)
{
	t_philo *philo;
	t_info	*info;

	philo = (t_philo *)arg_ptr;
	info = philo->info;
	if (info->num_philo % 2 == 1) //짝수번째 필로
	{
		if (philo->index % 2 == 0) //짝수번째 필로 먼저 생각하게 한다. 홀수번째 필로는 먼저 먹는걸로
		{
			// pthread_mutex_lock(&(info->message));
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is thinking");
			// pthread_mutex_unlock(&(info->message));
			// pthread_mutex_lock(&(info->block_ptime));
			philo->present_time = get_time();
			// pthread_mutex_unlock(&(info->block_ptime));
			while (get_time() - philo->present_time < info->eating_time)
				usleep(100);
		}
	}
	while (!info->die)
	{
		// if (philo->index % 2 == 1) // 홀수 일때 먹기
		// {
			pthread_mutex_lock(&(info->fork[philo->l_fork]));
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			pthread_mutex_lock(&(info->fork[philo->r_fork]));
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "has taken a fork");
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is eating");
			pthread_mutex_lock(&(philo->block_letime));
			philo->last_eat_time = get_time();
			pthread_mutex_unlock(&(philo->block_letime));
			philo->eat_count++;
			pthread_mutex_lock(&(info->block_ptime));
			philo->present_time = get_time();
			pthread_mutex_unlock(&(info->block_ptime));
			while (get_time() - philo->present_time < info->eating_time)
				usleep(100);
			pthread_mutex_unlock(&(info->fork[philo->l_fork]));
			pthread_mutex_unlock(&(info->fork[philo->r_fork]));
		// }
		if (philo->eat_count)
		{
			pthread_mutex_lock(&(info->message));
			printf("%lld %d %s\n", get_time() - info->s_time, philo->index + 1, "is sleeping");
			pthread_mutex_unlock(&(info->message));
			pthread_mutex_lock(&(info->block_ptime));
			philo->present_time = get_time();
			pthread_mutex_unlock(&(info->block_ptime));
			while (get_time() - philo->present_time < info->sleeping_time)
				usleep(100);
		}
	}

	return (NULL);
}

void	monitor_thread(t_info *info)
{
	int i;

	i = 0;
	while (i < info->num_philo)
	{
	// printf("here\n");
		pthread_mutex_lock(&(info->philo[i].block_letime));
		info->philo[i].last_eat_time = get_time();
		// printf("last eat time %d: %lld\n", i, info->philo[i].last_eat_time);
		pthread_mutex_unlock(&(info->philo[i].block_letime));
		i++;
	}
	while (!(info->eat))
	{
		i = 0;
		int how_many_time_eat = 0;
		while (i < info->num_philo)
		{
			pthread_mutex_lock(&(info->philo[i].block_letime));
			if (get_time() - info->philo[i].last_eat_time > info->living_time)
			{
				printf("%lld %d %s\n", get_time() - info->s_time, info->philo[i].index + 1, "died");
				info->die = 1;
				break ;
			}
			pthread_mutex_unlock(&(info->philo[i].block_letime));
			i++;
		}
		i = 0;
		while (info->max_eatcount && i < info->num_philo)
		{
			if (info->philo[i].eat_count >= info->max_eatcount)
			{
				// printf("here\n");
				how_many_time_eat++;
			}
			i++;
		}
		if (how_many_time_eat == info->num_philo)
			info->eat = 1;
	}
}

void	ft_test(t_info *info)
{
	int i;
	int eat_c;

	i = 0;
	eat_c = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_lock(&(info->philo[i].block_letime));
		info->philo[i].last_eat_time = get_time();
		pthread_mutex_unlock(&(info->philo[i].block_letime));
		i++;
	}
	while (!(info->eat))
	{
		while (i < info->num_philo && !(info->die))
		{
			// pthread_mutex_lock(&(info->protect_die));
			if (get_time() - info->philo[i].last_eat_time < info->living_time)
			{
				printf("%lld %d %s\n", get_time() - info->s_time, info->philo[i].index + 1, "died");
				info->die = 1;
			}
			// pthread_mutex_unlock(&(info->protect_die));
			i++;
		}
		if (info->die == 1)
			break ;
		i = 0;
		while (i < info->num_philo && info->max_eatcount)
		{
			if (info->philo[i].eat_count >= info->max_eatcount)
				eat_c++;
			i++;
		}
		if (eat_c == info->num_philo)
			info->eat = 1;
	}
}

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
	ft_test(&info);
	if (!info.die)
		printf("all philo miam miam\n");
	// monitor_thread(&info);
	//monitor_thread_function
	//to do : make function that monitor all changes of thread 
	//(which will be working with create_thread_philo)
	// if (!(info.die))
		// printf("done\n");

	// printf("eat time : %d\n", info.eat);
	int i = 0;
	while (i < info.num_philo)
	{
		pthread_join(info.philo[i].id, NULL);
		// pthread_detach(info.philo[i].id);
		// pthread_mutex_destroy(&(info.fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(info.message));
	// pthread_mutex_destroy(&(info.block_ptime));
	// pthread_mutex_destroy(&(info.philo->block_letime));
	// ft_debug(&info);
	return (0);
}

/*
** pthread_t t1;
** pthread_t t2;
**
** pthread_mutex_init(&mutex, NULL);
**
** pthread_create(&t1, NULL, count, (void *)"\tt1");
** pthread_create(&t2, NULL, count, (void *)"t2");
**
** pthread_join(t1, NULL);
** pthread_join(t2, NULL);
**
** pthread_mutex_destroy(&mutex);
**
** pthread_mutex_t mutex;
** int	cnt = 0;
**
** void *routine(void *arg)
** {
** 	pthread_t tid;
**	
** 	tid = pthread_self();
**
** 	int i = 0;
** 	printf("\ttid: %x \n", tid);
** 	while (i < 10)
** 	{
** 		printf("\tnew thread: %d\n", i);
** 		i++;
** 		usleep(1000 * 1000);
** 	}
** 	printf("Ending thread test\n");
** }
**
** void	*count(void *arg)
** {
** 	int i;
** 	char *name = (char *)arg;
**
** 	
**
** 	/////////////// critical section /////////////////
** 	cnt = 0;
** 	while (i < 10)
** 	{
** 		printf("%s cnt: %d\n", name, cnt);
** 		cnt++;
** 		usleep(1000000);
** 		i++;
** 	}
** 	//////////////// critical section //////////////////
**
** 	pthread_mutex_unlock(&mutex);
** }
**
** //thread create
** pthread_create(&t1, NULL, &routine, NULL);  //thread init
** printf("main tid:%x\n", pthread_self());
** // pthread_join(t1, NULL);
** pthread_detach(t1);
** int i = 0;
** while (i < 42)
** {
** 	printf("main : %d\n", i);
** 	i++;
** 	usleep(1000 * 1000);
** }
** printf("here\n");
** pthread_create(&t2, NULL, &routine, NULL);  //thread init
** pthread_join(t2, NULL);
**
** struct timeval;
** gettimeofday();
**
** //usleep test
** printf("test usleep\n");
** printf("text appears in 10 sec\n");
** int i = 1;
** while (i <= 10)
** {
** 	printf("%d sec\n", i++);
** 	usleep(1000 * 1000); // 마이크로세컨드 -> 1/1000000
** }
** printf("HELLO\n");
**
** gettimeofday test
** int		t;
** struct timeval tv;
**
** t = gettimeofday(&tv, NULL);
** if (t == -1)
** {
** 	perror("gettimeofday() call error");
** 	return (-1);
** }
** printf("tv sec : tv usec = %ld : %d\n", tv.tv_sec, tv.tv_usec / 15000);
**
** struct timeval starttime;
** struct timeval endtime;
** double diff_tv_sec;
** double diff_tv_usec;
**
** gettimeofday(&starttime, NULL);
** usleep(1000 * 1000);
** gettimeofday(&endtime, NULL);
** diff_tv_sec = endtime.tv_sec - starttime.tv_sec;
** diff_tv_usec = (endtime.tv_usec - starttime.tv_usec) / 1000;
*/