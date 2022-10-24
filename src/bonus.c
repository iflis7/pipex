#include "../include/pipex.h"

bool	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	if (ft_strncmp(argv[1], "here_doc", 8))
	{
		pipex->fd_in = open(argv[1], O_RDONLY, 0644);
		if (pipex->fd_in == -1)
			msg_exit("Infile couldn't be opened!");
	}
	pipex->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
		msg_exit("Outfile couldn't be opened!");
	pipex->cmd_n = argc - 2;
	pipex->env = envp;
	pipex->argv = argv;
	return (true);
}

bool	run_process(t_pipex *pipex, int i)
{
	if (pipe(pipex->pfd) == -1)
		msg_error("Pipe creation failed!\n");
	pipex->child = fork();
	if (pipex->child == -1)
		msg_error("Fork creation failed!\n");
	if (pipex->child == 0)
	{
		close(pipex->pfd[0]);
		printf("*pipex->cmd[i]: %s\n", *pipex->cmd[i]);
		dup2(pipex->pfd[1], STDOUT_FILENO);
		if (execve(*pipex->cmd[i], pipex->cmd[i], pipex->env) == -1)
			msg_error("Command execution failed!\n");
	}
	else
	{
		close(pipex->pfd[1]);
		dup2(pipex->pfd[0], STDIN_FILENO);
		waitpid(pipex->child, NULL, 0);
	}
	return (true);
}

void	pipex_bonus(t_pipex *pipex, int i)
{
	int	j;

	j = -1;
	while (++j < i - 1)
	{
		printf("::j:: %d\n", j);
		run_process(pipex, j);
	}
	dup2(pipex->fd_out, STDOUT_FILENO);
	if (execve(*pipex->cmd[j], pipex->cmd[j], pipex->env) == -1)
		msg_error("Command execution failed!\n");
}
