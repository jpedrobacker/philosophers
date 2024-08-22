/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:21 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/22 12:05:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


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
	philo_usleep(philo->table->philo_sleep);
	philo->eat_count++;
}

void	return_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->lfork);
	to_sleep(philo);
}
