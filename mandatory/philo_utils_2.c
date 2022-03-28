/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:01:55 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/26 11:01:56 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_lib.h"

int	arg_checker(t_philo_info info, int ac)
{
	if (info.philo_number < 1)
	{
		ft_return(2);
		return (1);
	}
	if (info.time_to_die < 60)
	{
		ft_return(3);
		return (1);
	}
	if (info.time_to_eat < 60)
	{
		ft_return(4);
		return (1);
	}
	return (0);
}

int	check_prio(t_simulation *philos, int num)
{
	int	i;

	i = 0;
	while (i < philos->info.philo_number)
	{
		if (philos->prio[num] > philos->prio[i])
			return (0);
		i++;
	}
	return (1);
}

void	creat_threads(t_philo_info info, t_simulation *philos)
{
	pthread_t		*t;
	int				i;
	pthread_mutex_t	x;

	i = 0;
	t = malloc (sizeof (pthread_t) * info.philo_number);
	philos->num = 0;
	while (i < info.philo_number)
	{
		pthread_create(&t[i], NULL, &philo, philos);
		i++;
	}
	i = 0;
	while (i < info.philo_number)
	{
		pthread_join(t[i], NULL);
		i++;
	}
}

void	creat_philo_state(t_simulation *philos, t_philo_info info)
{
	int	i;

	i = 0;
	philos->info = info;
	philos->num = 0;
	philos->philo_state = malloc (sizeof(int) * info.philo_number);
	philos->prio = malloc (sizeof(long long) * info.philo_number);
	while (i < info.philo_number)
	{
		philos->philo_state[i] = 0;
		philos->prio[i] = 0;
		i++;
	}
}

void	ft_get_info(int ac, char **av, t_philo_info *info)
{
	info->philo_number = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->must_eat = ft_atoi(av[5]);
	else
		info->must_eat = -1;
}
