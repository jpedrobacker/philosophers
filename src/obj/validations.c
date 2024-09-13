/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:38:41 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/12 22:41:16 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	add_infos(t_philo *aux, t_table *table, int i)
{
	aux->table = table;
	aux->eat_count = 0;
	aux->start = 0;
	aux->death = 0;
	aux->is_dead = 0;
	aux->stop_eat = 0;
	aux->lfork = &table->forks[i];
	aux->rfork = &table->forks[(i + 1) % table->philo_nb];
}

t_philo	*populate_philos(char **av, t_table *table)
{
	t_philo		*head;
	t_philo		*aux;
	t_philo		*last;
	int			i;
	int			nb_ph;

	head = NULL;
	last = NULL;
	i = -1;
	nb_ph = ft_atol(av[1]);
	while (nb_ph > ++i)
	{
		aux = malloc(sizeof(t_philo));
		aux->id = i + 1;
		add_infos(aux, table, i);
		aux->next = NULL;
		if (!head)
			head = aux;
		else
			last->next = aux;
		last = aux;
	}
	last->next = head;
	return (head);
}

void	start_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

int	check_infos(char **av, t_table *table)
{
	int	i;

	i = ft_atol(av[1]);
	if (i < 200 && i > 0)
		table->philo_nb = i;
	else
	{
		printf("Wrong number of philos!\n");
		return (0);
	}
	table->philo_die = ft_atol(av[2]);
	table->philo_eat = ft_atol(av[3]);
	table->philo_sleep = ft_atol((av[4]));
	table->stop_dinner = 0;
	if (av[5])
		table->to_eat = ft_atol((av[5]));
	else
		table->to_eat = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nb);
	table->philo = populate_philos(av, table);
	table->eaten = table->philo_nb;
	pthread_mutex_init(&table->m_print, NULL);
	pthread_mutex_init(&table->m_stop, NULL);
	pthread_mutex_init(&table->m_eat, NULL);
	return (1);
}
