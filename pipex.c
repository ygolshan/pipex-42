/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:51:44 by ygolshan          #+#    #+#             */
/*   Updated: 2023/12/26 15:57:48 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	redirecting_child0(t_file *file)
{
	if (close(file->fd[READ_END]) == -1)
	{
		perror("Error: ");
		return (-1);
	}
	if (dup2(file->fd[WRITE_END], STDOUT_FILENO) == -1)
	{
		perror("Error: ");
		return (-1);
	}
	if (close(file->fd[WRITE_END]) == -1)
	{
		perror("Error: ");
		return (-1);
	}
	return (0);
}

int	redirecting_child(t_file *file, char *cmd, char **envp)
{
	if (close(file->out) == -1)
	{
		perror("Error: ");
		return (-1);
	}
	if (dup2(file->in, STDIN_FILENO) == -1)
	{
		perror("Error: ");
		return (-1);
	}
	if (close(file->in) == -1)
	{
		perror("Error: ");
		return (-1);
	}
	redirecting_child0(file);
	cmd_exec(cmd, envp);
	return (0);
}

int	redirecting_child3(t_file *file, int error)
{
	if (dup2(file->fd[READ_END], STDIN_FILENO) == -1)
	{
		error = 1;
		perror("Error: ");
	}
	if (close(file->fd[READ_END]) == -1)
	{
		error = 1;
		perror("Error: ");
	}
	if (dup2(file->out, STDOUT_FILENO) == -1)
	{
		error = 1;
		perror("Error: ");
	}
	if (close(file->out) == -1)
	{
		error = 1;
		perror("Error: ");
	}
	return (error);
}

int	redirecting_parent(t_file *file, char *cmd, char **envp)
{
	int	error;

	error = 0;
	if (close(file->in) == -1)
	{
		error = 1;
		perror("Error: ");
	}
	if (close(file->fd[WRITE_END]) == -1)
	{
		error = 1;
		perror("Error: ");
	}
	error = redirecting_child3(file, error);
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}

int	main(int argc, char **argv, char **envp)
{
	t_file	file;
	pid_t	pid;

	if (argc != 5)
	{
		ft_putendl_fd("the number of parameters is not correct", 2);
		return (1);
	}
	open_files(argv, &file);
	if (pipe(file.fd) == -1)
		exec_failed("the pipe was not built");
	pid = fork();
	if (pid == -1)
		exec_failed("fork failed");
	if (pid == 0)
	{
		if (redirecting_child(&file, argv[2], envp) != 0)
			exec_failed("childprocess failed");
	}
	if (redirecting_parent(&file, argv[3], envp) != 0)
		exec_failed("parentprocess failed");
}
