/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:43:49 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/18 11:47:09 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exported_variables(t_data *data)
{
	int		i;
	int		j;
	char	*var;
	char	*name;

	i = -1;
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
	}
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
				printf("Data->envp: %s, %p\n", data->envp[j], data->envp[j]);
				printf("New var: %s, %p\n", var, var);
				temp = data->envp[j];
				data->envp[j] = var;
				printf("free %s, %p\n", temp, temp);
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
	int	i;
	int	set;
	int	j;

	set = 0;
	if (ft_strrchr(var, '='))
		set = 1;
	i = 0;
	while (!(var[i] == '=' || var[i] == '\0'))
		i++;
	j = add_if_existing(data, i, set, var);
	if (j)
	{
		data->envp[j] = data->envp[j - 1];
		data->envp[j - 1] = var;
		data->envp[j + 1] = NULL;
	}
}

int	check_identifier_export(char *id)
{
	int	i;

	if (ft_isdigit(id[0]) || id == '\0')
	{
		ft_printf("%s: '%s': %s\n", "export", id, "not a valid identifier");
		return (0);
	}
	i = -1;
	while (id[++i] != '=' && id[i] != '\0')
	{
		if (!(ft_isalnum(id[i]) || (id[i] == '_')))
		{
			ft_printf("%s: '%s': %s\n", "export", id, "not a valid identifier");
			//should make ft_printf_fd here maybe to print on stderr
			return (0);
		}
	}
	return (1);
}

void	ft_export(t_data *data)
{
	int		i;
	char	*temp;

	i = -1;
	if (data->params[1] == NULL)
	{
		print_exported_variables(data);
		return ;
	}
	i = 0;
	while (data->params[++i])
	{
		if (check_identifier_export(data->params[i]))
		{
			temp = malloc(sizeof(char) * (ft_strlen(data->params[i]) + 1));
			if (temp == NULL)
			{
				perror("malloc failed");
				return ;
			}
			add_to_envp(data, temp);
		}
	}
}
