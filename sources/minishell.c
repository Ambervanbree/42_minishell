/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:32:53 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/24 13:22:08 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_nonbuiltins(t_cmd *cmd)
{
	if (execve(cmd->params[0], cmd->params, NULL) == -1)
	{
		//some kind of free function
		perror("error - execution fail");
		exit (1);
	}
	exit (0);
}

int	fork_function(t_cmd *cmd)
{
	cmd->data->process_id[cmd->id] = fork();
	if (cmd->data->process_id[cmd->id] == -1)
	{
		perror("error - fork failed");
		return (-1);
	}
	else if (cmd->data->process_id[cmd->id] == 0)
	{
		if (redirect_or_pipe(cmd) == 0)
			return (-1);
		if (exec_builtins(cmd) == 1)
			return (1);
		// else if (exec_nonbuiltins(cmd) == 1)
		// 	return (2);
	}
	else
		waitpid(cmd->data->process_id[cmd->id], NULL, 0);
	return (1);
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
	data->nr_pipes = i - 1;
	data->cmd = malloc(sizeof(t_cmd) * data->nr_cmds);
	if (!data->cmd)
	{
		perror("malloc failed");
		return (0);
	}
	i = -1;
	while (++i < data->nr_cmds)
	{
		data->cmd[i].params = ft_split(commands[i], ' ');
		data->cmd[i].o_file = NULL;
		data->cmd[i].i_file = NULL;
		data->cmd[i].id = i;
		data->cmd[i].data = data;
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*command_in;
	t_data	data;
	int		i;

	argc = 0;
	init_envp(&data, envp);
	// not sure to protect with if -1, exit
	argv = NULL;
	ft_printf("Our_minishell%% ");
	command_in = get_next_line(STDIN_FILENO);
	i = 0;
	while (!(command_in[i] == '\n' && command_in[i] != '\0'))
		i++;
	command_in[i] = '\0';
	while (command_in != 0)
	{
		if (command_in)
		{
			// lexer + parser
			init_commands(&data, command_in);
			// not sure to protect with if -1, exit
			i = -1;
			while (++i < data.nr_cmds)
			{
				if (exec_prefork_builtins(&data.cmd[i])	== 0)
					fork_function(&data.cmd[i]);
				// not sure to protect with if -1, exit
			}
		}
		free(command_in);
		command_in = NULL;
		ft_printf("Our_minishell%% ");
		command_in = get_next_line(STDIN_FILENO);
		i = 0;
		while (!(command_in[i] == '\n' && command_in[i] != '\0'))
			i++;
		command_in[i] = '\0';
	}
}