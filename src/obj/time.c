/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:01:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/02 23:02:13 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	one_philo_usleep(int time)
{
	usleep(time * 1000);
}

int	philo_usleep(t_philo *philo, int time)
{
	long	final;

	final = get_cur_time() + time;
	while (final > get_cur_time())
	{
		if (is_dead(philo))
			return (0);
		if (philo->death <= get_cur_time())
		{
			philo->is_dead = 1;
			return (0);
		}
		usleep(500);
	}
	return (1);
}
