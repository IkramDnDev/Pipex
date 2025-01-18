/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:34:53 by idahhan           #+#    #+#             */
/*   Updated: 2025/01/18 18:00:06 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void child_process2(char *av, char **env)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execute_command(av, env);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        waitpid(pid, NULL, 0);
    }
}

int main(int ac, char **av, char **env)
{
    int i = 2;
    int infd = open(av[1], O_RDONLY, 0777);
    if (infd == -1)
	{
		perror("Error opening infile");
		exit(1);
	}
    int outfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (outfd == -1)
	{
		perror("Error opening outfile");
		exit(1);
	}
    dup2(infd, STDIN_FILENO);
    while (i < ac - 2)
        child_process2(av[i++], env);
    dup2(outfd, STDOUT_FILENO);
    execute_command(av[ac - 2], env);
}