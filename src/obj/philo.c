/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/22 18:05:50 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*populate_philos(char **av, t_infos *infos, t_mutex *mutex)
{
	t_philo		*head;
	t_philo		*aux;
	t_philo		*last;
	long int	philo_nums = atol(av[1]);

	head = NULL;
	while(philo_nums > 0)
	{
		aux = malloc(sizeof(t_philo));
		aux->forks = 1
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
		philo_nums--;
	}
	aux->next = head;
	return (head);
}

void	start_mutex(t_mutex *mutex, t_infos *infos)
{
	mutex->eaten = infos->philo_nums;
	pthread_mutex_init(&mutex->mutex_stop, NULL);
	pthread_mutex_init(&mutex->mutex_print, NULL);
	pthread_mutex_init(&mutex->mutex_eaten, NULL);
}

int	start_threads(t_philo *philo)
{

}

void	start_philo(char **av, t_philo *philo, t_infos *infos)
{
	t_mutex	mutex;
	start_mutex(&mutex, infos);
	philo = populate_philos(av, infos, &mutex);
	start_threads(philo);
}
