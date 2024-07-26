/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/26 16:20:03 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		aux->r_fork = 0;
		aux->l_fork = 0;
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

void	start_mutex(t_mutex *mutex, t_infos *infos)
{
	mutex->eaten = infos->philo_nums;
	pthread_mutex_init(&mutex->mutex_stop, NULL);
	pthread_mutex_init(&mutex->mutex_print, NULL);
	pthread_mutex_init(&mutex->mutex_eaten, NULL);
}

void	*print_hello(void *aux)
{
	int	i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *) aux;
	while (philos)
	{
		printf("%d says Hello!\n", philos->philo_num);
		philos = philos->next;
		i++;
		usleep(philos->infos->philo_die);
		if (i == philos->philo_num)
			return (NULL);
	}
	return (NULL);
}

int	start_threads(t_philo *philo)
{
	t_philo	*aux;

	aux = philo;
	while (aux)
	{
		if (pthread_create(&aux->thread, NULL, print_hello, aux))
			exit(1);
		printf("TESTE\n");
		if (pthread_join(aux->thread, NULL))
			exit(1);
		printf("TESTE2\n");
		aux = aux->next;
	}
	return (0);
}

void	start_philo(char **av, t_philo *philo, t_infos *infos)
{
	t_mutex	mutex;
	start_mutex(&mutex, infos);
	philo = populate_philos(av, infos, &mutex);
	(void) philo;
	start_threads(philo);
}
