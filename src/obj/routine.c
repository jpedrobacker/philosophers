/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:01 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/12 10:47:07 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_think(t_philo *philo)
{
	printf("%ld philo: %d is thinking\n", start_time() - philo->table->start_time, philo->id);
}

void	print_death(t_philo *philo)
{
	printf("%ld philo: %d died\n", start_time() - philo->table->start_time, philo->id);
}

void	print_sleep(t_philo *philo)
{
	printf("%ld philo : %d is sleeping\n", start_time() - philo->table->start_time, philo->id);
}

void	print_eating(t_philo *philo)
{
	printf("%ld philo : %d is eating\n", start_time() - philo->table->start_time, philo->id);
}

void	print_forks(t_philo *philo)
{
	printf("%ld philo : %d has taken a fork\n", start_time() - philo->table->start_time, philo->id);
}
