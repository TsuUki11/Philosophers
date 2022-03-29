/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:51:20 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/29 08:51:25 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus_lib.h"

int	get_usleep(t_philo_info info)
{
	if (info.time_to_eat < info.time_to_sleep)
		return (info.time_to_eat - 20);
	return (info.time_to_sleep - 20);
}

void	norm(t_simulation *philos)
{
	static long long		time;
	static int				eat;

	check_states(philos, 1);
	check_states(philos, 2);
	check_states(philos, 3);
	usleep (get_usleep(philos->info));
}

void	*philo(void *p)
{
	t_simulation	*philos;
	long long		time;
	struct timeval	c;

	gettimeofday(&c, NULL);
	time = c.tv_sec * 1000 + (c.tv_usec / 1000);
	philos = p;
	philos->curr = time;
	while (1)
		norm(philos);
	return (0);
}

int	check_deads(t_simulation *philos)
{
	struct timeval	c;
	long long		time;

	gettimeofday(&c, NULL);
	time = c.tv_sec * 1000 + (c.tv_usec / 1000);
	if (philos->info.time_to_die <= time - philos->curr - philos->last_time)
	{
		printf ("%lld %d is dead\n", time - philos->curr, philos->num + 1);
		return (1);
	}
	return (0);
}

void	simulation(t_simulation *philos)
{
	pthread_t		t;

	pthread_create(&t, NULL, &philo, philos);
	pthread_detach(t);
	while (1)
	{
		sem_wait(philos->chk);
		if (check_deads(philos))
			exit (0);
		sem_post(philos->chk);
	}
}
