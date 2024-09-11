/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/10 15:36:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*check_death(void *philo_pointer)
{
	t_philo	*philo;
	t_philo	*monit;

	philo = (t_philo *)philo_pointer;
	monit = philo;
	while (1)
	{
		pthread_mutex_lock(&philo->table->m_eat);
		if (monit->eat_count == philo->table->to_eat)
			philo->stop_eat = 1;
		pthread_mutex_unlock(&philo->table->m_eat);
		if (philo->is_dead)
		{
			philo->table->stop_dinner = 1;
			print_death(philo);
			break ;
		}
		philo = philo->next;
		monit = philo;
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
		usleep(100);
	while (1)
	{
		print_think(philo);
		if (!eat_pls(philo))
			break ;
		if (!to_sleep(philo))
			break ;
		pthread_mutex_lock(&philo->table->m_eat);
		if (philo->stop_eat || philo->table->stop_dinner)
		{
			pthread_mutex_unlock(&philo->table->m_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->table->m_eat);

	}
	return (NULL);
}

void	one_philo_routine(t_table *table)
{
	print_think(table->philo);
	one_philo_usleep(table->philo_die);
	print_death(table->philo);
}

void	start_philo(t_table *table)
{
	int			i;
	pthread_t	monit;
	t_philo		*philo;

	table->start_time = get_cur_time();
	philo = table->philo;
	if (table->philo_nb == 1)
		return (one_philo_routine(table));
	pthread_create(&monit, NULL, &check_death, (void *)philo);
	pthread_detach(monit);
	i = -1;
	while (++i < table->philo_nb)
	{
		pthread_create(&table->thrds[i], NULL, &routine, (void *)philo);
		philo = philo->next;
	}
	i = -1;
	while (++i < table->philo_nb)
		pthread_join(table->thrds[i], NULL);
	pthread_join(monit, NULL);
}
