/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:28:14 by tmarion           #+#    #+#             */
/*   Updated: 2025/02/10 17:35:06 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	read_stdin(t_pipex *pipex, char **argv, int *pipe_fd)
{
	char	*temp;
	int		i;

	temp = NULL;
	if (!argv || !pipex)
		return (0);
	while (1)
	{
		i = ft_strlen(argv[2]);
		temp = get_next_line(0);
		if (!temp)
			return (0);
		if (ft_strncmp(temp, argv[2], i) == 0)
			return (free(temp), 1);
		ft_putstr_fd(temp, pipe_fd[1]);
		free(temp);
	}
	return (0);
}

void	here_doc(t_pipex *pipex, char **argv)
{
	pid_t	herdoc;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror_exit_b("error; failed to create a pipe", pipex);
	herdoc = fork();
	if (herdoc == 0)
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (read_stdin(pipex, argv, pipe_fd) == 1)
			error_exit_b("", pipex);
		else
			error_exit_b("error: failed to read STDOUT", pipex);
	}
	else
	{
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror_exit_b("error: dup2 failed to STDIN", pipex);
		wait(NULL);
	}
}

int	process(t_pipex *pipex, char **argv, char **env, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror_exit_b("error; failed to create a pipe", pipex);
	pipex->pid = fork();
	if (pipex->pid == -1)
		perror_exit_b("error: failed to create a fork", pipex);
	if (pipex->pid == 0)
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror_exit_b("error: dup2 failed to STDOUT", pipex);
		exec_cmd(pipex, argv, env, i);
	}
	else
	{
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror_exit_b("error: dup2 failed to STDIN", pipex);
		waitpid(pipex->pid, NULL, 0);
		close_pipe(pipe_fd);
	}
	return (1);
}

void	multiple_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	int		i;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
	{
		i = 3;
		pipex->outfile = open (argv[argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile == -1)
			perror_exit("error: failed to open outputfile", pipex);
		here_doc(pipex, argv);
	}
	else
	{
		i = 2;
		open_fd(pipex, argv, argc);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			perror_exit_b("error: dup2 failed to STDIN", pipex);
	}
	while (i < argc - 2)
		process(pipex, argv, env, i++);
	end_process(pipex, argv, env, i);
	close_file(pipex);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_putstr_fd("error: Insufficient number of arguments", 2);
		return (0);
	}
	ft_init_bonus(&pipex, env);
	multiple_pipex(&pipex, argc, argv, env);
	close_file(&pipex);
	ft_free_bonus(&pipex, 1);
	return (EXIT_SUCCESS);
}
