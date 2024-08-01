/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:01:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/01 14:20:20 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

u_int64_t	start_time(void)
{
	struct timeval	cur_time;

	if (gettimeofday(&cur_time, NULL))
		return (0);
	return ((cur_time.tv_sec * (u_int64_t) 100) + (cur_time.tv_usec / 1000));
}

void	philo_usleep(u_int64_t time_to_sleep)
{
	u_int64_t	start;

	start = start_time();
	while ((start_time() - start) < time_to_sleep)
		usleep(500);
}
