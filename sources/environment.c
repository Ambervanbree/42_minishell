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
	return (node);
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
	j = -1;
	while (++j < i)
	{
		new = new_item(envp[j]);
		if (new == 0)
			return (0);
		add_item_back(&data->envp, new);
	}
	return (1);
}
