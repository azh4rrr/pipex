/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:29:24 by azmakhlo          #+#    #+#             */
/*   Updated: 2025/04/24 18:24:45 by codespace        ###   ########.fr       */
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
}

void	execute_first_cmd(t_pipe *pi)
{
	if (access(pi->av[1], F_OK) != 0)
	{
		write(2, pi->av[1], ft_strlen(pi->av[1]));
		write(2, " : No such file or directory\n", 29);
		cleanup_pipex(pi);
		exit(1);
	}
	else if (access(pi->av[1], R_OK) != 0)
	{
		write(2, pi->av[1], ft_strlen(pi->av[1]));
		write(2, " : Permission denied\n", 21);
		cleanup_pipex(pi);
		exit(1);
	}
	else
		pi->fd_in = open(pi->av[1], O_RDONLY);
	close(pi->fd[0]);
	dup2(pi->fd_in, STDIN_FILENO);
	dup2(pi->fd[1], STDOUT_FILENO);
	close(pi->fd_in);
	close(pi->fd[1]);
	execve(pi->cmd1, pi->cmd1_flags, pi->env);
	cleanup_pipex(pi);
	exit(1);
}

void	execute_second_cmd(t_pipe *pi)
{
	if (!access(pi->av[4], F_OK) && access(pi->av[4], W_OK))
	{
		write(2, pi->av[4], ft_strlen(pi->av[4]));
		write(2, " : Permission denied\n", 21);
		cleanup_pipex(pi);
		exit(1);
	}
	pi->fd_out = open(pi->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pi->fd_out < 0)
		return (cleanup_pipex(pi), ft_error("Error creating file"));
	close(pi->fd[1]);
	dup2(pi->fd[0], STDIN_FILENO);
	dup2(pi->fd_out, STDOUT_FILENO);
	close(pi->fd[0]);
	close(pi->fd_out);
	execve(pi->cmd2, pi->cmd2_flags, pi->env);
	cleanup_pipex(pi);
	exit(1);
}

void	execute(t_pipe *pi, int num)
{
	if (num == 1)
		execute_first_cmd(pi);
	else if (num == 2)
		execute_second_cmd(pi);
}

void create_processes(t_pipe *pi, pid_t *pid1, pid_t *pid2)
{
    if (pipe(pi->fd) < 0)
        ft_error("Pipe failed");
    
    *pid1 = fork();
    if (*pid1 < 0)
        return (ft_close(pi), ft_error("Fork failed"));
    if (*pid1 == 0)
    {
        if (access(pi->av[1], F_OK | R_OK) == 0)
            set_full_path(pi, 1);
        execute(pi, 1);
    }
    
    *pid2 = fork();
    if (*pid2 < 0)
        ft_error("Fork failed");
    if (*pid2 == 0)
    {
        set_full_path(pi, 2);
        execute(pi, 2);
    }
}

void ft_pipex(t_pipe *pi)
{
    pid_t pid1;
    pid_t pid2;
    int status;

    create_processes(pi, &pid1, &pid2);
    
    ft_close(pi);
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    cleanup_pipex(pi);
    exit(WEXITSTATUS(status));
}

void	init_pipex(t_pipe *pi, char **av, char **env)
{
	pi->cmd1 = NULL;
	pi->cmd2 = NULL;
	pi->cmd1_flags = ft_split(av[2], ' ');
	pi->cmd2_flags = ft_split(av[3], ' ');
	pi->env = env;
	pi->av = av;
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pi;

	if (ac == 5)
	{
		init_pipex(&pi, av, env);
		ft_pipex(&pi);
		// cleanup_pipex(&pi);
	}
	else
		ft_error("Error: Wrong number of arguments");
	return (0);
}