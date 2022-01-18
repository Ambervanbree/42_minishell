/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:58:05 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/17 10:14:01 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_data *data)
{
	data->fd_i = open(data->i_file, O_RDONLY);
	if (data->fd_i == -1)
	{
		perror("error - could not open input file");
		return (0);
	}
	if (access(data->i_file, R_OK) != 0)
	{
		perror("error - can not read input file");
		return (0);
	}
	dup2(data->fd_i, STDIN_FILENO);
	close(data->fd_i);
	return (1);
}

int	redirect_output(t_data *data)
{
	data->fd_o = open(data->o_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->fd_o == -1)
	{
		perror ("error - could not open output file");
		return (0);
	}
	if (access(data->o_file, W_OK) != 0)
	{
		perror("error - can not write to output file");
		return (0);
	}
	dup2(data->fd_o, STDOUT_FILENO);
	close(data->fd_o);
	return (1);
}

void	close_all_except(t_data *data, int pipe, int index)
{
	int	i;

	i = 0;
	while (i < data->nr_pipes)
	{
		if (i != pipe)
		{
			close(data->pipe_fd[i][0]);
			close(data->pipe_fd[i][1]);
		}
		else
		{
			if (index == 0)
				close(data->pipe_fd[i][1]);
			else
				close(data->pipe_fd[i][0]);
		}
		i++;
	}
}

void	close_all_except_two(t_data *data, int pipe)
{
	int	i;

	i = 0;
	while (i < data->nr_pipes)
	{
		if (i == pipe)
		{
			close(data->pipe_fd[i][1]);
			i++;
			close(data->pipe_fd[i][0]);
		}
		else
		{
			close(data->pipe_fd[i][0]);
			close(data->pipe_fd[i][1]);
		}
		i++;
	}
}

int	redirect_or_pipe(t_data *data)
{
	if (data->i_file != NULL)
		if (redirect_input(data) == 0)
			return (0);
	if (data->o_file != NULL)
		if (redirect_output(data) == 0)
			return (0);
	if (data->cmd_nr == 0 & data->nr_cmds > 1)
	{
		close_all_except(data, 0, 1);
		dup2(data->pipe_fd[0][1], STDOUT_FILENO);
		close(data->pipe_fd[0][1]);
	}
	else if (data->cmd_nr == data->nr_cmds && data->nr_cmds > 1)
	{
		close_all_except(data, data->nr_pipes - 1, 0);
		dup2(data->pipe_fd[data->nr_pipes - 1][0], STDIN_FILENO);
		close(data->pipe_fd[data->nr_pipes - 1][0]);
	}
	else if (data->nr_cmds > 1)
	{
		close_all_except_two(data, data->cmd_nr - 1);
		dup2(data->pipe_fd[data->cmd_nr - 1][0], STDIN_FILENO);
		close(data->pipe_fd[data->cmd_nr - 1][0]);
		dup2(data->pipe_fd[data->cmd_nr][1], STDOUT_FILENO);
		close(data->pipe_fd[data->cmd_nr][1]);
	}
	return (1);
}
