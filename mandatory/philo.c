/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:49:05 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/21 17:49:07 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_lib.h"

t_betw	get_bet(int number, t_simulation *philos)
{
	t_betw	bet;

	if (number == 0)
		bet.before = philos->info.philo_number - 1;
	else
		bet.before = number - 1;
	if (number == philos->info.philo_number - 1)
		bet.after = 0;
	else
		bet.after = number + 1;
	if (philos->info.philo_number == 1)
	{
		bet.before = -1;
		bet.after = -1;
	}
	return (bet);
}

int	c_s(int *state, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (state[i] == 4)
			return (0);
		i++;
	}
	return (1);
}

void	*philo_1(t_simulation *philos, t_betw bet, int number)
{
	long long		time;
	struct timeval	c;

	while (bet.before == -1)
	{
		pthread_mutex_lock(&philos->mutex);
		if (!c_s(philos->philo_state, philos->info.philo_number))
			break ;
		if (conditions(number, philos, bet, 4)
			&& c_s(philos->philo_state, philos->info.philo_number))
		{
			gettimeofday(&c, NULL);
			time = c.tv_sec * 1000 + (c.tv_usec / 1000) - philos->curr;
			philos->philo_state[number] = 4;
			print(4, time, number, philos);
		}
		pthread_mutex_unlock(&philos->mutex);
	}
	pthread_mutex_unlock(&philos->mutex);
	return (0);
}

void	*philo(void *p)
{
	t_simulation	*philos;
	t_betw			bet;
	int				number;

	philos = p;
	number = philos->num;
	philos->num = number + 1;
	bet = get_bet(number, philos);
	while (bet.before > -1)
	{
		if (norm(philos, bet, number))
			break ;
	}
	philo_1(philos, bet, number);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo_info		info;
	t_simulation		philos;
	int					i;
	int					k;
	struct timeval		c;

	gettimeofday(&c, NULL);
	pthread_mutex_init(&philos.mutex, NULL);
	if (ac < 5 || ac > 6)
	{
		ft_return (1);
		return (1);
	}
	ft_get_info(ac, av, &info);
	if (arg_checker(info, ac))
		return (1);
	creat_philo_state(&philos, info);
	philos.curr = c.tv_sec * 1000 + (c.tv_usec / 1000);
	creat_threads(info, &philos);
	free(philos.prio);
	free(philos.philo_state);
	pthread_mutex_destroy(&philos.mutex);
	return (0);
}
