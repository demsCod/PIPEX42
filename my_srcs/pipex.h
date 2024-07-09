/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:10:37 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/06 22:29:19 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MALLOC_FAIL "Malloc failed"
# define OPEN_FAIL "pipex: No such file or directory :"
# define CLOSE_FAIL "close failed"
# define FORK_FAIL "The fork failed"
# define DUP_FAIL "Dup fd fails"
# define PIP_FAIL "Pip fails"
# define EXEC_FAIL "Execve fails"
# include ".././libft_srcs/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_pip
{
	char	**paths;
	char	**comands;
	char	**args;
	char	*finalpath;
	bool	fakeinfile;
	int		numbers;
	int		status;
	int		fd[2];
	pid_t	*pid;
	int		flag;
	int		i;
	char	*nameout;
	int		here_dc;
	int		outfile;
	int		infile;
	int		savefd;
}			t_pip;

void		ft_close(int *fd, t_pip *x);
void		ft_pipe(int fd[2], t_pip *x);
char		**joincomand(t_pip *x);
char		**parcing(char **envp);
void		here_doc(t_pip *x, char *av, char *lim);
char		*gnlfunction(char *str);
char		*createpath(char **envp, t_pip *x, char *av);
char		*checkpath(t_pip *x);
void		free_and_exit(const char *err, int code, t_pip *x, bool status);
void		ft_dup2(int *fd1, int fd2, t_pip *x);
void		sacrificechild(t_pip *x, char **envp, int flag, char *args);

#endif