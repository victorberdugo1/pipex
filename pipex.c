/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:12:50 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/18 13:57:49 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command(char *cmd, char **env)
{
	char	**command_array;
	char	*command_path;

	command_array = ft_split(cmd, ' ');
	command_path = extract_path(command_array[0], env);
	if (!command_path)
	{
		free_array(command_array);
		handle_error();
	}
	if (execve(command_path, command_array, env) == -1)
	{
		free_array(command_array);
		free(command_path);
		handle_error();
	}
	free_array(command_array);
	free(command_path);
}

static void	child_process(int *pipe_ends, char **arguments, char **env)
{
	int	file_descriptor;

	file_descriptor = open(arguments[1], O_RDONLY);
	if (file_descriptor == -1)
		handle_error();
	dup2(file_descriptor, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(pipe_ends[0]);
	execute_command(arguments[2], env);
}

static void	parent_process(int *pipe_ends, char **arguments, char **env)
{
	int	file_descriptor;

	file_descriptor = open(arguments[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_descriptor == -1)
		handle_error();
	dup2(pipe_ends[0], STDIN_FILENO);
	dup2(file_descriptor, STDOUT_FILENO);
	close(pipe_ends[1]);
	execute_command(arguments[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		pipe_ends[2];
	pid_t	process_id;

	if (argc != 5)
		handle_exit();
	else
	{
		if (pipe(pipe_ends) == -1)
			handle_error();
		process_id = fork();
		if (process_id == -1)
			handle_error();
		if (!process_id)
			child_process(pipe_ends, argv, env);
		waitpid(process_id, NULL, 0);
		parent_process(pipe_ends, argv, env);
	}
}
