/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:57:31 by guribeir          #+#    #+#             */
/*   Updated: 2022/08/24 03:05:52 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	strclear(char **str)
{
	if (!str)
		return ;
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	strsclear(char **ptrs)
{
	int	i;

	if (ptrs != NULL)
	{
		i = 0;
		while (ptrs[i])
		{
			if (ptrs[i] != NULL)
				free(ptrs[i]);
			i++;
		}
		free(ptrs);
		ptrs = NULL;
	}
}

void	full_close(t_data *pipex)
{
	int	i;

	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	i = 0;
	while (i < 2 * (pipex->num_cmds - 1))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

int	before_split(t_data *pipex, char *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'')
		{
			j = i + 1;
			while (cmd[j] != '\'')
			{
				if (cmd[j] == ' ')
					pipex->argv[pipex->i + 2][j] = '~';
				j++;
			}
			return (1);
		}
	}
	return (0);
}

void	put_space(t_data *pipex)
{
	int		i;
	int		j;
	char	*aux;

	i = -1;
	while (pipex->cmds[++i])
	{
		j = -1;
		while (pipex->cmds[i][++j])
		{
			if (pipex->cmds[i][j] == '~')
			{
				while (pipex->cmds[i][j] == '~')
				{
					pipex->cmds[i][j] = ' ';
					j++;
				}
				aux = ft_strdup(pipex->cmds[i]);
				free(pipex->cmds[i]);
				pipex->cmds[i] = ft_strtrim(aux, "\'");
				free(aux);
				return ;
			}
		}
	}
}
