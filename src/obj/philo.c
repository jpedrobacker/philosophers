/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/02 23:24:25 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->death <= get_cur_time())
	{
		philo->is_dead = 1;
		return (1);
	}
	return (0);
}

void	*check_death(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
		if (get_cur_time() >= philo->death && !philo->is_dead)
		{
			philo->is_dead = 1;
			philo->table->stop_dinner = 1;
			print_death(philo);
			pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
			break ;
		}
		pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
		usleep(500);
	}
	return (NULL);
}

int	eat_pls(t_philo *philo)
{
	take_fork(philo);
	print_eating(philo);
	philo->death = get_cur_time() + philo->table->philo_die;
	philo->eat_count++;
	if (!philo_usleep(philo, philo->table->philo_eat))
	{
		return_fork(philo);
		return (0);
	}
	return_fork(philo);
	return (1);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *) p_philo;
	philo->start = get_cur_time();
	philo->death = philo->start + philo->table->philo_die;
	if (philo->id % 2 == 0)
		one_philo_usleep(1);
	while (1)
	{
		print_think(philo);
		if (!eat_pls(philo))
			break ;
		to_sleep(philo);
		if (philo->stop_eat || philo->table->stop_dinner)
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
	t_philo		*philo;

	table->start_time = get_cur_time();
	philo = table->philo;
	if (table->philo_nb == 1)
		return (one_philo_routine(table));
	i = -1;
	while (++i < table->philo_nb)
	{
		pthread_create(&table->thrds[i], NULL, &routine, (void *)philo);
		pthread_create(&monit, NULL, &check_death, (void *)philo);
		pthread_detach(monit);
		philo = philo->next;
	}
	i = -1;
	while (++i < table->philo_nb)
		pthread_join(table->thrds[i], NULL);
}
