/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:01 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/01 17:38:30 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
