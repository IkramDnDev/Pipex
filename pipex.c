/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:11:43 by idahhan           #+#    #+#             */
/*   Updated: 2025/02/07 17:22:44 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	child1_process(char **argv, char **env, int *fd)
{
	int	infd;

	close(fd[0]);
	infd = open(argv[1], O_RDONLY, 0777);
	if (infd == -1)
	{
		close_fds_except_std();
		error();
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);
	close(fd[1]);
	close(infd);
	execute_command(argv[2], env);
}

void	child2_process(char **argv, char **env, int *fd)
{
	int	outfd;

	close(fd[1]);
	outfd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfd == -1)
	{
		close_fds_except_std();
		error();
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	close(fd[0]);
	close(outfd);
	execute_command(argv[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac == 5)
	{
		handle_pipe(fd);
		pid1 = fork();
		handle_fork_error(pid1);
		if (pid1 == 0)
			child1_process(av, env, fd);
		pid2 = fork();
		handle_fork_error(pid2);
		if (pid2 == 0)
			child2_process(av, env, fd);
		close(fd[0]);
		close(fd[1]);
		close_fds_except_std();
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
		write(2, "number of argument is not valid !", 34);
	return (0);
}
