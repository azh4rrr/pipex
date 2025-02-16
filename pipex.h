/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:03:21 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/02/16 23:48:49 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*cmd1;
	char	**cmd1_flags;
	char	*cmd2;
	char	**path;
	int		fd[2];
	char	**env;
	char	**cmd2_flags;
	int		fd_in;
	int		fd_out;
	int		error;
}			t_pipe;

void		ft_error(char *str);
void		cleanup_pipex(t_pipe *pi);
void		ft_close(t_pipe *pi);
void		free_split(char **split);
char		**ft_split(const char *s, char c);
void		ft_free(char *c);
int			ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		set_full_path(t_pipe *pi, int num);
#endif