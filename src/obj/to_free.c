/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:57:14 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/10 15:35:44 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	end_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nb)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_eat);
	pthread_mutex_destroy(&table->m_stop);
	if (table->forks)
		free(table->forks);
	if (table->thrds)
		free(table->thrds);
	if (table->philo)
		free(table->philo);

}
