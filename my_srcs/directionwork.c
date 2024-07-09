/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directionwork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:04:15 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/06 22:48:19 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_dup2(int *fd1, int fd2, t_pip *x)
{
	if (dup2(*fd1, fd2) == -1)
		free_and_exit(NULL, EXIT_FAILURE, x, false);
	ft_close(fd1, x);
}

void	ft_pipe(int fd[2], t_pip *x)
{
	if (pipe(fd) == -1)
		free_and_exit(PIP_FAIL, EXIT_FAILURE, x, true);
}

void	killchild(t_pip *x, char **envp)
{
	if (x->finalpath == NULL)
	{
		if (x->comands != NULL && ft_strchr(x->comands[0], '/'))
		{
			ft_putstr_fd("No such file or directory :", 2);
			if (x->comands)
				ft_putendl_fd(x->comands[0], 2);
			free_and_exit(NULL, 127, x, false);
		}
		else
			ft_putstr_fd("pipex: command not found: ", 2);
		if (x->comands)
			ft_putendl_fd(x->comands[0], 2);
		free_and_exit(NULL, 127, x, false);
	}
	if (execve(x->finalpath, x->comands, envp) < 0)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		if (x->comands)
			ft_putendl_fd(x->comands[0], 2);
		else
			ft_putendl_fd(" ", 2);
		x->finalpath = NULL;
		free_and_exit(NULL, 127, x, false);
	}
}

void	sacrificechild(t_pip *x, char **envp, int flag, char *args)
{
	x->finalpath = createpath(envp, x, args);
	if (flag == 0)
	{
		ft_dup2(&x->infile, STDIN_FILENO, x);
		ft_dup2(&x->fd[1], STDOUT_FILENO, x);
		free((ft_close(&x->fd[0], x), ft_close(&x->outfile, x), NULL));
		killchild(x, envp);
	}
	else if (flag == x->numbers - 3)
	{
		free((ft_close(&x->fd[1], x), ft_close(&x->fd[0], x), NULL));
		ft_close(&x->infile, x);
		ft_dup2(&x->savefd, STDIN_FILENO, x);
		ft_dup2(&x->outfile, STDOUT_FILENO, x);
		killchild(x, envp);
	}
	else
	{
		ft_close(&x->fd[0], x);
		ft_close(&x->outfile, x);
		ft_close(&x->infile, x);
		ft_dup2(&x->savefd, STDIN_FILENO, x);
		ft_dup2(&x->fd[1], STDOUT_FILENO, x);
		killchild(x, envp);
	}
}
