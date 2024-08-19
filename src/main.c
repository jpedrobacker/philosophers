/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:03:38 by jbergfel          #+#    #+#             */
/*   Updated: 2024/08/19 11:43:16 by jbergfel         ###   ########.fr       */
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
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!validate_input(ac, av))
		return (0);
	check_infos(av, &table);
	start_forks(&table);
	start_philo(&table);
	//to_free(&table);
}

//se for mais de 200 philos não roda, philos > 0 não roda
//tempo abaixo de 60 não roda
//overflow de int, tambén não roda e nem negativo
//estudar o codeVault
