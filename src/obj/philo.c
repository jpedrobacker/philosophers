/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/29 12:26:23 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_eat(t_philo *philo)
{
	if (philo->table->philo_nb_meals == -1)
		return (false);
	if (philo->table->philo_nb_meals > philo->eat_count)
		return (false);
	return (true);
}

void	*check_death(void *philo_pointer)
{
	t_philo	*aux;

	aux = (t_philo *)philo_pointer;
	while (1)
	{
		if (aux->is_dead == true)
		{
			aux->table->stop_dinner = true;
			print_death(aux);
			exit(EXIT_FAILURE);
		}
		aux = aux->next;
	}
	return (NULL);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;

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
		//printf("--Philo: %d -> eated: %d--\n", philo->id, philo->eat_count);
		if (get_cur_time() - philo->last_meal <= philo->table->philo_die)
			philo->is_dead = true;
		if (check_eat(philo) != false)
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
	int	i;

	table->start_time = get_cur_time();
	pthread_create(&table->philo->monit, NULL, &check_death, (void *)table->philo);
	pthread_detach(table->philo->monit);
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

	i = -1;
	while (++i < table->philo_nb)
		pthread_mutex_destroy(&table->forks[i]);
	if (table->forks)
		free(table->forks);
	if (table->thrds)
		free(table->thrds);
	if (table->philo)
		free(table->philo);
}
