/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathwork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:50:29 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/06 22:40:34 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

bool	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
			++i;
		else
			return (false);
	}
	return (true);
}

char	**joincomand(t_pip *x)
{
	size_t	i;

	i = 0;
	while (x->paths[i] != NULL)
	{
		x->paths[i] = ft_re_strjoin(x->paths[i], x->comands[0]);
		if (!(x->paths[i]))
		{
			ft_free_2d((void ***)x->paths);
			return (NULL);
		}
		i++;
	}
	return (x->paths);
}

char	**parcing(char **envp)
{
	int		i;
	char	**parse;

	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
	}
	parse = ft_split(envp[i] + 5, ':');
	if (parse == NULL)
		return (NULL);
	i = -1;
	while (parse[++i] != NULL)
	{
		parse[i] = ft_re_strjoin(parse[i], "/");
		if (!(parse))
		{
			ft_free_2d((void ***)&parse);
			return (NULL);
		}
	}
	return (parse);
}

char	*checkpath(t_pip *x)
{
	size_t	i;

	i = 0;
	while (x->paths[i])
	{
		if (access(x->paths[i], F_OK) == 0)
			return (x->paths[i]);
		++i;
	}
	return (x->paths[i]);
}

char	*createpath(char **envp, t_pip *x, char *av)
{
	if (is_only_space(av) == true)
	{
		free((x->comands = NULL, x->finalpath = NULL, NULL));
		return (x->finalpath);
	}
	x->comands = ft_split(av, ' ');
	if (x->comands == NULL)
	{
		x->finalpath = ft_strdup("");
		free_and_exit("Command not found", 127, x, false);
	}
	if (access(x->comands[0], F_OK | X_OK) == 0)
		return (x->finalpath = ft_strdup(x->comands[0]), x->finalpath);
	x->paths = parcing(envp);
	if (x->paths == NULL)
		return (NULL);
	x->paths = joincomand(x);
	if (x->paths == NULL)
	{
		x->finalpath = ft_strdup("");
		free_and_exit("Command not found", 127, x, false);
	}
	return (x->finalpath = checkpath(x), x->finalpath);
}
