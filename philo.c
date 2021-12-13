#include "includes/philo.h"
#include <pthread.h>

void *routine(void *arg)
{
	pthread_t tid;
	
	tid = pthread_self();

	int i = 0;
	printf("\ttid: %x \n", tid);
	while (i < 10)
	{
		printf("\tnew thread: %d\n", i);
		i++;
		usleep(1000 * 1000);
	}
	printf("Ending thread test\n");
}

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	pthread_t t1;
	// pthread_t t2;
	// pthread_t t3;

	/*thread create*/
	pthread_create(&t1, NULL, &routine, NULL);  //thread init
	printf("main tid:%x\n", pthread_self());
	// pthread_join(t1, NULL);
	pthread_detach(t1);
	int i = 0;
	while (i < 42)
	{
		printf("main : %d\n", i);
		i++;
		usleep(1000 * 1000);
	}
	// printf("here\n");
	// pthread_create(&t2, NULL, &routine, NULL);  //thread init
	// pthread_join(t2, NULL);

	// struct timeval;
	// gettimeofday();

	// //usleep test
	// printf("test usleep\n");
	// printf("text appears in 10 sec\n");
	// int i = 1;
	// while (i <= 10)
	// {
	// 	printf("%d sec\n", i++);
	// 	usleep(1000 * 1000); // 마이크로세컨드 -> 1/1000000
	// }
	// printf("HELLO\n");
	
	// gettimeofday test
	// int		t;
	// struct timeval tv;

	// t = gettimeofday(&tv, NULL);
	// if (t == -1)
	// {
	// 	perror("gettimeofday() call error");
	// 	return (-1);
	// }
	// printf("tv sec : tv usec = %ld : %d\n", tv.tv_sec, tv.tv_usec / 15000);

	// struct timeval starttime;
	// struct timeval endtime;
	// double diff_tv_sec;
	// double diff_tv_usec;

	// gettimeofday(&starttime, NULL);
	// usleep(1000 * 1000);
	// gettimeofday(&endtime, NULL);
	// diff_tv_sec = endtime.tv_sec - starttime.tv_sec;
	// diff_tv_usec = (endtime.tv_usec - starttime.tv_usec) / 1000;
	



	return (0);
}
