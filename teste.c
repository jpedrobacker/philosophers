# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdint.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648

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
	int				to_eat; //av[5]
	long			start_time;
	t_philo			*philo;
	pthread_t		*thrds;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	int				stop_dinner;
}	t_table;

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	ft_atol(const char *str)
{
	long	res;
	long	i;
	long	s;

	res = 0;
	i = 0;
	s = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		s = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (str[i] - 48) + (res * 10);
		i++;
	}
	return (res * s);
}

long	get_cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_forks(philo, 1);
	pthread_mutex_lock(philo->rfork);
	print_forks(philo, 2);
}

int	to_sleep(t_philo *philo)
{
	print_sleep(philo);
	if (!philo_usleep(philo, philo->table->philo_sleep))
		return (0);
	return (1);
}

void	return_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

int	eat_pls(t_philo *philo)
{
	take_fork(philo);
	print_eating(philo);
	pthread_mutex_lock(&philo->table->m_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->m_eat);
	if (!philo_usleep(philo, philo->table->philo_eat))
	{
		return_fork(philo);
		return (0);
	}
	return_fork(philo);
	philo->death = get_cur_time() + philo->table->philo_die;
	return (1);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->m_stop);
	if (philo->table->stop_dinner)
	{
		pthread_mutex_unlock(&philo->table->m_stop);
		return (1);
	}
	if (philo->death <= get_cur_time())
	{
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->table->m_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->m_stop);
	return (0);
}

void	add_infos(t_philo *aux, t_table *table, int i)
{
	aux->table = table;
	aux->eat_count = 0;
	aux->start = 0;
	aux->death = 0;
	aux->is_dead = 0;
	aux->lfork = &table->forks[i];
	aux->rfork = &table->forks[(i + 1) % table->philo_nb];
}

t_philo	*populate_philos(char **av, t_table *table)
{
	t_philo		*head;
	t_philo		*aux;
	t_philo		*last;
	int			i;
	int			nb_ph;

	head = NULL;
	i = -1;
	nb_ph = atol(av[1]);
	while (nb_ph > ++i)
	{
		aux = malloc(sizeof(t_philo));
		aux->id = i + 1;
		add_infos(aux, table, i);
		aux->next = NULL;
		if (head == NULL)
			head = aux;
		else
			last->next = aux;
		last = aux;
	}
	aux->next = head;
	return (head);
}

void	start_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	check_infos(char **av, t_table *table)
{
	int	i;

	i = ft_atol(av[1]);
	if (i < 200 && i > 0)
		table->philo_nb = i;
	else
		printf("Wrong number of philos!\n");
	table->philo_die = ft_atol(av[2]);
	table->philo_eat = ft_atol(av[3]);
	table->philo_sleep = ft_atol((av[4]));
	table->stop_dinner = 0;
	if (av[5])
		table->to_eat = ft_atol((av[5]));
	else
		table->to_eat = -1;
	table->thrds = malloc(sizeof(pthread_t) * table->philo_nb);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nb);
	table->philo = populate_philos(av, table);
	pthread_mutex_init(&table->m_print, NULL);
	pthread_mutex_init(&table->m_stop, NULL);
	pthread_mutex_init(&table->m_eat, NULL);
}

void	end_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nb)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_eat);
	pthread_mutex_destroy(&table->m_stop);
	if (table->forks)
		free(table->forks);
	if (table->thrds)
		free(table->thrds);
	if (table->philo)
		free(table->philo);

}

void	print_think(t_philo *philo)
{
	if (philo->table->stop_dinner == 1 || philo->is_dead == 1)
		return ;
	pthread_mutex_lock(&philo->table->m_print);
	printf("%ld %d is thinking\n", get_cur_time() - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->m_print);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->m_print);
	printf("%ld %d died\n", get_cur_time() - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->m_print);
}

void	print_sleep(t_philo *philo)
{
	if (philo->table->stop_dinner == 1 || philo->is_dead == 1)
		return ;
	pthread_mutex_lock(&philo->table->m_print);
	printf("%ld %d is sleeping\n", get_cur_time() - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->m_print);
}

void	print_eating(t_philo *philo)
{
	if (philo->table->stop_dinner == 1 || philo->is_dead == 1)
		return ;
	pthread_mutex_lock(&philo->table->m_print);
	printf("%ld %d is eating\n", get_cur_time() - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->m_print);
}

void	print_forks(t_philo *philo, int fork_num)
{
	if (philo->table->stop_dinner == 1 || philo->is_dead == 1)
		return ;
	(void) fork_num;
	pthread_mutex_lock(&philo->table->m_print);
	printf("%ld %d has taken a fork\n", get_cur_time() - philo->table->start_time, philo->id/*, fork_num*/);
	pthread_mutex_unlock(&philo->table->m_print);
}

void	*check_death(void *philo_pointer)
{
	t_philo	*philo;
	t_philo	*monit;

	philo = (t_philo *)philo_pointer;
	monit = philo;
	while (1)
	{
		pthread_mutex_lock(&philo->table->m_eat);
		if (monit->eat_count == philo->table->to_eat)
			philo->stop_eat = 1;
		pthread_mutex_unlock(&philo->table->m_eat);
		if (philo->is_dead)
		{
			philo->table->stop_dinner = 1;
			print_death(philo);
			break ;
		}
		philo = philo->next;
		monit = philo;
	}
	return (NULL);
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
		if (!eat_pls(philo))
			break ;
		if (!to_sleep(philo))
			break ;
		pthread_mutex_lock(&philo->table->m_eat);
		if (philo->stop_eat || philo->table->stop_dinner)
		{
			pthread_mutex_unlock(&philo->table->m_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->table->m_eat);

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
	t_philo		*philo;

	table->start_time = get_cur_time();
	philo = table->philo;
	if (table->philo_nb == 1)
		return (one_philo_routine(table));
	pthread_create(&monit, NULL, &check_death, (void *)philo);
	pthread_detach(monit);
	i = -1;
	while (++i < table->philo_nb)
	{
		pthread_create(&table->thrds[i], NULL, &routine, (void *)philo);
		philo = philo->next;
	}
	i = -1;
	while (++i < table->philo_nb)
		pthread_join(table->thrds[i], NULL);
	pthread_join(monit, NULL);
}

int	validate_input(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("Wrong num of args!\n");
		return (0);
	}
	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!validate_input(ac, av))
		return (0);
	check_infos(av, &table);
	start_forks(&table);
	start_philo(&table);
	end_philo(&table);
}
