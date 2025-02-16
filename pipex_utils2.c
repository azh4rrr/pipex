/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:15:36 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/02/16 22:07:35 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		len_s;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc((sizeof(char) * len_s) + 1);
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = 0;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_close(t_pipe *pi)
{
	close(pi->fd[0]);
	close(pi->fd[1]);
	close(pi->fd_in);
	close(pi->fd_out);
}
