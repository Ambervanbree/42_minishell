/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:32:53 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/18 13:34:56 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_nonbuiltins(t_data *data)
{
	if (execve(data->params[0], data->params, data->envp) == -1)
	{
		//some kind of free function
		perror("error - execution fail");
		exit (1);
	}
	exit (0);
}

int	fork_function(t_data *data)
{
	data->process_id[data->cmd_nr] = fork();
	if (data->process_id[data->cmd_nr] == -1)
	{
		perror("error - fork failed");
		return (-1);
	}
	else if (data->process_id[data->cmd_nr] == 0)
	{
		if (redirect_or_pipe(data) == 0)
			return (-1);
		if (exec_builtins(data) == 1)
			return (1);
		else if (exec_nonbuiltins(data) == 1)
			return (2);
	}
	else
		waitpid(data->process_id[data->cmd_nr], NULL, 0);
	return (1);
}

void	free_envp(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
	{
		if (data->envp[i] != NULL)
		{
			printf("free (infunct) %p\n", data->envp[i]);
			free(data->envp[i]);
			data->envp[i] = NULL;
		}
	}
	if (data->envp != NULL)
	{
		printf("free (infunct) %p\n", data->envp);
		free(data->envp);
		data->envp = NULL;
	}
}

int	init_envp(t_data *data, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->envp = ft_calloc(i + 1, sizeof(char *));
	if (data->envp == NULL)
		return (-1);
	i = -1;
	while (envp[++i])
		data->envp[i] = ft_strdup(envp[i]);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*command_in;
	t_data	data;

	argc = 0;
	init_envp(&data, envp);
	// not sure to protect with if -1, exit
	argv = NULL;
	command_in = readline("Our_minishell\% ");
	while (command_in != 0)
	{
		data.nr_cmds = 1;
		data.cmd_nr = 0;
		data.o_file = NULL;
		data.i_file = NULL;
		data.nr_pipes = 0;
		data.params = ft_split(command_in, ' ');
		// parsing should happen here
		if (exec_prefork_builtins(&data) == 0)
			fork_function(&data);
		//return is -1 on error, but not sure what to do with it
		free(command_in);
		command_in = NULL;
		command_in = readline("Our_minishell\% ");
	}
}