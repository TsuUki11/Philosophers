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

void	kill_childrennnnnnnnn(int *id, t_simulation *philos)
{
	int	i;

	i = 0;
	while (i < philos->info.philo_number)
	{
		kill(id[i], SIGKILL);
		i++;
	}
}

int	creat_childs(t_simulation *philos)
{
	int		f;
	int		i;
	int		*id;

	i = 0;
	f = 1;
	id = malloc (sizeof(int) * philos->info.philo_number);
	while (i < philos->info.philo_number)
	{
		if (f != 0)
		{
			f = fork();
			id[i] = f;
			i++;
		}
		else
			break ;
	}
	if (f == 0)
	{
		philos->num = i;
		free(id);
		simulation(philos);
	}
	if (f != 0)
	{
		waitpid(-1, NULL, 0);
		kill_childrennnnnnnnn(id, philos);
		free(id);
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
	sem_unlink("sem");
	sem_unlink("chk");
	philos.chk = sem_open("chk", O_CREAT, 0660, 1);
	philos.sem = sem_open("sem", O_CREAT, 0660, philos.info.philo_number / 2);
	ft_get_info(ac, av, &info);
	if (arg_checker(info, ac))
		return (1);
	creat_philo_state(&philos, info);
	creat_childs(&philos);
	sem_close(philos.sem);
	sem_close(philos.chk);
	return (0);
}
