/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:43:49 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/19 17:11:25 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exported_variables(t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*var;
	char	*name;

	i = -1;
	k = 0;
	while (data->envp[++i])
	{
		if (!ft_strrchr(data->envp[i], '='))
			ft_printf("%s %s\n", "declare -x", data->envp[i]);
		else
		{
			j = 0;
			while (data->envp[i][j] != '=')
				j++;
			name = ft_substr(data->envp[i], 0, j);
			var = ft_substr(data->envp[i], j + 1, ft_strlen(data->envp[i]));
			ft_printf("%s %s%c\"%s\"\n", "declare -x", name, '=', var);
		}
		if (data->envp[i][0] == '_' && data->envp[i][1] == '=')
			k = i;
	}
	remove_from_envp(data, k);
}

int	add_if_existing(t_data *data, int i, int set, char *var)
{
	int		j;
	char	*temp;

	j = -1;
	while (data->envp[++j])
	{
		if (ft_strncmp(data->envp[j], var, i) == 0
			&& (data->envp[j][i] == '=' || data->envp[j][i] == '\0'))
		{
			if (!set)
				return (0);
			else
			{
				temp = data->envp[j];
				data->envp[j] = var;
				if (temp)
				{
					free(temp);
					temp = NULL;
				}
				return (0);
			}
		}
	}
	return (j);
}

void	add_to_envp(t_data *data, char *var)
{
	int		i;
	int		set;
	int		j;
	char	**temp;

	set = 0;
	if (ft_strrchr(var, '='))
		set = 1;
	i = 0;
	while (!(var[i] == '=' || var[i] == '\0'))
		i++;
	j = add_if_existing(data, i, set, var);
	if (j)
	{
		temp = data->envp;
		data->envp = ft_calloc(j + 2, sizeof(char *));
		i = -1;
		while (++i < j)
			data->envp[i] = temp[i];
		data->envp[i] = ft_strdup(var);
		data->envp[i + 1] = NULL;
		free(temp);
		temp = NULL;
	}
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
		print_exported_variables(cmd->data);
		return ;
	}
	else
	{
		i = 0;
		while (cmd->params[++i])
		{
			if (check_identifier_export(cmd->params[i]))
				add_to_envp(cmd->data, cmd->params[i]);
		}
	}
}
