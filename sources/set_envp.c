/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:09:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/26 16:56:25 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_cmd *cmd)
{
	int		i;
	t_envp	*temp;

	i = -1;
	while (cmd->params[++i])
	{
		if (cmd->params[i])
		{
			free(cmd->params[i]);
			cmd->params[i] = NULL;
		}
	}
	while (cmd->data->envp)
	{
		temp = cmd->data->envp;
		cmd->data->envp = cmd->data->envp->next;
		if (temp->name != NULL)
		{
			free(temp->name);
			temp->name = NULL;
		}
		if (temp->var != NULL)
		{		
			free(temp->var);
			temp->var = NULL;
		}
		free(temp);
		temp = NULL;
	}
}

void	adapt_values(t_envp **envp)
{
	add_to_envp(*envp, "SHLVL=2");
	remove_from_envp(*envp, "OLDPWD");
	add_to_envp(*envp, "OLDPWD");
	remove_from_envp(*envp, "_");
}

int	init_empty_env(t_envp **envp)
{
	t_envp	*new;
	char	*pwd;

	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	new = new_item(pwd);
	if (new == 0)
		return (0);
	add_item_back(envp, new);
	new = new_item("SHLVL=2\0");
	if (new == 0)
		return (0);
	add_item_back(envp, new);
	free(pwd);
	pwd = NULL;
	return (1);
}

int	init_envp(t_data *data, char *envp[])
{
	int		i;
	int		j;
	t_envp	*new;

	i = 0;
	while (envp[i])
		i++;
	if (i)
	{
		j = -1;
		while (++j < i)
		{
			new = new_item(envp[j]);
			if (new == 0)
				return (-1);
			add_item_back(&data->envp, new);
		}
		adapt_values(&data->envp);
	}
	else
	{
		if (init_empty_env(&data->envp) == 0)
			return (-1);
	}
	return (1);
}
