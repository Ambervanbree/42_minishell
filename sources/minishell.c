/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:32:53 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/27 13:28:01 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	i = -1;
	while (++i < data->nr_cmds)
	{
		data->cmd[i].params = ft_split(commands[i], ' ');
		data->cmd[i].o_file[0] = NULL;
		data->cmd[i].i_file[0] = NULL;
		data->cmd[i].out[0] = 0;
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
		status = 0;
		i = -1;
		while (++i < data.nr_cmds)
		{
			printf("Begin executing %s\n", data.cmd[i].params[0]);
			if (!exec_prefork_builtins(&data.cmd[i]))
				if (init_pipes(&data))
					fork_function(&data.cmd[i]);
			// not sure to protect with if -1, exit
		}
		free(command_in);
		command_in = NULL;
	}
}
