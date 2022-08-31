/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:48:04 by guribeir          #+#    #+#             */
/*   Updated: 2022/08/24 23:22:34 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**cmds;
	char	**curr_cmd;
	char	*path_cmd;
	int		fd_in;
	int		fd_out;
	int		*pipe;
	int		num_cmds;
	int		*pids;
	int		i;
	int		j;
	int		k;
}				t_data;

void	strclear(char **str);
void	strsclear(char **ptrs);
char	*find_cmd(char *cmd, t_data *pipex);
t_data	init(int argc, char **argv, char **envp);
void	full_close(t_data *pipex);
void	error_handler(char *str1, char *str2, int status, t_data *pipex);
void	perror_handler(char *str1, char *str2, int status, t_data *pipex);
void	error_quit(int status, t_data *pipex);
int		before_split(t_data *pipex, char *cmd);
void	put_space(t_data *pipex);

#endif