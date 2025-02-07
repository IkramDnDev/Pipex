/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:11:07 by idahhan           #+#    #+#             */
/*   Updated: 2025/02/07 15:42:21 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	error(void);
void	handle_pipe(int fd[2]);
void	handle_fork_error(pid_t pid);
void	child1_process(char **argv, char **env, int *fd);
void	child2_process(char **argv, char **env, int *fd);
void	ft_free_split(char **split);
void	execute_command(char *cmd, char **env);

char	**get_path_directories(char **env);
char	*find_command_path(const char *command, char **env);
char	*get_full_path_from_paths(char *command, char **paths);
void	close_fds_except_std(void);

void	handle_pipe(int fd[2]);
void	handle_fork_error(pid_t pid);
#endif
