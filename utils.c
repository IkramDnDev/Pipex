/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:10:59 by idahhan           #+#    #+#             */
/*   Updated: 2025/02/01 16:37:45 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

char	**get_path_directories(char **env)
{
	size_t	len;
	int		i;
	char	*path_env;

	len = ft_strlen("PATH");
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], len) == 0 && env[i][len] == '=')
		{
			path_env = env[i] + len + 1;
			return (ft_split(path_env, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*get_full_path_from_paths(char *command, char **paths)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*find_command_path(const char *command, char **env)
{
	char	**paths;
	char	*full_path;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	paths = get_path_directories(env);
	if (!paths)
		return (NULL);
	full_path = get_full_path_from_paths((char *)command, paths);
	ft_free_split(paths);
	if (full_path)
		return (full_path);
	ft_putstr_fd("pipex: command not found\n", 2);
	return (NULL);
	exit(1);
}

void	execute_command(char *cmd, char **env)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		ft_free_split(cmd_split);
		error();
	}
	path = find_command_path(cmd_split[0], env);
	if (!path)
	{
		ft_free_split(cmd_split);
		error();
	}
	if (execve(path, cmd_split, env) == -1)
	{
		ft_free_split(cmd_split);
		error();
	}
}
