/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:12:50 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/24 08:46:35 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ************************************************************************** */
/* Executes a given command by first splitting the command into arguments,    */
/* then finding the full path of the executable using environment variables.  */
/* Manages memory for the command arguments and handles errors if execution   */
/* fails, freeing all allocated resources as needed.                          */
/* ************************************************************************** */
static void	run_command(char *command, char **env)
{
	char	**split_command;
	char	*command_full_path;

	split_command = ft_split(command, ' ');
	command_full_path = find_command_path(split_command[0], env);
	if (!command_full_path)
	{
		deallocate_string_array(split_command);
		handle_execution_error();
	}
	if (execve(command_full_path, split_command, env) == -1)
	{
		deallocate_string_array(split_command);
		free(command_full_path);
		handle_execution_error();
	}
	deallocate_string_array(split_command);
	free(command_full_path);
}

/* ************************************************************************** */
/* Handles the child process by opening the input file and redirecting        */
/* its content to the standard input. Redirects the pipe output to standard   */
/* output, closes the unused pipe end, and executes the specified command.    */
/* Manages file and pipe descriptors and handles errors during execution.     */
/* ************************************************************************** */
static void	process_child(int *pipe_fds, char **arguments, char **env)
{
	int	input_fd;

	input_fd = open(arguments[1], O_RDONLY);
	if (input_fd == -1)
		handle_execution_error();
	dup2(input_fd, STDIN_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[0]);
	run_command(arguments[2], env);
}

/* ************************************************************************** */
/* Handles the parent process by opening the output file and redirecting      */
/* the pipe input to the standard input. Redirects standard output to the     */
/* specified output file, closes the unused pipe end, and executes the        */
/* second command. Manages file and pipe descriptors and handles errors       */
/* during execution.                                                          */
/* ************************************************************************** */
static void	process_parent(int *pipe_fds, char **arguments, char **env)
{
	int	output_fd;

	output_fd = open(arguments[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_fd == -1)
		handle_execution_error();
	dup2(pipe_fds[0], STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(pipe_fds[1]);
	run_command(arguments[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		pipe_fds[2];
	pid_t	process_pid;

	if (argc != 5)
		handle_invalid_argument_count();
	else
	{
		if (pipe(pipe_fds) == -1)
			handle_execution_error();
		process_pid = fork();
		if (process_pid == -1)
			handle_execution_error();
		if (process_pid == 0)
			process_child(pipe_fds, argv, env);
		waitpid(process_pid, NULL, 0);
		process_parent(pipe_fds, argv, env);
	}
}
