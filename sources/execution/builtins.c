/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                           s                     +#+#+#+#+#+   +#+          */
/*   Created: 2021/12/22 11:19:50 by avan-bre          #+#    #+#             */
/*   Updated: 2021/12/22 11:19:51 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_data *data)
{
	if (ft_strncmp(data->params[0], "echo\0", 5) == 0)
	{
		ft_echo(data);
		return (1);
	}
	else if (ft_strncmp(data->params[0], "pwd\0", 4) == 0)
	{
		ft_pwd();
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

void	reverse_redirection(t_data *data, int in, int out)
{
	if (data->i_file != NULL)
		dup2(in, STDIN_FILENO);
	if (data->o_file != NULL)
		dup2(out, STDOUT_FILENO);
	if (data->cmd_nr == 0 & data->nr_cmds > 1)
		dup2(out, STDOUT_FILENO);
	else if (data->cmd_nr == data->nr_cmds && data->nr_cmds > 1)
		dup2(in, STDIN_FILENO);
	else if (data->nr_cmds > 1)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
	}
	close(in);
	close(out);
}

int	exec_prefork_builtins2(t_data *data, enum BI funct)
{
	int		current_stdin;
	int		current_stdout;

	current_stdin = dup(STDIN_FILENO);
	current_stdout = dup(STDOUT_FILENO);
	if (redirect_or_pipe(data) == 0)
	{
		close(current_stdin);
		close(current_stdout);
		return (-1);
	}
	if (funct == CD)
		ft_cd(data);
	else if (funct == EXPORT)
		ft_export(data);
	else if (funct == UNSET)
		ft_unset(data);
	reverse_redirection(data, current_stdin, current_stdout);
	return (1);
}

int	exec_prefork_builtins(t_data *data)
{
	enum BI	funct;

	funct = 0;
	if (ft_strncmp(data->params[0], "cd\0", 3) == 0)
		funct = CD;
	else if (ft_strncmp(data->params[0], "export\0", 7) == 0)
		funct = EXPORT;
	else if (ft_strncmp(data->params[0], "unset\0", 6) == 0)
		funct = UNSET;
	if (funct)
	{
		if (exec_prefork_builtins2(data, funct) == -1)
			return (-1);
		return (1);
	}
	return (0);
}
