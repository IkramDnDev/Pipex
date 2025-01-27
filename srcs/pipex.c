/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:11:43 by idahhan           #+#    #+#             */
/*   Updated: 2025/01/25 10:31:49 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **env, int *fd)
{
	int	infd;

	close(fd[0]);
	infd = open(argv[1], O_RDONLY, 0777);
	if (infd == -1)
	{
		perror("Error opening infile");
		exit(1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);
	close(fd[1]);
	close(infd);
	execute_command(argv[2], env);
}

void	parent_process(char **argv, char **env, int *fd)
{
	int	outfd;

	close(fd[1]);
	outfd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfd == -1)
	{
		perror("Error opening outfile");
		exit(1);
	}
	if (access(argv[4], W_OK) != 0)
	{
		perror("Error permission");
		exit(1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	close(fd[0]);
	close(outfd);
	execute_command(argv[3], env);
}

void	le(void)
{
	system("leaks pipex");
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			child_process(av, env, fd);
		waitpid(pid, NULL, 0);
		parent_process(av, env, fd);
	}
	else
		write(1, "number of argument is not valid !", 33);
	atexit(le);
	return (0);
}
