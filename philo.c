#include "includes/philo.h"
#include <pthread.h>

void *routine()
{
	printf("Test from threads\n");
	// sleep(3);
	// printf("Ending test\n");
}

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	pthread_t t1;

	/*thread create*/
	pthread_create(&t1, NULL, &routine, NULL);  //thread init
	pthread_join(t1, NULL);

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

<<<<<<< HEAD
	gettimeofday(&starttime, NULL);
	usleep(1000 * 1000);
	gettimeofday(&endtime, NULL);
	diff_tv_sec = endtime.tv_sec - starttime.tv_sec;
	diff_tv_usec = (endtime.tv_usec - starttime.tv_usec) / 1000;
	
=======
	// gettimeofday(&starttime, NULL);
	// usleep(1000 * 1000);
	// gettimeofday(&endtime, NULL);
	// diff_tv_sec = endtime.tv_sec - starttime.tv_sec;
	// diff_tv_usec = (endtime.tv_usec - starttime.tv_usec) / 1000;
>>>>>>> d250506c37cb8534fd70149c43e3077098881a4a



	return (0);
}