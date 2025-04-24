/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:46:31 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/04/24 19:04:17 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
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
				ft_error("error splitting");
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	access_check(char *path, t_pipe *pi, int num)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	tmp2 = NULL;
	if (!tmp)
		return (0);
	if (num == 1)
		tmp2 = ft_strjoin(tmp, pi->cmd1_flags[0]);
	else if (num == 2)
		tmp2 = ft_strjoin(tmp, pi->cmd2_flags[0]);
	free(tmp);
	if (!tmp2)
		return (0);
	if (access(tmp2, F_OK | X_OK) == 0)
	{
		if (num == 1)
			pi->cmd1 = ft_strdup(tmp2);
		else if (num == 2)
			pi->cmd2 = ft_strdup(tmp2);
		free(tmp2);
		return (1);
	}
	free(tmp2);
	return (0);
}

static int	check_absolute_path(t_pipe *pi, int num)
{
	char	*cmd;

	cmd = (num == 1) ? pi->cmd1_flags[0] : pi->cmd2_flags[0];
	if (!cmd)
		return (0);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			if (num == 1)
				pi->cmd1 = ft_strdup(cmd);
			else if (num == 2)
				pi->cmd2 = ft_strdup(cmd);
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

	check = check_absolute_path(pi, num);
	if (check)
		return ;
	path = set_path(pi);
	if (!path)
		return (cleanup_pipex(pi),
			ft_error("Error: PATH environment variable not found"));
	i = -1;
	while (path[++i] && check == 0)
		if (num == 1 || num == 2)
			check = access_check(path[i], pi, num);
	free_split(path);
	if (!check || !pi->cmd1_flags[0] || !pi->cmd2_flags[0])
	{
		if (num == 1)
			print_error(pi->cmd1_flags[0]);
		else if (num == 2)
			print_error(pi->cmd2_flags[0]);
		cleanup_pipex(pi);
		exit(1);
	}
}
