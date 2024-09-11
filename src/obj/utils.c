/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:21 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/10 15:44:12 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_forks(philo, 1);
	pthread_mutex_lock(philo->rfork);
	print_forks(philo, 2);
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

int	eat_pls(t_philo *philo)
{
	take_fork(philo);
	print_eating(philo);
	philo->death = get_cur_time() + philo->table->philo_die;
	pthread_mutex_lock(&philo->table->m_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->m_eat);
	if (!philo_usleep(philo, philo->table->philo_eat))
	{
		return_fork(philo);
		return (0);
	}
	return_fork(philo);
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
