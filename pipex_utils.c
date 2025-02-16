/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:46:31 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/02/16 23:49:12 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	free_split(char **split)
{

    int i;

    if (!split)
        return;
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
				ft_error("error spliting");
			return (path);
		}
		i++;
	}
	return (NULL);
}

int access_check(char *path, t_pipe *pi, int num) {
    char *tmp ;
    char *tmp2 = NULL;

	tmp2 = NULL;
	tmp = ft_strjoin(path, "/");
    if (!tmp) 
		return (0);
    if (num == 1) 
		tmp2 = ft_strjoin(tmp, pi->cmd1_flags[0]);
    else if (num == 2) 
		tmp2 = ft_strjoin(tmp, pi->cmd2_flags[0]);
    free(tmp); // Free "path/" after creating tmp2
    if (!tmp2) 
		return (0);
    tmp = tmp2;
    if (access(tmp, F_OK | X_OK) == 0) 
	{
        if (num == 1) 
			pi->cmd1 = ft_strdup(tmp);
        else if (num == 2) 
			pi->cmd2 = ft_strdup(tmp);
        free(tmp); // Free the joined path after duplication
        return (1);
    }
    free(tmp2); // Free if access fails
    return (0);
}

void set_full_path(t_pipe *pi, int num)
{
    char    **path;
    int     i;
    int     check;

    check = 0;
    path = set_path(pi);
    if (!path)
	{
		cleanup_pipex(pi);
        ft_error("Error: PATH environment variable not found\n");
	}
    i = 0;
    while (path[i] && check == 0)
    {
        if (num == 1)
            check = access_check(path[i], pi, num);
        else if (num == 2)
            check = access_check(path[i], pi, num);
        i++;
    }
    free_split(path);
    if (!check)
    {
        cleanup_pipex(pi);
        if (num == 1)
            ft_error("Command not found");
        else
            ft_error("Command not found");
    }
}

