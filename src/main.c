/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 09:10:59 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/21 19:39:06 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	if (argc < 5 || !*envp)
		msg_exit("Program needs at least 5 args!\n👇Like👇\ninfile ls wc outfile");
	init_pipex(argc, argv, envp, &pipex);
	pipex_bonus(&pipex);

	close(pipex.fd_out);
	return (0);
}
