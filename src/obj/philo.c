/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/02 21:30:26 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	start_mutex(t_mutex *mutex, t_infos *infos)
{
	mutex->eaten = infos->philo_nums;
	pthread_mutex_init(&mutex->mutex_stop, NULL);
	pthread_mutex_init(&mutex->mutex_print, NULL);
	pthread_mutex_init(&mutex->mutex_eaten, NULL);
}

t_philo	*populate_philos(char **av, t_infos *infos, t_mutex *mutex)
{
	t_philo		*head;
	t_philo		*aux;
	t_philo		*last;
	int			i;

	head = NULL;
	i = 0;
	while(atol(av[1]) >= ++i)
	{
		aux = malloc(sizeof(t_philo));
		aux->philo_num = i;
		aux->has_eaten = 0;
		aux->has_died = 0;
		aux->infos = infos;
		aux->mutex = mutex;
		aux->next = NULL;
		if (head == NULL)
			head = aux;
		else
			last->next = aux;
		last = aux;
	}
	aux->next = head;
	return (head);
}
