/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:33:19 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/03/17 16:43:36 by azmakhlo         ###   ########.fr       */
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
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
}

int	ft_strchr(char c, char s)
{
	if (c == s)
		return (1);
	return (0);
}
