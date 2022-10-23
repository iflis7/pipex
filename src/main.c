/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 09:10:59 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/23 18:32:43 by hsaadi           ###   ########.fr       */
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
			i = 3;
			if (argc < 6)
				msg_exit("Program needs at least 5 args!\n👇Like👇\ninfile ls wc outfile");
			here_doc(&pipex);
		}
		else
		{
			i = 2;
			dup2(pipex.fd_in, STDIN_FILENO);
		}
		pipex_bonus(&pipex, argc, i);
	}
	msg_exit("Program needs at least 5 args!\n👇Like👇\ninfile ls wc outfile");
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int	fd;

// 	if (argc != 5 || !*envp)
// 		msg_exit("Program needs at least 5 args!\n👇Like👇\ninfile ls wc outfile");
// 	fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd == -1)
// 		msg_exit("Outfile couldn't be opened!");
// 	pipex(argv, envp, fd);
// 	close(fd);
// 	return (0);
// }