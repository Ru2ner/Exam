/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:49:21 by tmarion           #+#    #+#             */
/*   Updated: 2025/02/07 14:22:14 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_pipex *pipex, char **argv, char **env)
{
	if (!env)
		error_exit("error:failed to get env", pipex);
	pipex->paths = get_paths(env);
	if (!pipex->paths)
		error_exit("error:failed to get path(s)", pipex);
	pipex->cmd_1 = cmd_arg(argv[2]);
	pipex->cmd_2 = cmd_arg(argv[3]);
	if (!pipex->cmd_1 || !pipex->cmd_2)
		error_exit("error:failed to parse command", pipex);
	pipex->cmd_path_1 = cmd_path(pipex->cmd_1[0], pipex->paths);
	pipex->cmd_path_2 = cmd_path(pipex->cmd_2[0], pipex->paths);
	if (!pipex->cmd_path_1 || !pipex->cmd_path_2)
		error_exit("error:command not found", pipex);
	if (pipe(pipex->pipe_fd) == -1)
		perror_exit("error:failde to create a pipe", pipex);
	pipex->pid_2 = -1;
	pipex->pid_2 = -1;
}

char	**get_paths(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**cmd_arg(char *cmd)
{
	char	**arg;

	if (!cmd)
		return (NULL);
	arg = ft_split(cmd, ' ');
	if (!arg)
		return (NULL);
	return (arg);
}

char	*cmd_path(char *cmd, char **path)
{
	char	*temp;
	char	*tempo;
	int		i;

	i = 0;
	if (!cmd || !path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	while (path[i])
	{
		temp = ft_strdup(path[i]);
		temp = ft_strjoin(temp, "/");
		tempo = ft_strjoin(temp, cmd);
		if (!tempo)
			return (NULL);
		if (access(tempo, X_OK) == 0)
			return (tempo);
		i++;
		free(tempo);
	}
	return (NULL);
}
