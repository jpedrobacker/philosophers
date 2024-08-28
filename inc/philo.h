/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:36 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/28 18:32:41 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free
# include <string.h>    // memset
# include <unistd.h>    // usleep, write
# include <sys/time.h>  // gettimeofday
# include <pthread.h>   // pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
# include <sys/types.h> // u_int64_t
# include <stdbool.h>
# include <stdint.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_t		monit;
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
	bool			has_dead;
	long			start_time;
	pthread_t		*thrds;
	t_philo			*philo;
	pthread_mutex_t	*forks;
} t_table;

typedef enum e_state
{
	DEAD = 0,
	ALIVE = 1,
	SLEEP = 2,
	THINK = 3,
	EAT = 4
}	t_state;

/*-- Philo funcs --*/
t_philo		*populate_philos(char **av, t_table *table);
void		check_infos(char **av, t_table *table);
void		start_forks(t_table *table);
void		start_philo(t_table *table);
void		end_philo(t_table *table);

/*-- Time funcs --*/
long		get_cur_time(void);
void		philo_usleep(int time_to_sleep);

/*-- Print funcs --*/
void		print_think(t_philo *philo);
void		print_death(t_philo *philo);
void		print_sleep(t_philo *philo);
void		print_eating(t_philo *philo);
void		print_forks(t_philo *philo);

/*-- Common lib funcs --*/
size_t		ft_strlen(char const *str);
long		ft_atol(const char *str);

/*-- Utils funcs --*/
void		to_sleep(t_philo *philo);
void		take_fork(t_philo *philo);
void		return_fork(t_philo *philo);

/*-- Free funcs --*/
void		to_free(t_table *table);

#endif
