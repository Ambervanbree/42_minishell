/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:07:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/19 16:17:04 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_identifier_unset(char *id)
{
	int	i;

	if (ft_isdigit(id[0]) || id == '\0')
	{
		ft_printf("%s: '%s': %s\n", "unset", id, "not a valid identifier");
		return (0);
	}
	i = -1;
	while (id[++i])
	{
		if (!(ft_isalnum(id[i]) || (id[i] == '_')))
		{
			ft_printf("%s: '%s': %s\n", "unset", id, "not a valid identifier");
			//should make ft_printf_fd here maybe to print on stderr
			return (0);
		}
	}
	return (1);
}

void	remove_from_envp(t_data *data, int index)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	while (data->envp[i])
		i++;
	temp = data->envp;
	data->envp = ft_calloc(i, sizeof(char *));
	j = -1;
	while (++j < index)
		data->envp[j] = temp[j];
	while (j < (i - 1))
	{
		data->envp[j] = temp[j + 1];
		j++;
	}
	free(data->envp[j]);
	data->envp[j] = NULL;
}

void	ft_unset(t_cmd *cmd)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (cmd->params[++i])
	{
		if (check_identifier_unset(cmd->params[i]))
		{
			j = -1;
			while (cmd->data->envp[++j])
			{
				len = ft_strlen(cmd->params[i]);
				if (ft_strncmp(cmd->params[i], cmd->data->envp[j], len) == 0
					&& (cmd->data->envp[j][len] == '=' || cmd->data->envp[j][len] == '\0'))
					remove_from_envp(cmd->data, j);
			}
		}
	}
}
