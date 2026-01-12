/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:31:20 by tmarion           #+#    #+#             */
/*   Updated: 2025/02/10 15:24:52 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**paths;
	char	**cmd_1;
	char	**cmd_2;
	char	*cmd_path_1;
	char	*cmd_path_2;
	int		pipe_fd[2];
	pid_t	pid_1;
	pid_t	pid_2;
}		t_pipex;

char	*cmd_path(char *cmd, char **path);//utils_0
char	**get_paths(char **env);
char	**cmd_arg(char *cmd);
void	ft_init(t_pipex *pipex, char **argv, char **env);

void	close_file_pipe(t_pipex *pipex);//utils_1
void	ft_free(t_pipex *pipex);
void	error_exit(char *errormsg, t_pipex *pipex);
void	perror_exit(char *errormsg, t_pipex *pipex);

#endif