/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:53:12 by idahhan           #+#    #+#             */
/*   Updated: 2025/01/19 12:25:43 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

char	*get_env_value(char *name, char **env)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
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
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*tmp;

	i = 0;
	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	full_path = NULL;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	ft_free_split(paths);
	perror("Error : Command not found");
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
