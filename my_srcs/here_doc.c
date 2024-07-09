/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:27:36 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/06 22:28:30 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*gnlfunction(char *str)
{
	return (free(str), get_next_line(0));
}

void	here_doc(t_pip *x, char *av, char *lim)
{
	char	*temp;
	char	*total;
	int		size;

	size = ft_strlen(lim);
	total = ft_strdup("");
	if (!total)
		exit(EXIT_FAILURE);
	temp = ft_strdup("");
	while (temp)
	{
		temp = gnlfunction(temp);
		if (ft_strncmp(temp, lim, size) == 0 && temp[size] == '\n')
			break ;
		total = ft_re_strjoin(total, temp);
		if (total == NULL)
			exit(EXIT_FAILURE);
	}
	x->infile = open(av, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*total)
		ft_putstr_fd(total, x->infile);
	close(x->infile);
	ft_free((void **)&total);
	ft_free((void **)&temp);
}
