/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:32:53 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/31 16:58:41 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_up(t_data *data)
{
	int	i;

	if (data->nr_cmds > 1)
	{
		close_all_except_two(data, -1);
		i = -1;
		while (++i < data->nr_cmds)
		{
			data->pipe_fd[i][0] = 0;
			data->pipe_fd[i][1] = 0;
		}
	}
	i = -1;
	while ((++i < data->nr_cmds) && data->process_id[i])
	{
		waitpid(data->process_id[i], NULL, 0);
		data->process_id[i] = 0;
	}
}

int	init_commands(t_data *data, char *command_in)
{
	int		i;
	char	**commands;

	commands = ft_split(command_in, '*');
	i = 0;
	while (commands[i])
		i++;
	data->nr_cmds = i;
	data->cmd = malloc(sizeof(t_cmd) * data->nr_cmds);
	if (!data->cmd)
	{
		perror("malloc failed");
		return (0);
	}
	printf("check\n");
	i = -1;
	while (++i < data->nr_cmds)
	{
		data->cmd[i].params = ft_split(commands[i], ' ');
		data->cmd[i].o[0] = NULL;
		data->cmd[i].i[0] = NULL;
		data->cmd[i].out[0] = 0;
		data->cmd[i].id = i;
		data->cmd[i].data = data;
		data->process_id[i] = 0;
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*command_in;
	t_data	data;
	int		i;
	int		status;

	init_envp(&data, envp);
	// not sure to protect with if -1, exit
	if (argc > 1)
	{
		ft_printf("Expected usage: ./minishell");
		exit (127);
	}
	argv = NULL;
	while (1)
	{
		command_in = readline("Our_minishell:~% ");
		add_history(command_in);
		// lexer + parser
		init_commands(&data, command_in);
		// not sure to protect with if -1, exit
		status = 1;
		if (data.nr_cmds > 1)
			status = init_pipes(&data);
		if (status)
		{
			i = -1;
			while (++i < data.nr_cmds)
			{
				if (!exec_prefork_builtins(&data.cmd[i]))
					fork_function(&data.cmd[i]);
				// not sure to protect with if -1, exit
			}
		}
		finish_up(&data);
		free(command_in);
		command_in = NULL;
	//	exit (0);
	}
}
