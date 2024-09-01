# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free
# include <string.h>    // memset
# include <unistd.h>    // usleep, write
# include <sys/time.h>  // gettimeofday
# include <pthread.h>   // pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
# include <sys/types.h> // u_int64_t
# include <stdbool.h>
# include <stdint.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				is_dead;
	int				stop_eat;
	long			start;
	long			death;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct s_table	*table;
	struct s_philo	*next;
}	t_philo;

typedef struct s_table
{
	int				philo_nb; //av[1]
	int				philo_die; //av[2]
	int				philo_eat; //av[3]
	int				philo_sleep; //av[4]
	int				philo_nb_meals; //av[5]
	int				stop_dinner;
	long			start_time;
	t_philo			*philo;
	pthread_t		*thrds;
	pthread_mutex_t	*forks;
} t_table;

long	get_cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	is_dead(t_philo *philo)
{
	if (philo->death <= get_cur_time())
	{
		philo->is_dead = 1;
		return (1);
	}
	return (0);
}

void	one_philo_usleep(int time)
{
	usleep(time * 1000);
}

int	philo_usleep(t_philo *philo, int time)
{
	long	final;

	final = get_cur_time() + time;
	while (final > get_cur_time())
	{
		if (is_dead(philo))
			return (0);
		usleep(500);
	}
	return (1);
}

void	print_think(t_philo *philo)
{
	if (philo->table->stop_dinner == 1 || philo->is_dead == 1)
		return ;
	printf("%ld %d is thinking\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	print_death(t_philo *philo)
{
	printf("%ld %d died\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	print_sleep(t_philo *philo)
{
	if (philo->table->stop_dinner == 1 || philo->is_dead == 1)
		return ;
	printf("%ld %d is sleeping\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	print_eating(t_philo *philo)
{
	if (philo->table->stop_dinner == 1 || philo->is_dead == 1)
		return ;
	printf("%ld %d is eating\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	print_forks(t_philo *philo)
{
	if (philo->table->stop_dinner == 1 || philo->is_dead == 1)
		return ;
	printf("%ld %d has taken a fork\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_forks(philo);
	pthread_mutex_lock(philo->rfork);
	print_forks(philo);
}

void	to_sleep(t_philo *philo)
{
	print_sleep(philo);
	philo_usleep(philo, philo->table->philo_sleep);
}

void	return_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	*check_death(void *philo_pointer)
{
	t_philo	*aux_philo;
	t_philo	*monit;

	aux_philo = (t_philo *)philo_pointer;
	monit = aux_philo;
	while (1)
	{
		if (monit->is_dead == 1)
		{
			print_death(aux_philo);
			aux_philo->table->stop_dinner = 1;
			break ;
		}
		if (aux_philo->eat_count == aux_philo->table->philo_nb_meals)
			aux_philo->stop_eat = 1;
		aux_philo = aux_philo->next;
		monit = aux_philo;
	}
	return (NULL);
}

int	eat_pls(t_philo *philo)
{
	take_fork(philo);
	print_eating(philo);
	philo->death = get_cur_time() + philo->table->philo_die;
	philo->eat_count++;
	return (philo_usleep(philo, philo->table->philo_eat));
}

void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *) p_philo;
	philo->start = get_cur_time();
	philo->death = philo->start + philo->table->philo_die;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		print_think(philo);
		eat_pls(philo);
		return_fork(philo);
		to_sleep(philo);
		//printf("--Philo: %d -> eated: %d--\n", philo->id, philo->eat_count);
		if (philo->stop_eat)
			break ;
		if (philo->table->stop_dinner == 1)
			exit(EXIT_FAILURE);
	}
	return (NULL);
}

void	one_philo_routine(t_table *table)
{
	print_think(table->philo);
	one_philo_usleep(table->philo_die);
	print_death(table->philo);
}

void	start_philo(t_table *table)
{
	int			i;
	pthread_t	monit;

	table->start_time = get_cur_time();
	if (table->philo_nb == 1)
		return (one_philo_routine(table));
	i = -1;
	pthread_create(&monit, NULL, &check_death, (void *)table->philo);
	pthread_detach(monit);
	while (++i < table->philo_nb)
	{
		pthread_create(&table->thrds[i], NULL, &routine, (void *)table->philo);
		table->philo = table->philo->next;
	}
	table->start_time = get_cur_time();
	i = -1;
	while (++i < table->philo_nb)
		pthread_join(table->thrds[i], NULL);
}
