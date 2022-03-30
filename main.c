Esto va dentro del get_next_line.c

int	main(void)
{
	int	fd;
	char	*line;
	int	i;

	i = 1;
	fd = open("prueba.txt", O_RDONLY);
	printf("el fd: %d", fd);
	while (i < 7)
	{
		line = get_next_line(fd);
		printf("Linea %02d: %s", i, line);
		i++;
		free(line);
	}
	close(fd);
	return (0);
}
