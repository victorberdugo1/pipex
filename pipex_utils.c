/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:27:21 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/24 08:49:47 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ************************************************************************** */
/* Displays an error message for an incorrect number of arguments and         */
/* provides the correct usage format. Terminates the program with an exit     */
/* status of 0 after printing the message to the appropriate file descriptors.*/
/* ************************************************************************** */
void	handle_invalid_argument_count(void)
{
	ft_putstr_fd("Error: Incorrect number of arguments\n", 2);
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 1);
	exit(0);
}

/* ************************************************************************** */
/* Prints an error message indicating an execution failure using perror,      */
/* which provides a description of the error. Terminates the program with     */
/* an exit status of -1.                                                      */
/* ************************************************************************** */
void	handle_execution_error(void)
{
	perror("Execution Error");
	exit(-1);
}

/* ************************************************************************** */
/* Frees each string in a dynamically allocated array of strings and          */
/* sets their pointers to NULL. Once all strings are deallocated, it frees    */
/* the array itself. Handles null input by returning early without action.    */
/* ************************************************************************** */
void	deallocate_string_array(char **array)
{
	int	index;

	if (array == NULL)
		return ;
	index = 0;
	while (array[index])
	{
		free(array[index]);
		array[index] = NULL;
		index++;
	}
	free(array);
}

/* ************************************************************************** */
/* Searches for the full path of a command by checking each directory listed  */
/* in the PATH environment variable. Joins each directory with the command    */
/* and checks if the resulting path is accessible and executable. Frees all   */
/* allocated memory and returns the full command path if found, or NULL if    */
/* the command is not found in any PATH directory.                            */
/* ************************************************************************** */
char	*find_command_path(char *command, char **env)
{
	int		i;
	char	*path_prefix;
	char	**all_paths;
	char	*complete_command_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
	all_paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		path_prefix = ft_strjoin(all_paths[i], "/");
		complete_command_path = ft_strjoin(path_prefix, command);
		free(path_prefix);
		if (access(complete_command_path, F_OK | X_OK) == 0)
		{
			deallocate_string_array(all_paths);
			return (complete_command_path);
		}
		free(complete_command_path);
		i++;
	}
	deallocate_string_array(all_paths);
	return (NULL);
}
