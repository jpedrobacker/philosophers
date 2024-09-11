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

void take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	print_forks(philo, 1);
	pthread_mutex_lock(philo->lfork);
	print_forks(philo, 2);

}

int to_sleep(t_philo *philo)
{
	print_sleep(philo);
	if (!philo_usleep(philo, philo->table->philo_sleep))
		return (0);
	return (1);
}

void return_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

int eat_pls(t_philo *philo)
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
	pthread_mutex_lock(&philo->table->m_eat);
	if (philo->eat_count == philo->table->to_eat)
		philo->stop_eat = 1;
	pthread_mutex_unlock(&philo->table->m_eat);
	return (1);
}

int is_dead(t_philo *philo)
{
	int result;

	result = 0;
	pthread_mutex_lock(&philo->table->m_eat);
	if (philo->table->stop_dinner)
		result = 1;
	pthread_mutex_unlock(&philo->table->m_eat);
	pthread_mutex_lock(&philo->table->m_eat);
	if (philo->death <= get_cur_time())
	{
		philo->is_dead = 1;
		result = 1;
	}
	pthread_mutex_unlock(&philo->table->m_eat);
	return (result);
}
