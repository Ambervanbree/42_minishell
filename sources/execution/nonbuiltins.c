/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:30:26 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/03 10:15:31 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execve_function(t_data *data)
{
	if (execve(data->params[0], data->params, data->envp) == -1)
	{
		//some kind of free function
		perror("error - could not execute command");
		return (0);
	}
	return (1);
}

int	cmd_right(t_data *data)
{
	close_all_except(data, data->nr_pipes - 1, 0);
	dup2(data->pipe_fd[data->nr_pipes - 1][0], STDIN_FILENO);
	close(data->pipe_fd[data->nr_pipes - 1][0]);
	if (data->output_file != NULL)
		if (redirect_output(data) == 0)
			return (0);
	if (execve_function(data) == 0)
		return (0);
	return (1);
}

int	cmd_middle(int i, t_data *data)
{
	close_all_except_two(data, i - 1);
	dup2(data->pipe_fd[i - 1][0], STDIN_FILENO);
	close(data->pipe_fd[i - 1][0]);
	dup2(data->pipe_fd[i][1], STDOUT_FILENO);
	close(data->pipe_fd[i][1]);
	if (execve_function(data) == 0)
		return (0);
	return (1);
}

int	cmd_left(t_data *data)
{
	if (data->input_file != NULL)
		if (redirect_input(data) == 0)
			return (0);
	if (data->output_file != NULL)
		if (redirect_output(data) == 0)
			return (0);
	if (data->nr_cmds > 1)
	{
		close_all_except(data, 0, 1);
		dup2(data->pipe_fd[0][1], STDOUT_FILENO);
		close(data->pipe_fd[0][1]);
	}
	if (execve_function(data) == 0)
		return (0);
	return (1);
}

int	execute_non_builtin(int process, t_data *data)
{
	if (process == 0)
	{
		if (cmd_left(data) == 0)
			return (0);
	}
	else if (process == data->nr_cmds - 1)
	{
		if (cmd_right(data) == 0)
			return (0);
	}
	else
	{
		if (cmd_middle(process, data) == 0)
			return (0);
	}
	return (1);
}
