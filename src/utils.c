/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:36:35 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/22 11:18:08 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	fru(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
}

void	message(char *error)
{
	write(2, "Error: ", 8);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	msg_exit(char *error)
{
	write(2, "Exit: ", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	msg_error(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

char	***new_cmd(size_t rows, t_pipex *pipex)
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
		newArr[i] = ft_split(pipex->argv[i + 2], ' ');
		newArr[i][0] = get_cmd(pipex->argv[i + 2], pipex->env);
		i++;
	}
	return (newArr);
}

void	waiting(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_n)
		waitpid(-1, NULL, 0);
}
