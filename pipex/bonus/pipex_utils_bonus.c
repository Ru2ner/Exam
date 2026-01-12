/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:54:11 by tmarion           #+#    #+#             */
/*   Updated: 2025/02/10 17:36:02 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_bonus(t_pipex *pipex, char **env)
{
	if (!env)
		error_exit_b("error:failed to get env", pipex);
	pipex->paths = get_paths(env);
	if (!pipex->paths)
		error_exit_b("error:failed to get path(s)", pipex);
	pipex->pid = -1;
	pipex->cmd = NULL;
	pipex->cmd_path = NULL;
}

void	ft_free_bonus(t_pipex *pipex, int trigger)
{
	int	i;

	i = 0;
	if (!pipex)
		return ;
	while (pipex->cmd && pipex->cmd[i])
	{
		free(pipex->cmd[i]);
		i++;
	}
	free(pipex->cmd);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
	i = 0;
	if (trigger == 1 && pipex->paths)
	{
		while (pipex->paths[i])
		{
			free(pipex->paths[i]);
			i++;
		}
		free(pipex->paths);
	}
}

int	exec_cmd(t_pipex *pipex, char **argv, char **env, int i)
{
	pipex->cmd = cmd_arg(argv[i]);
	if (!pipex->cmd)
	{
		error_exit_b("error:failed to parse command", pipex);
	}
	pipex->cmd_path = cmd_path(pipex->cmd[0], pipex->paths);
	if (!pipex->cmd_path)
		error_exit_b("error:command not found", pipex);
	if (execve(pipex->cmd_path, pipex->cmd, env) == -1)
		perror_exit_b("error: command not found", pipex);
	ft_free_bonus(pipex, 0);
	return (1);
}

void	error_exit_b(char *errormsg, t_pipex *pipex)
{
	ft_putstr_fd(errormsg, 2);
	ft_free_bonus(pipex, 1);
	close_file(pipex);
	exit(0);
}

void	perror_exit_b(char *errormsg, t_pipex *pipex)
{
	perror(errormsg);
	ft_free_bonus(pipex, 1);
	close_file(pipex);
	exit(0);
}
