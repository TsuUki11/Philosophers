/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:17:29 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/26 12:17:30 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_lib.h"

int	check_time(t_simulation *p, int n, int t)
{
	struct timeval	c;
	long long		time;

	gettimeofday(&c, NULL);
	time = c.tv_sec * 1000 + (c.tv_usec / 1000) - p->curr;
	if (t == 1)
	{
		if (time - p->prio[n] >= p->info.time_to_eat)
			return (1);
		return (0);
	}
	if (t == 2)
	{
		if (time - p->prio[n] - p->info.time_to_eat >= p->info.time_to_sleep)
			return (1);
		return (0);
	}
	if (t == 3)
	{
		if (time - p->prio[n] > p->info.time_to_die)
			return (1);
		return (0);
	}
	return (0);
}

int	get_usleep(t_philo_info info)
{
	if (info.time_to_eat < info.time_to_sleep)
		return (info.time_to_eat - 20);
	return (info.time_to_sleep - 20);
}

int	norm(t_simulation *philos, t_betw bet, int number, t_lanes *t)
{
	call_checker(philos, bet, number);
	pthread_mutex_lock(&philos->mutex);
	if (t->time != philos->prio[number])
	{
		t->time = philos->prio[number];
		t->eat += 1;
	}
	if (!c_s(philos->philo_state, philos->info.philo_number)
		|| (philos->info.must_eat != -1 && t->eat >= philos->info.must_eat))
	{
		if (philos->info.must_eat != -1)
			philos->philo_state[number] = 0;
		pthread_mutex_unlock(&philos->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->mutex);
	usleep (get_usleep(philos->info));
	return (0);
}
