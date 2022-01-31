/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:43:49 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/31 16:08:59 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_printed(t_envp *envp)
{
	t_envp	*temp;

	temp = envp;
	while (temp)
	{
		temp->printed = 0;
		temp = temp->next;
	}
}

int	smaller_ascii(char *str1, char *str2)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(str1);
	if (ft_strlen(str2) < size)
		size = ft_strlen(str2);
	i = -1;
	while (++i < size)
	{
		if (str1[i] < str2[i])
			return (1);
		if (str1[i] > str2[i])
			return (0);
	}
	return (1);
}

t_envp	*get_smallest_unprinted(t_envp *envp, int size)
{
	t_envp	*temp;
	t_envp	*min;
	int		i;

	temp = envp;
	while (temp->printed)
		temp = temp->next;
	min = temp;
	temp = envp;
	i = -1;
	while (++i < size)
	{
		if (temp->printed == 0 && smaller_ascii(temp->name, min->name))
			min = temp;
		temp = temp->next;
	}
	return (min);
}

void	print_exported_variables(t_envp *envp)
{
	t_envp	*temp;
	t_envp	*min;
	int		size;
	int		i;

	size = size_list(envp);
	temp = envp;
	i = -1;
	while (++i < size)
	{
		min = get_smallest_unprinted(envp, size);
		if (min->var)
			ft_printf("%s %s=\"%s\"\n", "declare -x", min->name, min->var);
		else
			ft_printf("%s %s\n", "declare -x", min->name);
		min->printed++;
	}
	reset_printed(envp);
}

void	ft_export(t_cmd *cmd)
{
	int		i;

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
			if (check_identifier(cmd->params[i], EXPORT))
				add_to_envp(cmd->data->envp, cmd->params[i]);
		}
	}
}
