/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:21:14 by tmarion           #+#    #+#             */
/*   Updated: 2025/02/10 17:28:37 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	second_free(t_pipex *pipex)
{
	if (pipex->paths)
		free(pipex->paths);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
}

void	ft_free(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (!pipex)
		return ;
	if (pipex->cmd)
	{
		while (pipex->cmd[++i])
			free(pipex->cmd[i]);
		free(pipex->cmd);
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
	exit(0);
}

void	perror_exit(char *errormsg, t_pipex *pipex)
{
	perror(errormsg);
	ft_free(pipex);
	exit(0);
}
