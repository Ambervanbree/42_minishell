/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:58:05 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/19 16:58:41 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd *cmd)
{
	cmd->fd_i = open(cmd->i_file, O_RDONLY);
	if (cmd->fd_i == -1)
	{
		perror("error - could not open input file");
		return (0);
	}
	if (access(cmd->i_file, R_OK) != 0)
	{
		perror("error - can not read input file");
		return (0);
	}
	dup2(cmd->fd_i, STDIN_FILENO);
	close(cmd->fd_i);
	return (1);
}

int	redirect_output(t_cmd *cmd)
{
	cmd->fd_o = open(cmd->o_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (cmd->fd_o == -1)
	{
		perror ("error - could not open output file");
		return (0);
	}
	if (access(cmd->o_file, W_OK) != 0)
	{
		perror("error - can not write to output file");
		return (0);
	}
	dup2(cmd->fd_o, STDOUT_FILENO);
	close(cmd->fd_o);
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

int	redirect_or_pipe(t_cmd *cmd)
{
	if (cmd->i_file != NULL)
		if (redirect_input(cmd) == 0)
			return (0);
	if (cmd->o_file != NULL)
		if (redirect_output(cmd) == 0)
			return (0);
	// if (cmd->id == 0 & cmd->data->nr_cmds > 1)
	// {
	// 	close_all_except(cmd->data, 0, 1);
	// 	dup2(cmd->data->pipe_fd[0][1], STDOUT_FILENO);
	// 	close(cmd->data->pipe_fd[0][1]);
	// }
	// else if (cmd->id == cmd->data->nr_cmds && cmd->data->nr_cmds > 1)
	// {
	// 	close_all_except(cmd->data, cmd->data->nr_pipes - 1, 0);
	// 	dup2(cmd->data->pipe_fd[cmd->data->nr_pipes - 1][0], STDIN_FILENO);
	// 	close(cmd->data->pipe_fd[cmd->data->nr_pipes - 1][0]);
	// }
	// else if (cmd->data->nr_cmds > 1)
	// {
	// 	close_all_except_two(cmd->data, cmd->id - 1);
	// 	dup2(cmd->data->pipe_fd[cmd->id - 1][0], STDIN_FILENO);
	// 	close(cmd->data->pipe_fd[cmd->id - 1][0]);
	// 	dup2(cmd->data->pipe_fd[cmd->id][1], STDOUT_FILENO);
	// 	close(cmd->data->pipe_fd[cmd->id][1]);
	// }
	return (1);
}
