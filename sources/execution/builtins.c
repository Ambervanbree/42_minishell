/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                           s                     +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:19:50 by avan-bre          #+#    #+#             */
/*   Updated: 2021/12/22 11:19:51 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin2(t_data *data)
{
	if (ft_strncmp(data->params[0], "unset\0", 6) == 0)
	{
		ft_unset(data);
		return (1);
	}
	else if (ft_strncmp(data->params[0], "env\0", 4) == 0)
	{
		ft_env(data);
		return (1);
	}
// 	else if (ft_strncmp(data->params[0], "exit\0", 5) == 0)
// 	{
// 		ft_exit(data);
// 		return (1);
// 	}
 	return (0);
}

int	execute_builtin(t_data *data)
{
	if (ft_strncmp(data->params[0], "echo\0", 5) == 0)
	{
		ft_echo(data);
		return (1);
	}
	else if (ft_strncmp(data->params[0], "cd\0", 3) == 0)
	{
		ft_cd(data);
	 	return (1);
	}
	else if (ft_strncmp(data->params[0], "pwd\0", 4) == 0)
	{
		ft_pwd(data);
		return (1);
	}
	else if (ft_strncmp(data->params[0], "export\0", 7) == 0)
	{
		ft_export(data->params[1], data);
		return (1);
	}
	else
		if (execute_builtin2(data))
			return (1);
	return (0);
}