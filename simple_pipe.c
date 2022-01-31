/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:14:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/31 13:26:19 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	int	child[2];
	int	fd_pipe[2];
	int	i;

	printf("argc is %d\n", argc);
	if (pipe(fd_pipe) == -1)
		(printf("pipe failed"));
	i = -1;
	while (++i < 2)
	{
		child[i] = fork();
		if (child[i] == -1)
			printf("Fork child %d failed\n", i);
		else if (child[i] == 0)
		{
			if (i == 0)
			{
				printf("to execute %s\n", argv[1]);
				close(fd_pipe[0]);
				dup2(fd_pipe[1], 1);
				close(fd_pipe[1]);
				execve(argv[1], argv, NULL);
				exit (0);
			}
			else
			{
				printf("to execute %s\n", argv[3]);
				close(fd_pipe[1]);
				dup2(fd_pipe[0], 0);
				close(fd_pipe[0]);
				execve(argv[3], argv + 2, NULL);
				exit (0);
			}
		}
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	int j = -1;
	while (++j < 2)
		waitpid(child[j], NULL, 0);
}