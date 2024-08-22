/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/22 12:07:19 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_eat(t_table *table)
{
	int	i;

	i = 0;
	if (table->philo_nb_meals == -1)
		return (false);
	while (i < table->philo_nb)
	{
		if (table->philo->eat_count < table->philo_nb_meals)
			return (false);
		i++;
		table->philo = table->philo->next;
	}
	return (true);
}

void	*routine(void *p_philo)
{
	t_philo *philo;

	philo = (t_philo *) p_philo;
	philo->last_meal = get_cur_time();
	if (philo->id % 2 == 0)
		philo_usleep(1);
	while (1)
	{
		print_think(philo);
		take_fork(philo);
		print_eating(philo);
		philo->last_meal = get_cur_time();
		philo_usleep(philo->table->philo_eat);
		return_fork(philo);
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

	table->start_time = get_cur_time();
	if (table->philo_nb == 1)
		return (one_philo_routine(table));
	i = -1;
	while (++i < table->philo_nb)
	{
		pthread_create(&table->thrds[i], NULL, &routine, (void *)table->philo);
		table->philo = table->philo->next;
	}
	table->start_time = get_cur_time();
	i = -1;
	while (++i < table->philo_nb)
		pthread_join(table->thrds[i], NULL);
}

void	end_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	if (table->forks)
		free(table->forks);
	if (table->thrds)
		free(table->thrds);
	if (table->philo)
		free(table->philo);
}
