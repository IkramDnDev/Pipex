/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:34:53 by idahhan           #+#    #+#             */
/*   Updated: 2025/02/07 17:22:36 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex_bonus.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

void	child_process(char *av, char **env)
{
	int		fd[2];
	pid_t	pid;

	handle_pipe(fd);
	pid = fork();
	handle_fork_error(pid);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(av, env);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	handle_here_doc(char *limiter)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	handle_pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			write(STDOUT_FILENO, "pipe heredoc> ", 15);
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
				&& line[ft_strlen(limiter)] == '\n')
				return (free(line), close(fd[1]), exit(0));
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
}

void	process_children(int ac, int i, char **av, char **env)
{
	while (i < (ac - 2))
		child_process(av[i++], env);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	outfd;
	int	infd;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0)
		{
			i = 3;
			outfd = open_file(av[ac - 1], 0);
			handle_here_doc(av[2]);
		}
		else
		{
			i = 2;
			outfd = open_file(av[ac - 1], 1);
			infd = open_file(av[1], 2);
			dup2(infd, STDIN_FILENO);
		}
		process_children(ac, i, av, env);
		dup2(outfd, STDOUT_FILENO);
		close_fds_except_std();
		execute_command(av[ac - 2], env);
	}
	write(STDERR_FILENO, "Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 46);
}
