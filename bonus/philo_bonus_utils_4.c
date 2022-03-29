/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:51:38 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/29 08:51:40 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus_lib.h"

void	creat_philo_state(t_simulation *philos, t_philo_info info)
{
	philos->info = info;
	philos->num = 0;
	philos->philo_state = 0;
	philos->must = 0;
	philos->last_time = 0;
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

void	check_states_2(t_simulation *philos, int i)
{
	struct timeval	cur;

	if (i == 3)
	{
		if (conditions(philos, 3) && philos->philo_state != 4)
		{
			philos->philo_state = 0;
			gettimeofday(&cur, NULL);
			i = cur.tv_sec * 1000 + (cur.tv_usec / 1000) - philos->curr;
			print(3, i, philos->num);
		}
	}
	if (i == 2)
	{
		if (conditions(philos, 2) && philos->philo_state != 4)
		{
			sem_post(philos->sem);
			philos->philo_state = 2;
			gettimeofday(&cur, NULL);
			i = cur.tv_sec * 1000 + (cur.tv_usec / 1000) - philos->curr;
			print(2, i, philos->num);
		}
	}
}

void	check_states(t_simulation *p, int i)
{
	struct timeval	c;
	long long		time;

	if (i == 1)
	{
		if (p->philo_state == 0)
		{
			sem_wait(p->sem);
			p->philo_state = 1;
			gettimeofday(&c, NULL);
			time = c.tv_sec * 1000 + (c.tv_usec / 1000) - p->curr;
			p->last_time = time;
			print(1, time, p->num);
			p->must += 1;
		}
	}
	check_states_2(p, i);
}
