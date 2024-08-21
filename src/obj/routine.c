/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:01 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/21 14:22:15 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_think(t_philo *philo)
{
	printf("time: %ld philo: %d is thinking\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	print_death(t_philo *philo)
{
	printf("time: %ld philo: %d died\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	print_sleep(t_philo *philo)
{
	printf("time: %ld philo : %d is sleeping\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	print_eating(t_philo *philo)
{
	printf("time: %ld philo : %d is eating\n", get_cur_time() - philo->table->start_time, philo->id);
}

void	print_forks(t_philo *philo)
{
	printf("time: %ld philo : %d has taken a fork\n", get_cur_time() - philo->table->start_time, philo->id);
}
