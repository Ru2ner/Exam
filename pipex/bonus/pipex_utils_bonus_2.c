/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:21:15 by tmarion           #+#    #+#             */
/*   Updated: 2025/02/10 17:47:28 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_fd(t_pipex *pipex, char **argv, int argc)
{
	pipex->outfile = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		perror_exit_b("error: failed to open outputfile", pipex);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror_exit_b("error: failed to open inputfile", pipex);
}

int	end_process(t_pipex *pipex, char **argv, char **env, int i)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		perror_exit_b("error: failed to create a fork", pipex);
	if (pipex->pid == 0)
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			perror_exit_b("error: dup2 failed to STDOUT", pipex);
		exec_cmd(pipex, argv, env, i);
	}
	else
		waitpid(pipex->pid, NULL, 0);
	return (1);
}

void	close_file(t_pipex *pipex)
{
	pipex->infile = 0;
	pipex->outfile = 0;

	if (pipex->infile && pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile && pipex->outfile != -1)
		close(pipex->outfile);
}

void	close_pipe(int *fd)
{
	if (!fd)
		return ;
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}
