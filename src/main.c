/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:03:38 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/18 01:34:40 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	validate_input(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("Wrong num of args!\n");
		return (0);
	}
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (0);
			j++;
		}
		printf("OK: %s\n", av[i]);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	i;

	if (!validate_input(ac, av))
		return (0);
}

//se for mais de 200 philos não roda, 0 não roda
//tempo abaixo de 60 não roda
//overflow de int, tambén não roda e nem negativo
//estudar o codeVault
