/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/26 17:15:21 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(char *id, int code)
{
	int	i;

	if (ft_isdigit(id[0]) || id[0] == '\0')
	{
		if (code == 3)
			ft_printf("%s: '%s': %s\n", "export", id, "not a valid identifier");
		if (code == 4)
			ft_printf("%s: '%s': %s\n", "unset", id, "not a valid identifier");
		return (0);
	}
	i = -1;
	while (id[++i] != '=' && id[i] != '\0')
	{
		if (!(ft_isalnum(id[i]) || (id[i] == '_')))
		{
			if (code == 3)
				ft_printf("%s: '%s': %s\n", "export",
					id, "not a valid identifier");
			if (code == 4)
				ft_printf("%s: '%s': %s\n", "unset",
					id, "not a valid identifier");
			return (0);
		}
	}
	return (1);
}

void	add_to_envp(t_envp *envp, char *var)
{
	t_envp	*new;
	t_envp	*temp;

	temp = envp;
	new = new_item(var);
	while (envp)
	{
		if (ft_strncmp(envp->name, new->name, ft_strlen(envp->name) + 1) == 0)
		{
			if (new->var)
			{
				new->next = envp->next;
				new->previous = envp->previous;
				envp->previous->next = new;
				if (envp->next)
					envp->next->previous = new;
				free(envp);
				envp = NULL;
			}
			return ;
		}	
		envp = envp->next;
	}
	add_item_back(&temp, new);
}
