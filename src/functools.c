#include "../include/pipex.h"

char	***new_cmd(size_t rows, size_t j, t_pipex *pipex)
{
	char	***newArr;
	size_t	i;

	newArr = NULL;
	i = 0;
	newArr = malloc(sizeof(*newArr) * rows);
	if (!newArr)
		msg_exit("Something went wrong with malloc!");
	while (i < rows)
	{
		newArr[i] = malloc(sizeof(*newArr[i]) * 1);
		if (!newArr[i])
			msg_exit("Something went wrong with malloc!");
		newArr[i] = ft_split(pipex->argv[j], ' ');
		newArr[i][0] = get_cmd(pipex->argv[j++], pipex->env);
		i++;
	}
	return (newArr);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		rd;
	char	c;

	i = 0;
	rd = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	rd = read(0, &c, 1);
	while (rd && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		rd = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (rd);
}

void	here_doc(t_pipex *pipex)
{
	pid_t	rd;
	char *line;
	int pfd[2];
	if (pipex->cmd_n < 4)
			msg_exit("Needs at least 6 args when using here_doc!\n");
	if (pipe(pfd) == -1)
	// if (pipe(pipex->pfd) == -1)
		msg_error("Pipe creation failed!\n");
	// pipex->child = fork();
	rd = fork();
	// if (pipex->child == 0)
	if (rd == 0)
	{
		// close(pipex->pfd[0]);
		close(pfd[0]);
		while (get_next_line(&line))
		{
			printf("line: %s\n", line);
			printf("pipex->argv[2]: %s\n", line);
			if (ft_strncmp(line, pipex->argv[2],
					ft_strlen(pipex->argv[2])) == 0)
				exit(EXIT_SUCCESS);
			// write(pipex->pfd[1], line, ft_strlen(line));
			write(pfd[1], line, ft_strlen(line));
		}
	}
	else
	{
		// close(pipex->pfd[1]);
		// dup2(pipex->pfd[0], STDIN_FILENO);
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		wait(NULL);
	}
}