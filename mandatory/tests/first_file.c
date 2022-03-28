#include "philosophers_lib.h"

int	i = 0;
int	test[10] = {1, 2, 3, 5, 6, 9, 10, 12, 19, 21};
pthread_mutex_t	x;

void    *test_function(void	*in)
{
	int	index = *(int *)in;
	int	r;

	r = 0;
	sleep (1);
	while (r < 5)
	{
		printf ("%d\n", test[index + r]);
		r++;
	}
	free (in);
	return (0);
}

int	main()
{
	pthread_t	t[2];
	int	*k;
	int	j;

	j = 0;
	while (j < 2)
	{
		k = malloc (sizeof (int));
		*k = j * 5;
		pthread_create(&t[j], NULL, &test_function, k);
		j++;
	}
	j = 0;
	while (j < 2)
	{
		pthread_join(t[j], NULL);
		j++;
	}
	pthread_mutex_destroy(&x);
	return (0);
}