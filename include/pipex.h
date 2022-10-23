/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:36:53 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/23 18:47:11 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../include/libft/libft.h"

/* for write, read, close, access, pipe, dup, dup2, execve, fork */
# include <fcntl.h>

/* for perror*/
# include <stdbool.h>
# include <stdio.h>

typedef struct s_pipex
{
	pid_t	child;
	int		pfd[2];
	char	***cmd;
	char	**opts;
	char	**env;
	char	**argv;
	int		cmd_n;
	int		fd_in;
	int		fd_out;
}			t_pipex;

void		pipex(char **argv, char **envp, int fd);
bool		init_pipex(int argc, char **argv, char **envp, t_pipex *pipex);
// void		pipex_bonus(t_pipex *pipex, int i);
void		pipex_bonus(t_pipex *pipex, int argc, int i);

void		message(char *error);
void		msg_exit(char *error);
void		msg_error(char *error);

void		fru(char **str);
char		*get_cmd(char *paths, char **envp);
char		*get_cmd_path(char **envp, char *cmd);
void		waiting(t_pipex *pipex);
char		***new_cmd(size_t rows, t_pipex *pipex);
void		create_pipes(t_pipex *pipex);
void		here_doc(t_pipex *pipex);

#endif
