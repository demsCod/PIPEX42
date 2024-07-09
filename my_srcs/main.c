/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:04:15 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/07 20:41:41 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_process(t_pip *x)
{
	int	i;

	i = 0;
	while (i < x->numbers - 2)
	{
		waitpid(x->pid[i], &x->status, 0);
		if (WEXITSTATUS(x->status) != EXIT_SUCCESS)
			free_and_exit(NULL, WEXITSTATUS(x->status), x, false);
		++i;
	}
}

void	init_index(int *i, int *flag, t_pip *x)
{
	free((*i = 2, *flag = -1, NULL));
	if (x->here_dc == 1)
		free((*i = 3, x->numbers--, NULL));
}

void	pipex(t_pip *x, char **envp, char **av)
{
	int	flag;
	int	i;

	init_index(&i, &flag, x);
	x->pid = malloc(sizeof(pid_t) * x->numbers);
	if (x->pid == NULL)
		free_and_exit(NULL, EXIT_FAILURE, x, true);
	while (++flag < x->numbers - 2)
	{
		ft_pipe(x->fd, x);
		x->pid[flag] = fork();
		if (x->pid[flag] == -1)
			free_and_exit(FORK_FAIL, EXIT_FAILURE, x, true);
		if (x->pid[flag] == 0)
			sacrificechild(x, envp, flag, av[i]);
		else
		{
			ft_close(&x->fd[1], x);
			if (x->savefd != -1)
				ft_close(&x->savefd, x);
			free((x->savefd = x->fd[0], x->fd[0] = -1, NULL));
			i++;
		}
	}
	wait_process(x);
}

void	init_pipe(t_pip *x, int ac, char **av)
{
	x->numbers = ac - 1;
	x->infile = open(av[1], O_RDONLY);
	if (x->infile < 0)
	{
		if (access(av[1], F_OK) < 0)
			ft_putendl_fd("pipex: no such file or directory", 2);
		else
			ft_putendl_fd("Permission denied", 2);
	}
	if (x->here_dc == 0)
		x->outfile = open(av[x->numbers], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		x->outfile = open(av[x->numbers], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (x->outfile < 0)
	{
		ft_putendl_fd("pipex: permission denied", 2);
		ft_close(&x->infile, x);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pip	x;

	ft_memset(&x, 0, sizeof(t_pip));
	if (ac < 5)
	{
		perror("🤦💀​, Args should look like this : file1 cmd1 ... cmdn files2");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp("here_doc", av[1], 8) == 0 && av[1][8] == '\0')
	{
		if (ac < 6)
		{
			perror("🤦💀​,Args should be like this : HERE_DOC LIM...cmdn files");
			exit(EXIT_FAILURE);
		}
		here_doc(&x, av[1], av[2]);
		x.here_dc = 1;
	}
	init_pipe(&x, ac, av);
	pipex(&x, envp, av);
	free_and_exit(NULL, EXIT_SUCCESS, &x, false);
}
