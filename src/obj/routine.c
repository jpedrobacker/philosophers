/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:01 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/02 21:41:42 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	make_thread(t_philo *philo)
{

}

void	update_meal_time(t_philo *philo)
{
	//Mutex lock
	//Update current philo time
	//Mutex unlock
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	update_meal_time(philo);
	if (philo->philo_num % 2 == 0)
		philo_usleep(philo->infos->philo_nb_meals - 10);
	while (/*while philo isn't dead func*/1)
	{
		if (/*eat func*/0)
			break ;
		if (/*check_philo_state*/0)
			break ;
		if (/*sleep_func*/0)
			break ;
		if (/*check_philo_state*/0)
			break ;
		if (/*think func*/0)
			break ;
	}
	return (NULL);
}

bool	nb_meals_option(t_philo *philo)
{
	if (philo->infos->philo_eat > 0)
		return (1);
	return (0);
}

int	start_threads(t_philo *philo)
{
	int	i;

	i = -1;
	philo->start_time = start_time();
	while (++i < philo->infos->philo_nums)
	{
		if (pthread_create(philo->philo_thrds, NULL, &routine, philo))
			return (1);
		philo = philo->next;
	}
	if (pthread_create(&philo->monit_check_alive, NULL, /*check_all_live_routine*/NULL, philo))
		return (1);
	if (nb_meals_option(philo) == true && pthread_create(&philo->monit_check_eat, NULL, NULL/*&all_full_routine*/, philo))
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
	to_free(philo);
}
