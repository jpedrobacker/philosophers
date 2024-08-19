/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/19 12:20:19 by jbergfel         ###   ########.fr       */
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

void	to_sleep(t_philo *philo)
{
	print_sleep(philo);
	philo_usleep(philo->table->philo_sleep);
	philo->eat_count++;
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_forks(philo);
	pthread_mutex_lock(philo->rfork);
	print_forks(philo);
}

void	return_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->lfork);
	to_sleep(philo);
}

/*void	*check_deaths(void *p_table)
{
	t_table	*table;

	table = (t_table *)p_table;
	while (1)
	{
		if (check_eat(table))
			break;
		if (start_time() - table->philo->last_meal > table->philo_die && table->philo->last_meal != -1 && (table->philo->eat_count < table->philo_nb_meals || table->philo_nb_meals == -1))
		{
			print_death(&table->philo);
			table->has_dead = true;
			exit(EXIT_FAILURE);
		}
		table->philo = table->philo->next;
	}

}*/

void	*routine(void *p_philo)
{
	t_philo *philo;

	philo = (t_philo *) p_philo;
	philo->last_meal = start_time();
//	pthread_create(&philo->monit, NULL, &check_deaths, philo->table);
//	pthread_detach(philo->monit);
	if (philo->id % 2 == 0)
		philo_usleep(1);
	while (!philo->table->has_dead /*&& !check_eat(philo->table)*/)
	{
		print_think(philo);
		printf("teste1\n");
		//take_fork(philo);
		print_eating(philo);
		philo->last_meal = start_time();
		philo_usleep(philo->table->philo_eat - 5);
		//return_fork(philo);
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
