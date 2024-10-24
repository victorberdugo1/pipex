/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:18:55 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/24 08:40:22 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>

void	handle_invalid_argument_count(void);
void	handle_execution_error(void);
void	deallocate_string_array(char **array);
char	*find_command_path(char *command, char **env);

#endif
