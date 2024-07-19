/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:08 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/19 12:56:51 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*populate_philos(char **av, t_infos *infos)
{
	t_philo		*head;
	t_philo		*aux;
	t_philo		*last;
	long int	philo_nums = atol(av[1]);

	head = NULL;
	while(philo_nums > 0)
	{
		aux = malloc(sizeof(t_philo));
		aux->infos = infos;
		aux->philo_num = philo_nums;
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

void	start_philo(char **av, t_philo *philo, t_infos *infos)
{
//	t_philo	*aux_philo = philo;
	philo = populate_philos(av, infos);
	(void) philo;
}
