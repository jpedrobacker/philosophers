/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:03:38 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/22 12:00:04 by jbergfel         ###   ########.fr       */
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

int	check_philos(char *av, t_infos *infos)
{
	int	philo_num;

	philo_num = atol(av);

	if (philo_num < 1 || philo_num > 200)
		return (printf("Invalid Num of Philos!\n"), 0);
	else
		infos->philo_nums = philo_num;
	return (1);

}

int	check_time_die(char *av, t_infos *infos)
{
	int	time_to_die;

	time_to_die = atol(av);
	if (time_to_die < 60 || time_to_die > MAX_INT)
		return (printf("Invalid time to die!\n"), 0);
	else
		infos->philo_die = time_to_die;
	return (1);
}

int	check_time_eat(char *av, t_infos *infos)
{
	int	time_to_eat;

	time_to_eat = atol(av);
	if (time_to_eat < 1 || time_to_eat > MAX_INT)
		return (printf("Invalid time to eat!\n"), 0);
	else
		infos->philo_eat = time_to_eat;
	return (1);
}

int	check_time_sleep(char *av, t_infos *infos)
{
	int	time_to_sleep;

	time_to_sleep = atol(av);
	if (time_to_sleep < 1 || time_to_sleep > MAX_INT)
		return (printf("Invalid time to sleep!\n"), 0);
	else
		infos->philo_sleep = time_to_sleep;
	return (1);
}

int	check_must_eat(char *av, t_infos *infos)
{
	int	must_eat;

	must_eat = atol(av);
	if (must_eat < 1 || must_eat > MAX_INT)
		return (printf("Invalid must eat!\n"), 0);
	else
		infos->philo_die = must_eat;
	return (1);
}

int	check_infos(char **av, t_infos *infos)
{
	if (!check_philos(av[1], infos))
		return (0);
	if (!check_time_die(av[2], infos))
		return (0);
	if (!check_time_eat(av[3], infos))
		return (0);
	if (!check_time_sleep(av[4], infos))
		return (0);
	if (av[5])
	{
		if (!check_must_eat(av[5], infos))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	t_infos	infos;

	if (!validate_input(ac, av))
		return (0);
	if (!check_infos(av, &infos))
		return (0);
	start_philo(av, &philo, &infos);
}

//se for mais de 200 philos não roda, 0 não roda
//tempo abaixo de 60 não roda
//overflow de int, tambén não roda e nem negativo
//estudar o codeVault
