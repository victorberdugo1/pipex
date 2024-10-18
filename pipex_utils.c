/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:27:21 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/18 13:58:12 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exit(void)
{
	ft_putstr_fd("Error: Incorrect number of arguments\n", 2);
	ft_putstr_fd("Please Input: ./pipex infile cmd1 cmd2 outfile\n", 1);
	exit(0);
}

void	handle_error(void)
{
	perror("Error");
	exit(-1);
}

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

char	*extract_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*full_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
	all_paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_array(all_paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(all_paths);
	return (NULL);
}
