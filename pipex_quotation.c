/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:33:19 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/04/24 18:42:21 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	single_quote(const char *s, size_t *i, size_t *start)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		(*start)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
	else if (s[*i] == '\"')
	{
		(*i)++;
		(*start)++;
		while (s[*i] && s[*i] != '\"')
			(*i)++;
	}
}

int	ft_strchr(char c, char s)
{
	if (c == s)
		return (1);
	return (0);
}

void	file_check(char *file, t_pipe *pi)
{
	if (access(file, F_OK))
	{
		write(2, "pipex: ", 7);
		write(2, file, ft_strlen(file));
		write(2, ": No such file or directory\n", 28);
		cleanup_pipex(pi);
		exit(1);
	}
	if (access(file, R_OK))
	{
		write(2, "pipex: ", 7);
		write(2, file, ft_strlen(file));
		write(2, ": Permission denied\n", 20);
		cleanup_pipex(pi);
		exit(1);
	}
}

void	print_error(char *str)
{
	if (!str)
		return ;
	write(2, "pipex: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
}