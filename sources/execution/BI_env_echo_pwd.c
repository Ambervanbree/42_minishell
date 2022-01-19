/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_env_echo_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:18:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/19 17:16:53 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	ft_printf("%s\n", getcwd(NULL, 0));
	exit(0);
}

int	no_backslash(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->params[1][i] == 'n')
		i++;
	if (cmd->params[1][i] != '\0')
		return (0);
	else
		return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd->params[1] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	else if (ft_strncmp(cmd->params[1], "-n", 2) == 0)
		j = no_backslash(cmd);
	i = j;
	while (cmd->params[++i] && cmd->params[i + 1])
		ft_printf("%s ", cmd->params[i]);
	if (j)
		ft_printf("%s", cmd->params[i]);
	else
		ft_printf("%s\n", cmd->params[i]);
	exit(0);
}

void	ft_env(t_cmd *cmd)
{	
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd->data->envp[++i])
	{
		if (cmd->data->envp[i][0] == '_' && cmd->data->envp[i][1] == '=')
			j = i;
		else
		{
			if (ft_strrchr(cmd->data->envp[i], '='))
				ft_printf("%s\n", cmd->data->envp[i]);
		}
	}
	ft_printf("_=/bin/env\n");
	exit (0);
}
