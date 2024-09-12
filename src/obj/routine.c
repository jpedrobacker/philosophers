/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:01 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/12 10:10:00 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
