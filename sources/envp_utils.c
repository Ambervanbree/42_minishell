/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:21:43 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/26 16:53:49 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_list(t_envp *head)
{
	t_envp	*temp;
	int		i;

	temp = head;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

t_envp	*last_list_item(t_envp *head)
{
	if (head)
		while (head->next)
			head = head->next;
	return (head);
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
	node->printed = 0;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}
