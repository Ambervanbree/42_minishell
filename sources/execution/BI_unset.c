/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:07:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/17 13:50:18 by avan-bre         ###   ########.fr       */
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

void	update_env(t_data *data, int index)
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

void	ft_unset(t_data *data)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (data->params[++i])
	{
		if (check_identifier_unset(data->params[i]))
		{
			j = -1;
			while (data->envp[++j])
			{
				len = ft_strlen(data->params[i]);
				if (ft_strncmp(data->params[i], data->envp[j], len) == 0
					&& (data->envp[j][len] == '=' || data->envp[j][len] == '\0'))
				{
					update_env(data, j);
					// while (data->envp[j + 1])
					// {
					// 	data->envp[j] = data->envp[j + 1];
					// 	j++;
					// }
					// free(data)
					// data->envp[j] = NULL;
				}
			}
		}
	}
}
