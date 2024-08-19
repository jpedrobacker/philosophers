/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:38:41 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/19 12:00:04 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*populate_philos(char **av, t_table *table)
{
	t_philo		*head;
	t_philo		*aux;
	t_philo		*last;
	int			i;

	head = NULL;
	i = 0;
	while(atol(av[1]) >= i)
	{
		aux = malloc(sizeof(t_philo));
		aux->id = i + 1;
		aux->table = table;
		aux->eat_count = 0;
		aux->last_meal = -1;
		aux->next = NULL;
		if (head == NULL)
			head = aux;
		else
			last->next = aux;
		last = aux;
		i++;
	}
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

void	check_infos(char **av, t_table *table)
{
	if (ft_atol(av[1]) < 200 && ft_atol(av[1]) > 0)
		table->philo_nb = ft_atol(av[1]);
	else
		printf("Wrong number of philos!\n");
	table->philo_die = ft_atol(av[2]);
	table->philo_eat = ft_atol(av[3]);
	table->philo_sleep = ft_atol((av[4]));
	table->has_dead = false;
	if (av[5])
		table->philo_nb_meals = ft_atol((av[5]));
	else
		table->philo_nb_meals = -1;
	table->thrds = malloc(sizeof(pthread_t) * table->philo_nb);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nb);
	table->philo = populate_philos(av, table);
}
