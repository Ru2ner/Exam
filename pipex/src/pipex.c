/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:28:14 by tmarion           #+#    #+#             */
/*   Updated: 2025/02/10 15:03:22 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_simple_fd(t_pipex *pipex, char **argv, int argc)
{
	pipex->outfile = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		perror_exit("error: failed to open outputfile", pipex);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror_exit("error: failed to open inputfile", pipex);
}

static void	child_two(t_pipex *pipex, char **env)
{
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		perror_exit("error: dup2 failed to STDIN (child 2)", pipex);
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		perror_exit("error: dup2 failed to STDOUT (child 2)", pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (execve(pipex->cmd_path_2, pipex->cmd_2, env) == -1)
		perror_exit("error: command not found", pipex);
}

static void	child_one(t_pipex *pipex, char **env)
{
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		perror_exit("error: dup2 failed to STDIN (child 1)", pipex);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		perror_exit("error: dup2 failed to STDOUT (child 1)", pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (execve(pipex->cmd_path_1, pipex->cmd_1, env) == -1)
		perror_exit("error: command not found", pipex);
}

static int	simple_pipex(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		statu1;
	int		statu2;

	ft_init(&pipex, argv, env);
	open_simple_fd(&pipex, argv, argc);
	pipex.pid_1 = fork();
	if (pipex.pid_1 == -1)
		perror_exit("error: failed to create a fork", &pipex);
	if (pipex.pid_1 == 0)
		child_one(&pipex, env);
	pipex.pid_2 = fork();
	if (pipex.pid_2 == -1)
		perror_exit("error: failed to create a fork", &pipex);
	if (pipex.pid_2 == 0)
		child_two(&pipex, env);
	close_file_pipe(&pipex);
	waitpid(pipex.pid_1, &statu1, 0);
	waitpid(pipex.pid_2, &statu2, 0);
	ft_free(&pipex);
	exit(WEXITSTATUS(statu2));
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		ft_putstr_fd("error: Insufficient number of arguments", 2);
		return (0);
	}
	simple_pipex(argc, argv, env);
	return (1);
}
