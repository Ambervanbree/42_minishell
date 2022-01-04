/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:02:21 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/03 10:18:56 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	execute_command(int process, t_data *data, char *command)
{
	data->params = ft_split(command, ' ');
	if (execute_builtin(data) == 1)
	 	return (1) ;
	else if (execute_non_builtin(process, data) == 1)
		return (2) ;
	else
		ft_putstr_fd("error - command not found\n", 2);
	// I would like to add the command here, but printf doesn't print to stderr...
	// and if you use ft_putstr_fd twice, it might mess up the order when there's multiple processes
	// solution: make ft_printf_fd, but that's a lot of work
	return (0);
}
