/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:51:08 by aaitoual          #+#    #+#             */
/*   Updated: 2022/03/29 08:51:09 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus_lib.h"

void	ft_return(int i)
{
	if (i == 1)
		printf ("syntax error\n");
	if (i == 2)
		printf ("the number of philosophers is less than 1 or not digit\n");
	if (i == 3)
		printf ("the time_to_die is less than 60 or not digit\n");
	if (i == 4)
		printf ("the time_to_eat is less than 60 or not digit\n");
}

static int	ft_second(const char *a, int r, int i)
{
	int	p;

	p = 0;
	while (i - r != 0)
		p = p * 10 + a[r++] - 48;
	return (p);
}

static int	lenq(const char *s, int i)
{
	int	j;

	j = 0;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		i++;
		j++;
	}
	return (j);
}

int	len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	r;

	j = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		j = -1;
		i++;
	}
	if (lenq (str, i) > 10)
		return (-1);
	r = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i != len(str))
		return (0);
	return (ft_second(str, r, i) * j);
}
