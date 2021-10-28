# minishell
42 project philosophers to learn about the threads and the mutex.

--------

## Resume of the subject_Mandatory Part

1. program name : philo  
2. Turn in files: philo/
3. Makefile     : yes
4. Libft        : no
5. Description 	: philosopher with threads and mutex  
6. Arguments	: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]  
7. External functions
```
memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create,  
pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy,  
pthread_mutex_lock, pthread_mutex_unlock
```
  
The specific rules for the mandatory part are:  
1. Each philosopher should be a thread.  
2. One fork between each philosopher, therefore if they are multiple philosophers, there will be a fork at the right and the left of each philosopher.  
3. To avoid philosophers duplicating forks, you should protect the forks state with a mutex for each of them.  

## Resume of the subject_Bonus Part
1. program name : philo_bonus  
2. Turn in files: philo_bonus/
3. Makefile     : yes
4. Libft        : no
5. Description 	: philosopher with processes and semaphore   
6. Arguments	: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]  
7. External functions
```
memset, printf, malloc, free, write, fork, kill,  
exit, pthread_create, pthread_detach, pthread_join,  
usleep, gettimeofday, waitpid, sem_open, sem_close,  
sem_post, sem_wait, sem_unlink  
```
  
For the bonus part, the program takes the same arguments as before and should behave as explained on the General Instructions chapter.  
The specific rules are:  
1. All the forks are in the middle of the table.  
2. They have no states in memory but the number of available forks is represented by a semaphore.  
3. Each philosopher should be a process and the main process should not be a philosopher.  

### Need to understand before starting the project
  
1. One or more philosophers are sitting at a round table either eating, either thinking, either sleeping. While they are eating, they do not think or sleep; while thinking they don’t eat or sleep; and, of course, while sleeping, they do not eat or think.  
2. The philosophers sit at a circular table with a large bowl of spaghetti in the center.  
3. There are some forks on the table. Serving and eating spaghetti with a single fork is very inconvenient, so the philosophers will eat with two forks, one for each hand.  
4. Each time a philosopher finishes eating, they will drop their forks and start sleeping. Once they have finished sleeping, they will start thinking. The simulation stops when a philosopher dies.  
5. Every philosopher needs to eat and they should never starve.  
6. Philosophers don’t speak with each other.  
7. Philosophers don’t know when another philosopher is about to die.  
8. No need to say that philosophers should avoid dying!  

### General Instructions
  
Same Basic rules for both the Mandatory part and the Bonus part:  
1. Global variables are forbidden!  
2. The program should take the following arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
1) number_of_philosophers: is the number of philosophers and also the number of forks.  
2) time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting their last meal or the beginning of the simulation, it dies.  
3) time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time they will need to keep the two forks.  
4) time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping.  
5) number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.  
```
  
3. Each philosopher should be given a number from 1 to ’number_of_philosophers’.  
4. Philosopher number 1 is next to philosopher number ’number_of_philosophers’. Any other philosopher with the number N is seated between philosopher N - 1 and philosopher N + 1.  
  
About the logs of your program:  
5. Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in milliseconds):  
```
timestamp_in_ms X has taken a fork  
timestamp_in_ms X is eating  
timestamp_in_ms X is sleeping  
timestamp_in_ms X is thinking  
timestamp_in_ms X died  
```

6. The status printed should not be scrambled or intertwined with another philosopher’s status.  
7. You can’t have more than 10 ms between the death of a philosopher and when it will print its death.  
8. Again, philosophers should avoid dying!  

