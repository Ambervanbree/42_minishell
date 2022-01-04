/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:32:53 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/03 10:43:09 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
int	main(int argc, char *argv[], char *envp[])
 {
	char	*command_in;
	t_data	data;

	argc = 0;
	argv = NULL;
	command_in = readline("Our_minishell\% ");
	while (command_in != 0)
	{
		data.nr_cmds = 1;
		data.output_file = NULL;
		data.input_file = NULL;
		data.nr_pipes = 0;
		data.envp = envp;
		// parsing should happen here
		// the number I'm passing as first arg below is the process nr (now 0 because simple command)
		// will encorporate counter in fork function
		data.process_id[0] = fork ();
		if (data.process_id[0] == -1)
		{
			perror("error - fork failed");
			return (1);
		}
		else if (data.process_id[0] == 0)
		{
			if (execute_command(0, &data, command_in) == 0)
				return (1);
		}
		else
			waitpid(data.process_id[0], NULL, 0);
		free(command_in);
		command_in = NULL;
		command_in = readline("Our_minishell\% ");
	}
}