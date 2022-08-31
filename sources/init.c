/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 03:54:08 by guribeir          #+#    #+#             */
/*   Updated: 2022/08/23 22:41:36 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	create_pipes(t_data *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		if (pipe(pipex->pipe + 2 * i) == -1)
			perror_handler("create_pipe: ", "", 1, pipex);
		i++;
	}
}

static void	open_input_file(t_data *pipex)
{
	pipex->fd_in = open(pipex->argv[1], O_RDONLY, 644);
	if (pipex->fd_in == -1)
		perror_handler(pipex->argv[1], ": ", 0, pipex);
}

static void	open_output_file(t_data *pipex)
{
	pipex->fd_out = open(pipex->argv[pipex->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
		perror_handler(pipex->argv[pipex->argc - 1], ": ", 1, pipex);
}

static t_data	init_data(void)
{
	t_data	pipex;

	pipex.argc = -1;
	pipex.argv = NULL;
	pipex.envp = NULL;
	pipex.cmds = NULL;
	pipex.path_cmd = NULL;
	pipex.fd_in = -1;
	pipex.fd_out = -1;
	pipex.pipe = NULL;
	pipex.num_cmds = -1;
	pipex.curr_cmd = NULL;
	pipex.pids = NULL;
	pipex.i = -1;
	pipex.j = -1;
	pipex.k = 0;
	return (pipex);
}

t_data	init(int argc, char **argv, char **envp)
{
	t_data	pipex;

	pipex = init_data();
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.j = 1;
	open_input_file(&pipex);
	open_output_file(&pipex);
	pipex.num_cmds = argc - 3;
	pipex.pids = malloc(pipex.num_cmds * sizeof(pipex.pids));
	if (!pipex.pids)
		error_handler("init: ", "malloc error", 1, &pipex);
	pipex.pipe = malloc(2 * (pipex.num_cmds - 1) * sizeof(pipex.pipe));
	if (!pipex.pipe)
		error_handler("init: ", "fail malloc for pipe", 1, &pipex);
	create_pipes(&pipex);
	return (pipex);
}
