#include "philosophers_bonus_lib.h"

void	print(int i, long long time, int number)
{
	if (i == 1)
		printf ("%lld %d has taken a fork\n", time, number + 1);
	if (i == 0)
    {
		printf ("%lld %d has taken a fork\n", time, number + 1);
		printf ("%lld %d is eating\n", time, number + 1);
    }
    if (i == 2)
		printf ("%lld %d is sleeping\n", time, number + 1);
	if (i == 3)
		printf ("%lld %d is thiking\n", time, number + 1);
	if (i == 4)
		printf ("%lld %d is dead\n", time, number + 1);
}

int	check_time(t_simulation *p, int t)
{
	struct timeval	c;
	long long		time;

	gettimeofday(&c, NULL);
	time = c.tv_sec * 1000 + (c.tv_usec / 1000) - p->curr;
	if (t == 1)
	{
		if (time - p->last_time >= p->info.time_to_eat)
			return (1);
		return (0);
	}
	if (t == 2)
	{
		if (time - p->last_time - p->info.time_to_eat >= p->info.time_to_sleep)
			return (1);
		return (0);
	}
	if (t == 3)
	{
		if (time - p->last_time > p->info.time_to_die)
			return (1);
		return (0);
	}
	return (0);
}

int	conditions(t_simulation *philos, int con)
{
	if (con == 2)
	{
		if (philos->philo_state == 1 && check_time(philos, 1))
			return (1);
	}
	if (con == 3)
	{
		if (philos->philo_state == 2 && check_time(philos, 2))
			return (1);
	}
	return (0);
}