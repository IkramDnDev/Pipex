/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:43:42 by idahhan           #+#    #+#             */
/*   Updated: 2025/02/01 16:52:54 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

void	error(void);
void	ft_free_split(char **split);
void	execute_command(char *cmd, char **env);
void	child_process(char *av, char **env);

char	*get_next_line(int fd);
char	**get_path_directories(char **env);
char	*find_command_path(const char *command, char **env);
char	*get_full_path_from_paths(char *command, char **paths);

int		open_file(char *argv, int i);

#endif