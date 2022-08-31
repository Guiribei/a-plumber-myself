/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:35:53 by guribeir          #+#    #+#             */
/*   Updated: 2022/08/23 22:31:21 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_cmd_path(char *cmd, char **paths, t_data *pipex)
{
	int		i;
	char	*cmdpath;

	cmdpath = NULL;
	i = 0;
	while (paths[i])
	{
		cmdpath = ft_strjoin(paths[i], cmd);
		if (!cmdpath)
		{
			strsclear(paths);
			error_handler("find_cmd_path: ", "unexpected error", 1, pipex);
		}
		if (access(cmdpath, F_OK | X_OK) == 0)
			return (cmdpath);
		strclear(&cmdpath);
		i++;
	}
	return (NULL);
}

static char	**put_slash(char **paths)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		strclear(&temp);
		i++;
	}
	return (paths);
}

static char	*find_env_path(char **envp)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (envp[i] != NULL && envp[i][0] != '\0')
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			break ;
		}
		i++;
	}
	return (path);
}

static char	**find_paths(char **envp)
{
	char	*pathstr;
	char	**paths;

	pathstr = find_env_path(envp);
	if (!pathstr)
		return (NULL);
	paths = ft_split(pathstr, ':');
	strclear(&pathstr);
	if (!paths)
		return (NULL);
	paths = put_slash(paths);
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_cmd(char *cmd, t_data *pipex)
{
	char	*cmdpath;
	char	**paths;

	pipex-> j++;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	paths = find_paths(pipex->envp);
	if (!paths)
		return (NULL);
	cmdpath = find_cmd_path(cmd, paths, pipex);
	strsclear(paths);
	if (!cmdpath)
	{
		pipex->curr_cmd = ft_split(pipex->argv[pipex->j], ' ');
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(pipex->curr_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		if (pipex->j == pipex->argc - 2)
			error_quit(127, pipex);
	}
	return (cmdpath);
}
