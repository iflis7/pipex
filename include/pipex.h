/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:36:53 by hsaadi            #+#    #+#             */
/*   Updated: 2022/06/14 10:36:16 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../include/libft/libft.h"

/* for write, read, close, access, pipe, dup, dup2, execve, fork */
# include <fcntl.h>

/* for perror*/
# include <stdio.h>

void	pipex(char **argv, char **envp, int fd);

void	message(char *error);
void	msg_exit(char *error);
void	msg_error(char *error);

void	fru(char **str);
char	*get_cmd(char *paths, char **envp);
char	*get_cmd_path(char **envp, char *cmd);

#endif
