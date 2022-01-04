/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:58:05 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/03 10:27:50 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_data *data)
{
	data->fd_in = open(data->input_file, O_RDONLY);
	if (data->fd_in == -1)
	{
		perror("error - could not open input file");
		return (0);
	}
	if (access(data->input_file, R_OK) != 0)
	{
		perror("error - can not read input file");
		return (0);
	}
	dup2(data->fd_in, STDIN_FILENO);
	close(data->fd_in);
	return (1);
}

int	redirect_output(t_data *data)
{
	data->fd_out = open(data->output_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->fd_out == -1)
	{
		perror ("error - could not open output file");
		return (0);
	}
	if (access(data->output_file, W_OK) != 0)
	{
		perror("error - can not write to output file");
		return (0);
	}
	dup2(data->fd_out, STDOUT_FILENO);
	close(data->fd_out);
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
