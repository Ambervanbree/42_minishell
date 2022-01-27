/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:03:37 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/27 15:33:59 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_except(t_data *data, int pipe, int index, char *cmd)
{
	int	i;

	i = -1;
	while (++i < (data->nr_cmds - 1))
	{
		if (i != pipe)
		{
			close(data->pipe_fd[i][0]);
			printf("%s Closes: %d, %d\n", cmd, i, 0);
			close(data->pipe_fd[i][1]);
			printf("%s Closes: %d, %d\n", cmd, i, 1);
		}
		else
		{
			if (index == 0)
			{
				close(data->pipe_fd[i][1]);
				printf("%s Closes: %d, %d\n", cmd, i, 1);
			}
			else
			{
				close(data->pipe_fd[i][0]);
				printf("%s Closes: %d, %d\n", cmd, i, 0);
			}
		}
	}
}

void	close_all_except_two(t_data *data, int pipe)
{
	int	i;

	i = 0;
	while (i < (data->nr_cmds - 1))
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

int	pipe_function(t_cmd *cmd)
{
	if (cmd->id == 0)
	{
//		printf("%s close all except %d, %d\n", cmd->params[0], 0, 1);
		close_all_except(cmd->data, 0, 1, cmd->params[0]);
		//if (cmd->o_file[0] == NULL)
		dup2(cmd->data->pipe_fd[0][1], STDOUT_FILENO);
		close(cmd->data->pipe_fd[0][1]);
	}
	else if (cmd->id == (cmd->data->nr_cmds - 1))
	{
//		printf("%s close all except %d, %d\n", cmd->params[0], cmd->id - 1, 0);
		close_all_except(cmd->data, cmd->id - 1, 0, cmd->params[0]);
		//if (cmd->i_file[0] == NULL)
		dup2(cmd->data->pipe_fd[cmd->id - 1][0], STDIN_FILENO);
		close(cmd->data->pipe_fd[cmd->id - 1][0]);
	}
	else
	{
		close_all_except_two(cmd->data, cmd->id - 1);
		if (cmd->i_file[0] == NULL)
			dup2(cmd->data->pipe_fd[cmd->id - 1][0], STDIN_FILENO);
		if (cmd->o_file[0] == NULL)
			dup2(cmd->data->pipe_fd[cmd->id][1], STDOUT_FILENO);
		close(cmd->data->pipe_fd[cmd->id - 1][0]);
		close(cmd->data->pipe_fd[cmd->id][1]);
	}
	return (1);
}

int	init_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (data->nr_cmds - 1))
	{
		printf("pipe %d is made\n", i);
		if (pipe(data->pipe_fd[i]) == -1)
		{
			perror("error - pipe failed");
			return (-1);
		}
	}
	return (1);
}
