/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/12 13:24:37 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*check_death(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (1)
	{
		if (philo->is_dead == 1)
		{
			pthread_mutex_lock(&philo->table->m_stop);
			philo->table->stop_dinner = 1;
			pthread_mutex_unlock(&philo->table->m_stop);
			print_death(philo);
			break ;
		}
		pthread_mutex_lock(&philo->table->m_eat);
		if (!philo->table->eaten)
		{
			pthread_mutex_unlock(&philo->table->m_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->table->m_eat);
		philo = philo->next;
		usleep(500);
	}
	return (NULL);
}

int	have_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->m_eat);
	if (philo->eat_count == philo->table->to_eat)
	{
		philo->table->eaten--;
		if (!philo->table->eaten)
		{
			pthread_mutex_unlock(&philo->table->m_eat);
			pthread_mutex_lock(&philo->table->m_stop);
			philo->stop_eat = 1;
			pthread_mutex_unlock(&philo->table->m_stop);
		}
		else
			pthread_mutex_unlock(&philo->table->m_eat);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->m_eat);
	return (1);
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
		to_sleep(philo);
		if (!have_eaten(philo))
			break ;
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
	pthread_t	*thrds;
	t_philo		*philo;

	philo = table->philo;
	table->start_time = get_cur_time();
	if (table->philo_nb == 1)
		return (one_philo_routine(table));
	thrds = malloc(sizeof(pthread_t) * table->philo_nb);
	pthread_create(&monit, NULL, &check_death, (void *)philo);
	i = -1;
	while (++i < table->philo_nb)
	{
		pthread_create(&thrds[i], NULL, &routine, (void *)philo);
		philo = philo->next;
	}
	i = -1;
	while (++i < table->philo_nb)
		pthread_join(thrds[i], NULL);
	pthread_join(monit, NULL);
	free(thrds);
}
