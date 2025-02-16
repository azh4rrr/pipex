/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:46:31 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/02/16 22:07:28 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	free_split(char **split)
{
	while (*split)
	{
		free(*split);
		split++;
	}
	free(split);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**set_path(t_pipe *pi)
{
	int		i;
	char	**path;

	i = 0;
	while ((pi->env)[i])
	{
		if (ft_strncmp((pi->env)[i], "PATH=", 5) == 0)
		{
			path = ft_split((pi->env)[i] + 5, ':');
			if (!path)
				ft_error("error spliting", NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	access_check(char *path, t_pipe *pi, int num)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (num == 1)
	{
		tmp = ft_strjoin(tmp, pi->cmd1_flags[0]);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			pi->cmd1 = ft_strdup(tmp);
			return (1);
		}
	}
	else if (num == 2)
	{
		tmp = ft_strjoin(tmp, pi->cmd2_flags[0]);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			pi->cmd2 = ft_strdup(tmp);
			return (1);
		}
	}
	return (0);
}

void	set_full_path(t_pipe *pi, int num)
{
	char	**path;
	int		i;
	int		check;

	check = 0;
	path = set_path(pi);
	if (!path)
		ft_error("Error: PATH environment variable not found\n", NULL);
	i = 0;
	while (path[i] && check == 0)
	{
		if (num == 1)
			check = access_check(path[i], pi, num);
		else if (num == 2)
			check = access_check(path[i], pi, num);
		i++;
	}
	if (!check && num == 1)
		return (ft_error("Command not found", pi->cmd1_flags[0]));
	else if (!check && num == 2)
		ft_error("Command not found", pi->cmd2_flags[0]);
}
