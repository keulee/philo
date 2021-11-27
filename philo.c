#include "includes/philo.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;

	// struct timeval;
	// gettimeofday();

	/* usleep test
	printf("test usleep\n");
	printf("text appears in 10 sec\n");
	int i = 1;
	while (i <= 10)
	{
		printf("%d sec\n", i++);
		usleep(1000000); // 마이크로세컨드 -> 1/1000000
	}
	printf("HELLO\n");
	*/
	
	int		t;
	struct timeval tv;

	t = gettimeofday(&tv, NULL);
	if (t == -1)
	{
		perror("gettimeofday() call error");
		return (-1);
	}
	printf("tv sec : tv usec = %ld : %d\n", tv.tv_sec, tv.tv_usec / 15000);

	return (0);
}
