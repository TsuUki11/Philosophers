#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	long long		i;
	long long		j;
	long long		k;
	long long		t;

	j = 1;
	k = 0;
	t = 1;
	i = current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		// usleep (100000);
		j = current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
		// printf ("%lld\n", j);
		// while (((j - i) % 10))
		// {
		// 	gettimeofday(&current_time, NULL);
		// 	j = current_time.tv_sec * 1000 + (current_time.tv_usec / 1000) ;
		// 	// printf ("%lld-----------------\n", j);
		// 	usleep (1);
		// }
		
		// k = (t * 1000) - (j - i);
		// j += k;
		if (!(((j - i) * t) % 100000))
		{
			printf ("%lld-\n", (j - i));
			t++;
		}
	}
	// usleep (1000000);
	return 0;
}
