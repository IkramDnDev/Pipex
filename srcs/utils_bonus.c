/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:53:12 by idahhan           #+#    #+#             */
/*   Updated: 2025/01/25 11:58:42 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

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

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*find_command_path(const char *command, char **env)
{
	int		i;
	char	**paths;
	char	*full_path;
	char	*tmp;

	paths = get_path_directories(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i++])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
		full_path = NULL;
	}
	perror("pipex: command not found");
	ft_free_split(paths);
	return (NULL);
}

void	error(void)
{
	perror("Error");
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
		perror("Error");
		exit(1);
	}
	path = find_command_path(cmd_split[0], env);
	if (!path)
	{
		ft_free_split(cmd_split);
		exit(1);
	}
	if (execve(path, cmd_split, env) == -1)
	{
		ft_free_split(cmd_split);
		perror("Execve Failed");
		exit(1);
	}
}
