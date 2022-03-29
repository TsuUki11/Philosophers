/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus_lib.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:06:22 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/28 01:06:25 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_LIB_H
# define PHILOSOPHERS_BONUS_LIB_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct philo_info_s
{
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_philo_info;

typedef struct simulation_s
{
	int				philo_state;
	sem_t			*sem;
	sem_t			*chk;
	t_philo_info	info;
	int				num;
	long 	long	curr;
	long	long	last_time;
}	t_simulation;

typedef struct bet_s
{
	int	before;
	int	after;
}	t_betw;

void	ft_return(int i);
void	creat_philo_state(t_simulation *philos, t_philo_info info);
void	*philo(void *p);
void	check_states(t_simulation *p, int i);
void	print(int i, long long time, int number);
void	ft_get_info(int ac, char **av, t_philo_info *info);
int		ft_atoi(const char *str);
int		arg_checker(t_philo_info info, int ac);
int		conditions(t_simulation *philos, int con);
int		check_time(t_simulation *philos, int t);
void	simulation(t_simulation *philos);

#endif