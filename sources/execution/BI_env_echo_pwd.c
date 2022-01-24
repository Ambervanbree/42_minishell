/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_env_echo_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:18:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/24 13:23:10 by avan-bre         ###   ########.fr       */
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
	while (cmd->data->envp->next)
	{
		if (cmd->data->envp->var
			&& ft_strncmp("_\0", cmd->data->envp->name, 2) != 0)
			ft_printf("%s=%s\n", cmd->data->envp->name, cmd->data->envp->var);
		cmd->data->envp = cmd->data->envp->next;
	}
	ft_printf("_=/bin/env\n");
	exit (0);
}
