/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:34:53 by idahhan           #+#    #+#             */
/*   Updated: 2025/01/19 18:46:16 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

void child_process2(char *av, char **env)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
        error();
    pid = fork();
    if (pid == -1)
        error();
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

void handle_here_doc(char *limiter)
{
    int fd[2];
    pid_t pid;
    char *line;

    if (pipe(fd) == -1)
        error();
    pid = fork();
    if (pid == -1)
        error();
    if (pid == 0)
    {
        close(fd[0]);
        while (1)
        {
            write(STDOUT_FILENO, "heredoc> ", 9);
            line = get_next_line(STDIN_FILENO);
            if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
            {
                free(line);
                exit(1);
            }
            write(fd[1], line, ft_strlen(line));
            free(line);
        }
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
    int i;
    int outfd;
    if (ac >= 5)
    {
        if(ft_strncmp(av[1], "here_doc", 8) == 0)
        {
            i = 3;
            outfd = open(av[5], O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (outfd == -1)
                error();
            handle_here_doc(av[2]);
        }
        else
        {
            i = 2;
            int infd = open(av[1], O_RDONLY, 0777);
            if (infd == -1)
                error();
            outfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (outfd == -1)
                error();
            dup2(infd, STDIN_FILENO);
        }
        while (i < ac - 2)
            child_process2(av[i++], env);
        dup2(outfd, STDOUT_FILENO);
        execute_command(av[ac - 2], env);
    }
    else
        write(STDERR_FILENO, "Usage: ./pipex [here_doc] infile cmd1 cmd2 ... cmdn outfile\n", 59);
}
