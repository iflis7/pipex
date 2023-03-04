/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 09:10:59 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/28 20:53:17 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	
	if (argc >= 5)
	{
		init_pipex(argc, argv, envp, &pipex);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = argc - 4;
			here_doc(&pipex);
		}
		else
		{
			i = argc - 3;
			dup2(pipex.fd_in, STDIN_FILENO);
		}
		pipex_bonus(&pipex, i);
		fru(pipex.argv);	
		fru(pipex.env);	
	}
	else
		msg_exit("Program needs at least 5 args!\n👇Like👇\ninfile ls wc outfile");
	return (0);
}
