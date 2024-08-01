/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:04:21 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/01 13:08:10 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_elems(t_philo *philos)
{
	while (philos)
	{
		printf("ola: %d\n", philos->infos->philo_nums);
		philos = philos->next;
	}
}
