/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:21:14 by tmarion           #+#    #+#             */
/*   Updated: 2025/02/10 13:20:43 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_file_pipe(t_pipex *pipex)
{
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
}

static void	second_free(t_pipex *pipex)
{
	if (pipex->paths)
		free(pipex->paths);
	if (pipex->cmd_path_1)
		free(pipex->cmd_path_1);
	if (pipex->cmd_path_2)
		free(pipex->cmd_path_2);
}

void	ft_free(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (!pipex)
		return ;
	if (pipex->cmd_1)
	{
		while (pipex->cmd_1[++i])
			free(pipex->cmd_1[i]);
		free(pipex->cmd_1);
	}
	i = -1;
	if (pipex->cmd_2)
	{
		while (pipex->cmd_2[++i])
			free(pipex->cmd_2[i]);
		free(pipex->cmd_2);
	}
	i = -1;
	while (pipex->paths && pipex->paths[++i])
		free(pipex->paths[i]);
	second_free(pipex);
}

void	error_exit(char *errormsg, t_pipex *pipex)
{
	ft_putstr_fd(errormsg, 2);
	ft_free(pipex);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *errormsg, t_pipex *pipex)
{
	perror(errormsg);
	ft_free(pipex);
	exit(EXIT_FAILURE);
}
