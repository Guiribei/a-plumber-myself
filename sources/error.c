/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:21:03 by guribeir          #+#    #+#             */
/*   Updated: 2022/08/23 20:22:52 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(char *str1, char *str2, int status, t_data *pipex)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	if (pipex)
	{
		full_close(pipex);
		if (pipex->pipe != NULL)
			free(pipex->pipe);
		if (pipex->pids != NULL)
			free(pipex->pids);
		if (pipex->cmds != NULL)
			strsclear(pipex->cmds);
		if (pipex->path_cmd != NULL)
			strclear(&(pipex->path_cmd));
	}
	exit(status);
}

void	perror_handler(char *str1, char *str2, int status, t_data *pipex)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	perror("");
	if (pipex)
	{
		full_close(pipex);
		if (pipex->pipe != NULL)
			free(pipex->pipe);
		if (pipex->pids != NULL)
			free(pipex->pids);
		if (pipex->cmds != NULL)
			strsclear(pipex->cmds);
		if (pipex->path_cmd != NULL)
			strclear(&(pipex->path_cmd));
	}
	exit(status);
}

void	error_quit(int status, t_data *pipex)
{
	if (pipex)
	{
		full_close(pipex);
		if (pipex->pipe != NULL)
			free(pipex->pipe);
		if (pipex->pids != NULL)
			free(pipex->pids);
		if (pipex->cmds != NULL)
			strsclear(pipex->cmds);
		if (pipex->path_cmd != NULL)
			strclear(&(pipex->path_cmd));
		if (pipex->curr_cmd)
			strsclear(pipex->curr_cmd);
	}
	exit(status);
}
