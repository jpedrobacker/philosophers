/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:36 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/12 13:26:43 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	int				philo_nb;
	int				philo_die;
	int				philo_eat;
	int				philo_sleep;
	int				to_eat;
	long			start_time;
	int				eaten;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	int				stop_dinner;
}	t_table;

/*-- Philo funcs --*/
t_philo	*populate_philos(char **av, t_table *table);
int		check_infos(char **av, t_table *table);
void	start_forks(t_table *table);
void	start_philo(t_table *table);
int		is_dead(t_philo *philo);

/*-- Time funcs --*/
long	get_cur_time(void);
int		philo_usleep(t_philo *philo, int time_to_sleep);
void	one_philo_usleep(int time);

/*-- Print funcs --*/
void	print_think(t_philo *philo);
void	print_death(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_eating(t_philo *philo);
void	print_forks(t_philo *philo);

/*-- Common lib funcs --*/
size_t	ft_strlen(char const *str);
long	ft_atol(const char *str);

/*-- Utils funcs --*/
void	take_fork(t_philo *philo);
int		eat_pls(t_philo *philo);
void	return_fork(t_philo *philo);
void	to_sleep(t_philo *philo);

/*-- Free funcs --*/
void	end_philo(t_table *table);
void	clear_philos(t_philo *philo);

#endif
