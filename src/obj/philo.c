/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/12 11:27:35 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_eat(t_table *table)
{
	(void) table;
	return (1);
}

void	*routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *) philo_pointer;
	philo->last_meal = start_time();
	//monitor routine to check deaths
	if (philo->id % 2 == 0)
		philo_usleep(1);
	while (!philo->table->has_dead && !check_eat(philo->table))
	{
		print_think(philo);
		//take fork func if necessary
		print_eating(philo);
		philo->last_meal = start_time();
		philo_usleep(philo->table->philo_eat - 5);
		//return fork to table func
	}
	return (NULL);
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
