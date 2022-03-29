/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 10:48:09 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/26 10:48:10 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_lib.h"

void	print(int i, long long time, int number, t_simulation *philos)
{
	if (i == 1)
	{
		printf ("%lld %d has taken a fork\n", philos->prio[number], number + 1);
		printf ("%lld %d has taken a fork\n", philos->prio[number], number + 1);
		printf ("%lld %d is eating\n", philos->prio[number], number + 1);
	}
	if (i == 2)
		printf ("%lld %d is sleeping\n", time, number + 1);
	if (i == 3)
		printf ("%lld %d is thiking\n", time, number + 1);
	if (i == 4)
		printf ("%lld %d is dead\n", time, number + 1);
}

void	check_states_2(t_simulation *philos, t_betw bet, int number, int i)
{
	struct timeval	cur;

	if (i == 3)
	{
		if (conditions(number, philos, bet, 3)
			&& c_s(philos->philo_state, philos->info.philo_number))
		{
			gettimeofday(&cur, NULL);
			i = cur.tv_sec * 1000 + (cur.tv_usec / 1000) - philos->curr;
			philos->philo_state[number] = 0;
			print(3, i, number, philos);
		}
	}
	if (i == 4)
	{
		if (conditions(number, philos, bet, 4)
			&& c_s(philos->philo_state, philos->info.philo_number))
		{
			gettimeofday(&cur, NULL);
			i = cur.tv_sec * 1000 + (cur.tv_usec / 1000) - philos->curr;
			philos->philo_state[number] = 4;
			print(4, i, number, philos);
		}
	}
}

void	check_states(t_simulation *p, t_betw bet, int number, int i)
{
	struct timeval	c;

	if (i == 1)
	{
		if (conditions(number, p, bet, 1)
			&& c_s(p->philo_state, p->info.philo_number))
		{
			gettimeofday(&c, NULL);
			p->prio[number] = c.tv_sec * 1000 + (c.tv_usec / 1000) - p->curr;
			p->philo_state[number] = 1;
			print(1, i, number, p);
		}
	}
	if (i == 2)
	{
		if (conditions(number, p, bet, 2)
			&& c_s(p->philo_state, p->info.philo_number))
		{
			gettimeofday(&c, NULL);
			i = c.tv_sec * 1000 + (c.tv_usec / 1000) - p->curr;
			p->philo_state[number] = 2;
			print(2, i, number, p);
		}
	}
	check_states_2(p, bet, number, i);
}

void	call_checker(t_simulation *philos, t_betw bet, int number)
{
	pthread_mutex_lock(&philos->mutex);
	check_states(philos, bet, number, 1);
	pthread_mutex_unlock(&philos->mutex);
	pthread_mutex_lock(&philos->mutex);
	check_states(philos, bet, number, 2);
	pthread_mutex_unlock(&philos->mutex);
	pthread_mutex_lock(&philos->mutex);
	check_states(philos, bet, number, 3);
	pthread_mutex_unlock(&philos->mutex);
	pthread_mutex_lock(&philos->mutex);
	check_states(philos, bet, number, 4);
	pthread_mutex_unlock(&philos->mutex);
}

int	conditions(int number, t_simulation *philos, t_betw bet, int con)
{
	if (con == 1)
	{
		if (philos->philo_state[number] == 0
			&& philos->philo_state[bet.after] != 1
			&& philos->philo_state[bet.before] != 1
			&& check_prio(philos, number))
			return (1);
	}
	if (con == 2)
	{
		if (philos->philo_state[number] == 1 && check_time(philos, number, 1))
			return (1);
	}
	if (con == 3)
	{
		if (philos->philo_state[number] == 2 && check_time(philos, number, 2))
			return (1);
	}
	if (con == 4)
	{
		if (philos->philo_state[number] != 1 && check_time(philos, number, 3))
			return (1);
	}
	return (0);
}
