/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:48:23 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/25 00:55:20 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	***new_cmd(size_t rows, size_t j, t_pipex *pipex)
{
	char	***newarr;
	size_t	i;

	newarr = NULL;
	i = 0;
	newarr = malloc(sizeof(*newarr) * rows);
	if (!newarr)
		msg_exit("Something went wrong with malloc!");
	while (i < rows)
	{
		newarr[i] = ft_split(pipex->argv[j], ' ');
		newarr[i][0] = get_cmd(pipex->argv[j++], pipex->env);
		i++;
	}
	return (newarr);
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
	char	*line;

	if (pipex->cmd_n < 4)
		msg_exit("Needs at least 6 args when using here_doc!\n");
	if (pipe(pipex->pfd) == -1)
		msg_error("Pipe creation failed!\n");
	pipex->child = fork();
	if (pipex->child == 0)
	{
		close(pipex->pfd[0]);
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
