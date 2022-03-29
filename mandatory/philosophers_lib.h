/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_lib.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:19:09 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/26 12:19:10 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_LIB_H
# define PHILOSOPHERS_LIB_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct philo_info_s
{
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_philo_info;

typedef struct lanes
{
	long long	time;
	int			eat;
}	t_lanes;

typedef struct simulation_s
{
	int				*philo_state;
	pthread_mutex_t	mutex;
	t_philo_info	info;
	int				num;
	long long		curr;
	long long		*prio;
}	t_simulation;

typedef struct bet_s
{
	int	before;
	int	after;
}	t_betw;

void	ft_return(int i);
void	creat_threads(t_philo_info info, t_simulation *philos);
void	creat_philo_state(t_simulation *philos, t_philo_info info);
void	*philo(void *p);
void	check_states(t_simulation *philos, t_betw bet, int number, int i);
void	call_checker(t_simulation *philos, t_betw bet, int number);
void	print(int i, long long time, int number, t_simulation *philos);
void	ft_get_info(int ac, char **av, t_philo_info *info);
int		ft_atoi(const char *str);
int		arg_checker(t_philo_info info, int ac);
int		check_prio(t_simulation *philos, int num);
int		conditions(int number, t_simulation *philos, t_betw bet, int con);
int		c_s(int *state, int number);
int		check_time(t_simulation *philos, int number, int t);
int		norm(t_simulation *philos, t_betw bet, int number, t_lanes *t);

#endif
