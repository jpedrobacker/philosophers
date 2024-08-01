/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:36 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/01 14:35:13 by jbergfel         ###   ########.fr       */
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

typedef struct s_infos
{
	int	philo_nums;
	int	philo_die;
	int	philo_eat;
	int	philo_sleep;
	int	philo_must_eat;
	//color or name;
}	t_infos;

typedef struct s_mutex
{
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_eaten;
	pthread_mutex_t	mutex_print;
	int				eaten;
	int				stop;
}	t_mutex;

typedef struct s_philo
{
	int				philo_num;
	int				r_fork;
	int				l_fork;
	int				has_eaten;
	int				has_died;
	u_int64_t		start_time;
	pthread_t		philo_thrds;
	t_infos			*infos;
	t_mutex			*mutex;
	struct s_philo	*next;
}	t_philo;

/*-- Philo funcs --*/
t_philo		*populate_philos(char **av, t_infos *infos, t_mutex *mutex);
void		start_philo(char **av, t_philo *philo, t_infos *infos);
void		start_mutex(t_mutex *mutex, t_infos *infos);

/*-- Time funcs --*/
u_int64_t	start_time(void);
void		philo_usleep(u_int64_t time_to_sleep);

/*-- Common lib funcs --*/
size_t	ft_strlen(char const *str);
long	ft_atol(const char *str);

/*-- Utils funcs --*/
void	print_elems(t_philo *philos);

/*-- Free funcs --*/
void	to_free(t_philo *philo);

#endif
