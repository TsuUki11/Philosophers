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

void	creat_philo_state(t_simulation *philos, t_philo_info info)
{
	philos->info = info;
	philos->num = 0;
	philos->philo_state = 0;
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

int	check_states_2(t_simulation *philos, int i)
{
	struct timeval	cur;

	if (i == 3)
	{
		if (conditions(philos, 3) && philos->philo_state != 4)
		{
			gettimeofday(&cur, NULL);
			i = cur.tv_sec * 1000 + (cur.tv_usec / 1000) - philos->curr;
			philos->philo_state = 0;
			print(3, i, philos->num);
			return (1);
		}
	}
	return (0);
}

int	check_states(t_simulation *p, int i)
{
	struct timeval	c;
	long	long	time;

	if (i == 1)
	{
		if (p->philo_state == 0)
		{
			// puts("yoo\n");
			sem_wait(p->sem);
			// puts("too\n");
			gettimeofday(&c, NULL);
			time = c.tv_sec * 1000 + (c.tv_usec / 1000) - p->curr;
			print(1, time, p->num);
			gettimeofday(&c, NULL);
			p->philo_state = 1;
			p->last_time = c.tv_sec * 1000 + (c.tv_usec / 1000) - p->curr;
			print(0, p->last_time, p->num);
		}
	}
	if (i == 2)
	{
		if (conditions(p, 2) && p->philo_state != 4)
		{
			gettimeofday(&c, NULL);
			i = c.tv_sec * 1000 + (c.tv_usec / 1000) - p->curr;
			sem_post(p->sem);
			p->philo_state = 2;
			print(2, i, p->num);
		}
	}
	return (check_states_2(p, i));
}

int	call_checker(t_simulation *philos)
{
	check_states(philos, 1);
	check_states(philos, 2);
	if (check_states(philos, 3))
		return (1);
	return (0);
}

int	get_usleep(t_philo_info info)
{
	if (info.time_to_eat < info.time_to_sleep)
		return (info.time_to_eat - 20);
	return (info.time_to_sleep - 20);
}

int	norm(t_simulation *philos)
{
	static long long		time;
	static int				eat;

	if (call_checker(philos))
		return (0);
	// if (time != philos->prio[number])
	// {
	// 	time = philos->prio[number];
	// 	eat++;
	// }
	// if (!c_s(philos->philo_state, philos->info.philo_number)
	// 	|| eat == philos->info.must_eat)
	// {
	// 	philos->philo_state[number] = 0;
	// 	return (1);
	// }
	usleep (get_usleep(philos->info));
	return (0);
}

void	*philo(void *p)
{
	t_simulation	*philos;
	long	long	time;
	struct timeval	c;

	gettimeofday(&c, NULL);
	time = c.tv_sec * 1000 + (c.tv_usec / 1000);
	philos = p;
	philos->curr = time;
	while (philos->info.philo_number != 1)
	{
		if (norm(philos))
			break ;
	}
	while (philos->info.philo_number == 1);
	return (0);
}

int	check_deads(t_simulation *philos)
{
	struct timeval	c;
	long	long	time;

	gettimeofday(&c, NULL);
	time = c.tv_sec * 1000 + (c.tv_usec / 1000);
	if (philos->info.time_to_die <= time - philos->curr - philos->last_time)
	{
		printf ("%lld %d is dead\n", time - philos->curr, philos->num);
		return (1);
	}
	return (0);
}

int	simulation(t_simulation *philos)
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
	return (0);
}

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
	int		j;
	int		*id;
	sem_t	*sem;
	struct timeval	current_time;
	long long	time;
	
	i = 0;
	f = 1;
	j = 10;
	sem_unlink("sem");
	sem = sem_open("sem", O_CREAT, 0660, philos->info.philo_number / 2);
	id = malloc (sizeof(int) * philos->info.philo_number);
	while (i < philos->info.philo_number)
	{
		if (f != 0)
			f = fork();
		if (f != 0)
		{
			id[i] = f;
			i++;
		}
		else
			break ;
	}
	if (f == 0)
	{
		philos->sem = sem;
		philos->num = i;
		simulation(philos);
	}
	if (f != 0)
	{
		waitpid(-1, NULL, 0);
		kill_childrennnnnnnnn(id, philos);
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
	creat_childs(&philos);
	return (0);
}
