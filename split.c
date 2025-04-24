/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:56:22 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/04/24 18:36:18 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s)
		return (NULL);
	if ((int)start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static void	handle_quotes(const char *s, size_t *i)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
	else if (s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\"')
			(*i)++;
	}
}

static size_t	counts(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			if (s[i] == '\'' || s[i] == '\"')
				handle_quotes(s, &i);
			count++;
		}
		i++;
	}
	return (count);
}

static char	**shorten(char **p, size_t x)
{
	while (x > 0)
		free(p[--x]);
	free(p);
	return (NULL);
}

static char	**shoten2(char **p, const char *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	x;

	i = 0;
	x = 0;
	while (s[i] && x < counts(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		single_quote(s, &i, &start);
		while (s[i] && ft_strchr(c, s[i]) == 0 && s[i] != '\'' && s[i] != '\"')
			i++;
		p[x++] = ft_substr(s, start, i - start);
		if (!p[x - 1])
			return (shorten(p, x));
	}
	p[x] = NULL;
	return (p);
}

char	**ft_split(const char *s, char c)
{
	size_t	count;
	char	**p;

	if (!s)
		return (NULL);
	count = counts(s, c);
	p = (char **)malloc(sizeof(char *) * (count + 1));
	if (!p)
		return (NULL);
	return (shoten2(p, s, c));
}