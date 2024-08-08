/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/05 12:46:19 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *philo_pointer)
{
	(void) philo_pointer;
}

void	one_philo_routine(t_table *table)
{
	print_think(table->philo);
	philo_usleep(table->philo_die);
	print_death(table->philo);
}

void	start_philo(t_table *table)
{
	int	i;

	table->start_time = start_time();
	if (table->philo_nb == 1)
		return (one_philo_routine(table));
	i = 0;
	while (i < table->philo_nb)
	{
		pthread_create(&table->thrds[i], NULL, &routine, &table->philo);
		i++;
		table->philo = table->philo->next;
	}
	table->start_time = start_time();
	i = 0;
	while (i < table->philo_nb)
	{
		pthread_join(table->thrds[i], NULL);
		i++;
	}
}
