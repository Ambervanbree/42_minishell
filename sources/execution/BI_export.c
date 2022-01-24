/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:43:49 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/24 17:24:06 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exported_variables(t_envp *envp)
{
	t_envp	*temp;

	temp = envp;
	while (temp)
	{
		if (temp->var)
			ft_printf("%s %s=\"%s\"\n", "declare -x", temp->name, temp->var);
		else
			ft_printf("%s %s\n", "declare -x", temp->name);
		temp = temp->next;
	}
}

void	add_to_envp(t_envp *envp, char *var)
{
	t_envp	*new;
	t_envp	*temp;
	t_envp	*temp2;
	
	temp = envp;
	new = new_item(var);
	while (temp->next->next)
	{
		if (ft_strncmp(temp->next->name, new->name, ft_strlen(new->name) + 1) == 0)
		{
			if (new->var)
			{
				new->next = temp->next->next;
				temp2 = temp->next;
				temp->next = new;
				free(temp2);
				temp2 = NULL;
			}
			return ;
		}
		temp = temp->next;
	}
	add_item_back(&temp, new);
}

int	check_identifier_export(char *id)
{
	int	i;

	if (ft_isdigit(id[0]) || id == '\0')
	{
		ft_printf("%s: '%s': %s\n", "export",
			id, "not a valid identifier");
		return (0);
	}
	i = -1;
	while (id[++i] != '=' && id[i] != '\0')
	{
		if (!(ft_isalnum(id[i]) || (id[i] == '_')))
		{
			ft_printf("%s: '%s': %s\n", "export",
				id, "not a valid identifier");
			//should make ft_printf_fd here maybe to print on stderr
			return (0);
		}
	}
	return (1);
}

void	ft_export(t_cmd *cmd)
{
	int		i;

	i = -1;
	if (cmd->params[1] == NULL)
	{
		print_exported_variables(cmd->data->envp);
		return ;
	}
	else
	{
		i = 0;
		while (cmd->params[++i])
		{
			if (check_identifier_export(cmd->params[i]))
				add_to_envp(cmd->data->envp, cmd->params[i]);
		}
	}
}
