/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:11:07 by idahhan           #+#    #+#             */
/*   Updated: 2025/02/01 16:53:16 by idahhan          ###   ########.fr       */
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
void	child_process(char **argv, char **env, int *fd);
void	parent_process(char **argv, char **env, int *fd);
void	ft_free_split(char **split);
void	execute_command(char *cmd, char **env);

char	**get_path_directories(char **env);
char	*find_command_path(const char *command, char **env);
char	*get_full_path_from_paths(char *command, char **paths);

#endif
