/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:05:39 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/28 01:05:40 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus_lib.h"

	sem_t	*sem;

void	creat_philo_state(t_simulation *philos, t_philo_info info)
{
	int	i;

	i = 0;
	philos->info = info;
	philos->num = 0;
	philos->prio = malloc (sizeof(long long) * info.philo_number);
	while (i < info.philo_number)
	{
		philos->philo_state = 0;
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

int	simulation(t_simulation *philos, int i, sem_t *sem)
{
	
	return (0);
}

int	creat_childs(t_simulation *philos)
{
	int		f;
	int		i;
	int		j;

	i = 0;
	f = 1;
	j = 10;
	// sem_unlink("sem");
	sem_unlink("sem");
	// sem = sem_open("sem", O_CREAT, 0660, philos->info.philo_number);
	sem = sem_open("sem", O_CREAT, 0660, 0);
	while (i < philos->info.philo_number)
	{
		if (f != 0)
			f = fork();
		if (f != 0)
			i++;
		else
			break ;
		// usleep (10);
	}
	if (f == 0)
		return (simulation(philos, i, sem));
	if (f != 0)
	{
		usleep(10000);
		sem_post(sem);
		waitpid(-1, NULL, 0);
		sem_close(sem);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo_info		info;
	t_simulation		philos;
	int					i;
	int					k;
	int					f;

	if (ac < 5 || ac > 6)
	{
		ft_return (1);
		return (1);
	}
	ft_get_info(ac, av, &info);
	if (arg_checker(info, ac))
		return (1);
	creat_philo_state(&philos, info);
	return(creat_childs(&philos));
	return (0);
}
