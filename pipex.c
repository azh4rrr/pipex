/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:29:24 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/02/16 23:51:36 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	ft_free(char *c)
{
	if (c)
		free(c);
	return ;
}

void	execute(t_pipe *pi, int num)
{
	if (num == 1)
	{
		close(pi->fd[0]);
		dup2(pi->fd_in, STDIN_FILENO);
		dup2(pi->fd[1], STDOUT_FILENO);
		close(pi->fd_in);
		close(pi->fd[1]);
		close(pi->fd_out);
		execve(pi->cmd1, pi->cmd1_flags, pi->env);
		cleanup_pipex(pi);
		exit(1);
	}
	else if (num == 2)
	{
		close(pi->fd[1]);
		dup2(pi->fd[0], STDIN_FILENO);
		dup2(pi->fd_out, STDOUT_FILENO);
		close(pi->fd[0]);
		close(pi->fd_out);
		close(pi->fd_in);
		execve(pi->cmd2, pi->cmd2_flags, pi->env);
		cleanup_pipex(pi);
		exit(1);
	}
}

void	ft_pipex(t_pipe *pi)
{
	pid_t	pid;
	pid_t	pid2;

	if (pipe(pi->fd) < 0)
		ft_error("Pipe faild");
	pid = fork();
	if (pid < 0)
		return (close(pi->fd[0]), close(pi->fd[1]), ft_error("Fork faild"));
	if (pid == 0)
	{
		set_full_path(pi, 1);
		execute(pi, 1);
	}
	pid2 = fork();
	if (pid2 < 0)
		ft_error("Fork faild");
	if (pid2 == 0)
	{
		set_full_path(pi, 2);
		execute(pi, 2);
	}
	ft_close(pi);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pi;

	if (ac == 5)
	{
		pi.cmd1 = NULL;
		pi.cmd2 = NULL;
		pi.cmd1_flags = ft_split(av[2], ' ');
		pi.cmd2_flags = ft_split(av[3], ' ');
		pi.env = env;
		pi.fd_in = open(av[1], O_RDONLY);
		pi.fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pi.fd_in < 0)
			return (cleanup_pipex(&pi) ,ft_error("No such file or directory"), 1);
		if (pi.fd_out < 0)
			return(close(pi.fd_in), cleanup_pipex(&pi), ft_error("Error creating file"), 1);
		ft_pipex(&pi);
		free_split(pi.cmd1_flags);
		free_split(pi.cmd2_flags);
	}
	else
		ft_error("Error: Wrong number of arguments");
}

