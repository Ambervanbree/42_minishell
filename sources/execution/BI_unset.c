/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:07:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/24 17:09:44 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_envp(t_envp *envp, char *name)
{
	while (envp)
	{
		if (ft_strncmp(envp->name, name, ft_strlen(envp->name) + 1) == 0)
		{
			envp->previous->next = envp->next;
			free (envp);
			envp = NULL;
			return ;
		}
		envp = envp->next;
	}
}

void	ft_unset(t_cmd *cmd)
{
	int		i;
	t_envp	*temp;
	
	temp = cmd->data->envp;
	i = 0;
	while (cmd->params[++i])
	{
		if (check_identifier(cmd->params[i], UNSET))
		{
			while (temp)
			{
				if (ft_strncmp(temp->name, cmd->params[i], ft_strlen(temp->name)) == 0)
				{
					remove_from_envp(cmd->data->envp, temp->name);
					return ;
				}
				temp = temp->next;
			}
		}
	}
}
