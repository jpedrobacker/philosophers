/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:36 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/18 01:40:42 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <string.h>   // memset
# include <unistd.h>   // usleep, write
# include <sys/time.h> // gettimeofday
# include <pthread.h>  // pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

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
}	t_mutex;	

typedef struct s_philo
{
	int		i;
	char	*str;
	t_infos	infos;
	t_mutex	*mutex;
	struct s_philo *next;
}	t_philo;


size_t	ft_strlen(char const *str);
long	ft_atol(const char *str);

#endif
