/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:36:35 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/26 01:21:24 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	fru(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	// free(str);
}

void	fruthree(char ***str)
{
	int	i;

	i = -1;
	while (str[++i])
		fru(str[i]);
}

void	msg_exit(char *error)
{
	write(2, "Exit: ", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	waiting(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_n)
		waitpid(-1, NULL, 0);
}
