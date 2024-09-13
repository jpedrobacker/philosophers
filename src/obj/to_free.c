/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:57:14 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/12 13:16:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clear_philos(t_philo *philo)
{
	int		i;
	int		size;
	t_philo	*tmp;

	if (!philo)
		return ;
	i = -1;
	tmp = philo;
	size = philo->table->philo_nb;
	while (++i < size)
	{
		philo = tmp->next;
		free(tmp);
		tmp = philo;
	}
}

void	end_philo(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->philo_nb)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_eat);
	pthread_mutex_destroy(&table->m_stop);
	if (table->forks)
		free(table->forks);
	clear_philos(table->philo);
}
