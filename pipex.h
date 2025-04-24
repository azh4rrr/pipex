/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:03:21 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/04/24 18:33:53 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	*cmd1;
	char	**cmd1_flags;
	char	*cmd2;
	char	**cmd2_flags;
	char	**path;
	char	**av;
	char	**env;
	int		fd[2];
	int		fd_in;
	int		fd_out;
}			t_pipe;

/* Error handling and cleanup */
void		ft_error(char *str);
void		cleanup_pipex(t_pipe *pi);
void		ft_close(t_pipe *pi);
void		print_error(char *str);
void		file_check(char *file, t_pipe *pi);
void		ft_free(char *c);

/* String utilities */
int			ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);

/* Split and quote handling */
char		**ft_split(const char *s, char c);
void		single_quote(const char *s, size_t *i, size_t *start);
int			ft_strchr(char c, char s);
void		free_split(char **split);

/* Command execution */
void		set_full_path(t_pipe *pi, int num);
void		execute(t_pipe *pi, int num);
void		ft_pipex(t_pipe *pi);
void		init_pipex(t_pipe *pi, char **av, char **env);

#endif