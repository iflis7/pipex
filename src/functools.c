#include "../include/pipex.h"

// bool create_pipes(t_pipex *pipex)
// {
//     int i;

//     i = 0;
//     pipex->pipe = malloc(sizeof(t_pipe) * (pipex->cmd_n));
//     // pipex->pfd[2] = malloc(sizeof(int) * (pipex->cmd_n));
//     while (i < pipex->cmd_n)
//     {
//         if (pipe(pipex->pipe[i].pfd) == -1)
//             msg_error("Pipe creation failed!\n");
//         i++;
//     }
//     // while (i < pipex->cmd_n)
//     // {
//     //     if (pipe(pipex->pfd[i]) == -1)
//     //         msg_error("Pipe creation failed!\n");
//     //     i++;
//     // }
//     return (true);
// }

// void	create_pipes(t_pipex *pipex)
// {
// 	int i = 0;
// 	pipex->pfd = malloc(sizeof(int) * pipex->cmd_n);
// 	while (i < pipex->cmd_n)
// 	{
// 		if (pipe(pipex->pfd + (2 * i++)) == -1)
// 			msg_error("Pipe creation failed!\n");
// 	}
// }
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
	char	*line;

	if (pipe(pipex->pfd) == -1)
		msg_error("Pipe creation failed!\n");
	pipex->child = fork();
	if (pipex->child == 0)
	{
		close(pipex->pfd[0]);
		printf("heredoc> \n");
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, pipex->argv[2], ft_strlen(pipex->argv[2])) == 0)
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