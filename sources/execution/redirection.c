/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:58:05 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/31 16:58:24 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->i[++i])
	{
		cmd->fd_i[i] = open(cmd->i[i], O_RDONLY);
		if (cmd->fd_i[i] == -1)
		{
			perror("error - could not open input file");
			return (0);
		}
		if (access(cmd->i[i], R_OK) != 0)
		{
			perror("error - can not read input file");
			return (0);
		}
	}
	dup2(cmd->fd_i[i - 1], STDIN_FILENO);
	i = -1;
	while (cmd->i[++i])
		close(cmd->fd_i[i]);
	return (1);
}

int	redirect_output(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->out[++i])
	{
		if (cmd->out[i] == 1)
			cmd->fd_o[i] = open(cmd->o[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (cmd->out[i] == 2)
			cmd->fd_o[i] = open(cmd->o[i], O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (cmd->fd_o[i] == -1)
		{
			perror ("error - could not open output file");
			return (0);
		}
		if (access(cmd->o[i], W_OK) != 0)
		{
			perror("error - can not write to output file");
			return (0);
		}
	}
	dup2(cmd->fd_o[i - 1], STDOUT_FILENO);
	i = -1;
	while (cmd->out[++i])
		close(cmd->fd_o[i]);
	return (1);
}

int	redirect_io(t_cmd *cmd)
{
	int	i;

	if (redirect_input(cmd) == 0)
		return (0);
	if (redirect_output(cmd) == 0)
		return (0);
	return (1);
}

void	reverse_redirection(t_cmd *cmd, int in, int out)
{
	if (cmd->i[0] != NULL)
		dup2(in, STDIN_FILENO);
	if (cmd->o[0] != NULL)
		dup2(out, STDOUT_FILENO);
	if (cmd->id == 0 & cmd->data->nr_cmds > 1)
		dup2(out, STDOUT_FILENO);
	else if (cmd->id == cmd->data->nr_cmds && cmd->data->nr_cmds > 1)
		dup2(in, STDIN_FILENO);
	else if (cmd->data->nr_cmds > 1)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
	}
	close(in);
	close(out);
}
