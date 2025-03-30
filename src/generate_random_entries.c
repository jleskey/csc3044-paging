/*
	NAME:
	DATE:
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int errnum;
	long *values;

	printf("argc=%d\n", argc);
	if (argc < 4)
	{
		printf("Usage: %s filename num_entries max_page\n", argv[0]);
		exit(1);
	}

	srand(time(0));

	int fd = open(argv[1], O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		errnum = errno;
		fprintf(stderr, "Value of errno: %d\n", errno);
		perror("Error printed by perror");
		fprintf(stderr, "Error opening file %s\n", strerror(errnum));
	}

	long num_entries = atol(argv[2]);
	long max_entry = atol(argv[3]);
	values = (long *)malloc(sizeof(long) * num_entries);
	for (long i = 0; i < num_entries; i++)
	{
		values[i] = rand() % max_entry;
		printf("values[%ld]=%ld\n", i, values[i]);
	}

	for (long i = 0; i < num_entries; i++)
	{
		write(fd, &values[i], sizeof(long));
	}

	close(fd);
	return 0;
}
