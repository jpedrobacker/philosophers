/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/01 12:49:24 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*check_death(void *philo_pointer)
{
	t_philo	*aux_philo;
	t_philo	*monitor;

	aux_philo = (t_philo *)philo_pointer;
	monitor = (t_philo *)philo_pointer;
	while (1)
	{
		if (monitor->is_dead)
		{
			print_death(aux_philo);
			break ;
		}
		if (monitor->eat_count == aux_philo->table->philo_nb_meals)
			aux_philo->stop_eat = 1;
		aux_philo = aux_philo->next;
		monitor = aux_philo;
	}
	return (NULL);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *) p_philo;
	philo->start = get_cur_time();
	philo->death = philo->start + philo->table->philo_die;
	if (philo->id % 2 == 0)
		philo_usleep(1);
	while (1)
	{
		print_think(philo);
		take_fork(philo);
		print_eating(philo);
		philo_usleep(philo->table->philo_eat);
		return_fork(philo);
		printf("--Philo: %d -> eated: %d--\n", philo->id, philo->eat_count);
		if (philo->stop_eat == 1)
			break;
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
	int			i;
	pthread_t	monit;

	table->start_time = get_cur_time();
	if (table->philo_nb == 1)
		return (one_philo_routine(table));
	i = -1;
	pthread_create(&monit, NULL, &check_death, (void *)table->philo);
	pthread_detach(monit);
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
