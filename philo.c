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
	if (!info.die)
		printf("all philo miam miam\n");

	int i = 0;
	while (i < info.num_philo)
	{
		pthread_join(info.philo[i].id, NULL);
		// pthread_detach(info.philo[i].id);
		pthread_mutex_destroy(&(info.fork[i]));
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