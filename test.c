#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>

void	f()
{
	system("leaks a.out");
}

int	main()
{
	// atexit(f);
	char	*str = strdup("name=alex");
	char	*new = strchr(str, '=');
	free(str);
	str = NULL;
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
	printf("%s\n", new);
}
