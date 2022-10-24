/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:36:35 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/24 11:00:25 by hsaadi           ###   ########.fr       */
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

void	waiting(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_n)
		waitpid(-1, NULL, 0);
}
