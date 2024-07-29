/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:01 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/29 12:25:05 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	start_threads(t_philo *philo)
{
	int	i;

	i = -1;
	philo->start_time = start_time();
	while (++i < philo->infos->philo_nums)
	{
		if (phtread_create(&philo->philo_thrds, NULL, &routine, philo))
			return (1);
		philo = philo->next;
	}
	if (pthread_create(/*monitor thread*/, NULL, /*check_all_live_routine*/, philo))
		return (1);
	return (0);
}

void	start_philo(char **av, t_philo *philo, t_infos *infos)
{
	t_mutex	mutex;
	start_mutex(&mutex, infos);
	philo = populate_philos(av, infos, &mutex);
	//forks func
	start_threads(philo);
	make_thread(philo);
	free_data(philo);
}
