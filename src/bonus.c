#include "../include/pipex.h"

// static void	child_process1(char **argv, int *pfd, char **envp)
// {
// 	char	**concats;
// 	char	*cmd;
// 	int		fd1;
// 	fd1 = open(argv[1], O_RDONLY, 0644);
// 	if (fd1 == -1)
// 		msg_exit("Infile couldn't be opened!\nPlease check the pathname!");
// 	dup2(pfd[1], STDOUT_FILENO);
// 	dup2(fd1, STDIN_FILENO);
// 	close(pfd[0]);
// 	cmd = get_cmd(argv[2], envp);
// 	concats = ft_split(argv[2], ' ');
// 	if (execve(cmd, concats, envp) == -1)
// 		msg_error("Command execution failed!\n");
// 	free(cmd);
// 	fru(concats);
// 	close(pfd[1]);
// 	close(fd1);
// }

// static void	child_process2(int file, char **argv, int *pfd, char **envp)
// {
// 	char	**concats;
// 	char	*cmd;
// 	dup2(pfd[0], STDIN_FILENO);
// 	dup2(file, STDOUT_FILENO);
// 	close(pfd[1]);
// 	cmd = get_cmd(argv[3], envp);
// 	concats = ft_split(argv[3], ' ');
// 	if (execve(cmd, concats, envp) == -1)
// 		msg_error("Command execution failed!\n");
// 	free(cmd);
// 	fru(concats);
// 	close(pfd[0]);
// 	close(file);
// }

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}


bool	run_process(t_pipex *pipex, int i)
{
	printf(":I: %d\n", i);
	if (i == 1)
	{
		sub_dup2(pipex->fd_in, pipex->pfd[1]);
		// close(pipex->pfd[0]);
	}
	else if (i == pipex->cmd_n)
	{
		sub_dup2(pipex->pfd[0], pipex->fd_out);
		// close(pipex->pfd[1]);
	}
	// else
	// {
	// 	sub_dup2(pipex->pfd[0], pipex->pfd[1]);
	// 	// close(pipex->pfd[0]);
	// 	// close(pipex->pfd[1]);
	// }
	if (execve(*pipex->cmd[i], pipex->cmd[i], pipex->env) == -1)
		msg_error("Command execution failed!\n");
	if (i == 1)
	{
		close(pipex->pfd[1]);
		close(pipex->fd_in);
	}
	else if (i == pipex->cmd_n)
	{
		close(pipex->pfd[0]);
		close(pipex->fd_out);
	}
	return (true);
}

char	***new_cmd(size_t rows, t_pipex *pipex)
{
	char	***newArr;
	size_t	i;

	newArr = NULL;
	i = 0;
	newArr = malloc(sizeof(*newArr) * rows);
	if (!newArr)
		msg_exit("Something went wrong with malloc!");
	while (i < rows)
	{
		newArr[i] = malloc(sizeof(*newArr[i]) * 1);
		if (!newArr[i])
			msg_exit("Something went wrong with malloc!");
		newArr[i] = ft_split(pipex->argv[i + 2], ' ');
		newArr[i][0] = get_cmd(pipex->argv[i + 2], pipex->env);
		i++;
	}
	return (newArr);
}

bool	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	pipex->child = malloc(sizeof(int) * argc - 1);
	if (pipex->fd_out == -1)
		msg_exit("Something went wrong with malloc!");
	pipex->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
		msg_exit("Outfile couldn't be opened!");
	pipex->fd_in = open(argv[1], O_RDONLY, 0644);
	if (pipex->fd_in == -1)
		msg_exit("Outfile couldn't be opened!");
	if (pipe(pipex->pfd) == -1)
		msg_error("Pipe creation failed!\n");
	pipex->env = envp;
	pipex->argv = argv;
	pipex->cmd_n = argc - 3;
	pipex->cmd = new_cmd(argc - 3, pipex);
	return (true);
}

void	waiting(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_n)
		waitpid(-1, NULL, 0);
}

void	pipex_bonus(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_n)
	{
		// printf("I:: %d\n", i);
		pipex->child[i] = fork();
		if (pipex->child[i] < 0)
			return (perror("Fork: "));
		else if (pipex->child[i] == 0)
			run_process(pipex, i);
		i++;
	}
	close(pipex->pfd[0]);
	close(pipex->pfd[1]);
	waiting(pipex);
}
