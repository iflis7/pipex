/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:40:21 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/26 01:42:31 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_cmd(char *paths, char **envp)
{
	char	**opt;
	char	*ret;
	char	*cmd;

	opt = ft_split(paths, ' ');
	if (access(*opt, (R_OK, X_OK)) == 0)
		return (*opt);
	cmd = ft_strjoin("/", *opt);
	ret = get_cmd_path(envp, cmd);
	if (access(ret, (R_OK, X_OK)) == 0)
	{
		free(cmd);
		fru(opt);
		return (ret);
	}
	free(cmd);
	free(ret);
	fru(opt);
	return (NULL);
}

char	*get_cmd_path(char **envp, char *cmd)
{
	char	**conc;
	char	*temp;
	// int i = -1;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", ft_strlen(*envp)))
		{
			conc = ft_split(ft_strnstr(*envp, "PATH=", ft_strlen(*envp)), ':');
			while (*conc)
			// while (conc[++i])
			{
				// printf(	"*conc = %s\n", *conc);
				// printf(	"[i] = %d\n", i);
				
				// printf(	"conc[i] = %s\n", conc[i]);
				// temp = ft_strjoin(conc[i], cmd);
				temp = ft_strjoin(*conc, cmd);
				if (access(temp, (R_OK, X_OK)) == 0)
				{
					fru(conc);
					// free(conc);
					// printf(	"::temp------ = %s\n", temp); 
					return (temp);
				}
				// printf(	"::temp------ = %s\n", temp);
				free(temp);
				// i++;
				(conc)++;
			}
			// fru(conc);
			// free(*conc); 
		}
		envp++;
	}
	fru(conc);
	free(cmd);
	// free(conc);
	msg_exit("Command not found!");
	return (NULL);
}
