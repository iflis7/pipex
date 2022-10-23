#include "../include/pipex.h"

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		rd;
	char	c;

	i = 0;
	rd = 0;
	buffer = (char *)malloc(1000);
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
	char *line;

	if (pipe(pipex->pfd) == -1)
		msg_error("Pipe creation failed!\n");
	pipex->child = fork();
	if (pipex->child == 0)
	{
		close(pipex->pfd[0]);
		printf("heredoc> \n");
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, pipex->argv[2],
					ft_strlen(pipex->argv[2])) == 0)
				exit(EXIT_SUCCESS);
			write(pipex->pfd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(pipex->pfd[1]);
		dup2(pipex->pfd[0], STDIN_FILENO);
		wait(NULL);
	}
}