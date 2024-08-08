/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:01 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/05 12:38:46 by jbergfel         ###   ########.fr       */
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
