/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freework.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:04:29 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/06 22:23:48 by mdembele         ###   ########.fr       */
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

void	remove_files(char *filename)
{
	unlink(filename);
}

void	ft_close(int *fd, t_pip *x)
{
	if (*fd == -1 || *fd == STDIN_FILENO || *fd == STDERR_FILENO
		|| *fd == STDOUT_FILENO)
		return ;
	if (close(*fd) == -1)
	{
		*fd = -1;
		free_and_exit("CLOSE FAILED", EXIT_FAILURE, x, true);
	}
	*fd = -1;
}

void	print_err_and_exit(const char *err, int code, bool status)
{
	if (status == true)
	{
		perror((char *)err);
		exit(code);
	}
	if (err != NULL)
	{
		ft_putendl_fd((char *)err, STDERR_FILENO);
	}
	exit(code);
}

void	free_and_exit(const char *err, int code, t_pip *x, bool status)
{
	ft_free_2d((void ***)&x->comands);
	ft_free_2d((void ***)&x->paths);
	ft_free((void **)&x->pid);
	ft_free((void **)&x->finalpath);
	ft_close(&x->fd[0], x);
	ft_close(&x->fd[1], x);
	ft_close(&x->savefd, x);
	ft_close(&x->infile, x);
	ft_close(&x->outfile, x);
	if (x->here_dc == 1)
		remove_files("here_doc");
	print_err_and_exit(err, code, status);
}
