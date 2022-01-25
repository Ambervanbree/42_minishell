/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:09:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/24 16:33:04 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_cmd *cmd)
{
	int	i;
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

t_envp	*last_list_item(t_envp *node)
{
	if (node)
		while (node->next)
			node = node->next;
	return (node);
}

void	add_item_back(t_envp **list, t_envp *new)
{
	t_envp	*last;
	
	if (*list == 0)
		*list = new;
	else
	{
		last = last_list_item(*list);
		new->previous = last;
		last->next = new;
	}
}

t_envp	*new_item(char *string)
{
	t_envp	*node;
	int		i;
	int		j;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (0);
	i = 0;
	while (!(string[i] == '=' || string[i] == '\0'))
		i++;
	node->name = ft_substr(string, 0, i);
	if (string[i] == '=')
	{
		i++;
		j = i;
		while (string[j])
			j++;
		node->var = ft_substr(string, i, j - i);
	}
	else
		node->var = NULL;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

void	adapt_values(t_envp **envp)
{
	add_to_envp(*envp, "SHLVL=2");
	remove_from_envp(*envp, "OLDPWD");
	add_to_envp(*envp, "OLDPWD");
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

	data->envp = NULL;
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
				return (0);
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
