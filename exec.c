/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:51:52 by ygolshan          #+#    #+#             */
/*   Updated: 2023/03/24 20:49:25 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exec_failed(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	find_path(char **paths, char **cmd_args, char **envp)
{
	int		i;
	char	*match;
	char	*tmp_match;

	i = 0;
	while (paths && paths[i])
	{
		tmp_match = ft_strjoin(paths[i], "/");
		match = ft_strjoin(tmp_match, cmd_args[0]);
		free(tmp_match);
		if (access(match, F_OK) == 0)
			execve(match, cmd_args, envp);
		free(match);
		i++;
	}
	if (access(cmd_args[0], F_OK) == 0)
		execve(cmd_args[0], cmd_args, envp);
}

void	cmd_exec(char *cmd, char **envp)
{
	char	**paths;
	char	**cmd_args;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = NULL;
	if (envp[i])
		paths = ft_split(envp[i] + 6, ':');
	cmd_args = ft_split(cmd, ' ');
	find_path(paths, cmd_args, envp);
	free_split(paths);
	free_split(cmd_args);
	ft_putendl_fd("the correct path was not found\n", 2);
	exit(1);
}

void	open_files(char **argv, t_file *file)
{
	file->in = open(argv[1], O_RDONLY);
	if (file->in == -1)
	{
		ft_putendl_fd("there is a problem in opening the input file\n", 2);
		exit(1);
	}
	file->out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file->out == -1)
	{
		close(file->in);
		ft_putendl_fd("there is a problem in opening the output file\n", 2);
		exit(1);
	}
}
