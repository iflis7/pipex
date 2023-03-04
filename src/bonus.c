#include "../include/pipex.h"

int	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	if (ft_strncmp(argv[1], "here_doc", 8))
	{
		pipex->fd_in = open(argv[1], O_RDONLY, 0644);
		if (pipex->fd_in == -1)
			msg_exit("Infile couldn't be opened!");
		pipex->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pipex->fd_out == -1)
			msg_exit("Outfile couldn't be opened!");
	}
	else
		pipex->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if (pipex->fd_out == -1)
		msg_exit("Outfile couldn't be opened!");
	pipex->cmd_n = argc - 2;
	pipex->env = envp;
	pipex->argv = argv;
	return (true);
};

bool	run_process(t_pipex *pipex, int i)
{
	char	*cmd;
	char	**opt;

	cmd = get_cmd(pipex->argv[i], pipex->env);
	opt = ft_split(pipex->argv[i], ' ');
	if (pipe(pipex->pfd) == -1)
		msg_exit("Pipe creation failed!\n");
	pipex->child = fork();
	if (pipex->child == -1)
		msg_exit("Fork creation failed!\n");
	if (pipex->child == 0)
	{
		close(pipex->pfd[0]);
		dup2(pipex->fd_in, STDIN_FILENO);
		dup2(pipex->pfd[1], STDOUT_FILENO);
		if (execve(cmd, opt, pipex->env) == -1)
			msg_exit("Command execution failed}!\n");
	}
	else
	{
		close(pipex->pfd[1]);
		dup2(pipex->pfd[0], STDIN_FILENO);
		waitpid(pipex->child, NULL, WNOHANG);
		fru(opt);
		free(cmd);
	}
	return (true);
};

void	pipex_bonus(t_pipex *pipex, int i)
{
	char	*cmd;
	char	**opt;

	while (i < pipex->cmd_n)
		run_process(pipex, i++);
	cmd = get_cmd(pipex->argv[i], pipex->env);
	opt = ft_split(pipex->argv[i], ' ');
	dup2(pipex->fd_out, STDOUT_FILENO);
	printf("opt[0]: %s\n", opt[0]);
	printf("opt[1]: %s\n", opt[1]);
	if (execve(cmd, opt, pipex->env) == -1)
		msg_exit("Command execution failed!\n");
	fru(opt);
	free(cmd);
};
