/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:53:47 by idahhan           #+#    #+#             */
/*   Updated: 2025/02/07 17:18:22 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex_bonus.h"

void	handle_fork_error(pid_t pid)
{
	if (pid == -1)
		error();
}

void	handle_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		error();
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	close_fds_except_std(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}
