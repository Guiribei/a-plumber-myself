/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:44:43 by guribeir          #+#    #+#             */
/*   Updated: 2022/08/24 03:14:58 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	change_inout(int input, int output, t_data *pipex)
{
	if (dup2(input, 0) == -1)
		perror_handler("dup: ", "", 1, pipex);
	if (dup2(output, 1) == -1)
		perror_handler("dup: ", "", 1, pipex);
}

static void	child(t_data *pipex)
{
	if (pipex->i == 0)
		change_inout(pipex->fd_in, pipex->pipe[1], pipex);
	else if (pipex->i == pipex->num_cmds - 1)
		change_inout(pipex->pipe[(2 * pipex->i) - 2], pipex->fd_out, pipex);
	else
		change_inout(pipex->pipe[(2 * pipex->i) - 2],
			pipex->pipe[(2 * pipex->i) + 1], pipex);
	full_close(pipex);
	if (pipex->cmds == NULL || pipex->path_cmd == NULL)
		error_quit(127, pipex);
	if (execve(pipex->path_cmd, pipex->cmds, pipex->envp) == -1)
		perror_handler(pipex->path_cmd, ": ", 1, pipex);
}

static int	parent(t_data *pipex)
{
	pid_t	pid;
	int		status;
	int		exitcode;

	full_close(pipex);
	pipex->i--;
	exitcode = 1;
	while (pipex->i >= 0)
	{
		pid = waitpid(pipex->pids[pipex->i], &status, 0);
		if (pid == pipex->pids[pipex->num_cmds - 1])
		{
			if ((pipex->i == (pipex->num_cmds - 1)) && WIFEXITED(status))
				exitcode = WEXITSTATUS(status);
		}
		pipex->i--;
	}
	free(pipex->pipe);
	free(pipex->pids);
	return (exitcode);
}

static int	core(t_data *pipex)
{
	int	exitcode;

	if (pipe(pipex->pipe) == -1)
		error_handler("pipe:", "invalid pipe", 1, pipex);
	pipex->i = 0;
	while (pipex->i < pipex->num_cmds)
	{
		pipex->k = before_split(pipex, pipex->argv[pipex->i + 2]);
		pipex->cmds = ft_split(pipex->argv[pipex->i + 2], ' ');
		if (pipex->k)
			put_space(pipex);
		if (!pipex->cmds)
			perror_handler("core: ", "", 1, pipex);
		pipex->path_cmd = find_cmd(pipex->cmds[0], pipex);
		pipex->pids[pipex->i] = fork();
		if (pipex->pids[pipex->i] == -1)
			perror_handler("fork: ", "", 1, pipex);
		else if (pipex->pids[pipex->i] == 0)
			child(pipex);
		strclear(&(pipex->path_cmd));
		strsclear(pipex->cmds);
		pipex->i++;
	}
	exitcode = parent(pipex);
	return (exitcode);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;
	int		exitcode;

	if (argc < 5)
	{
		write(2, "Use as follow: ./pipex file1 cmd1 cmd2 ... file2\n", 49);
		return (1);
	}
	if (!envp || envp [0][0] == '\0')
		error_handler("Enviroment error", "", 1, &pipex);
	pipex = init(argc, argv, envp);
	exitcode = core(&pipex);
	return (exitcode);
}
