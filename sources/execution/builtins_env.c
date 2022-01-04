/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:07:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/03 10:38:26 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->output_file != NULL)
		redirect_output(data);
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	exit (0);
	// not sure if to the last variable /env should be added
}

void	ft_export(char *var, t_data *data)
{
	int		i;
	int		j;

	j = 0;
	if (!(in_set('=', var)))
		return ;
	while (var[j] != '=')
		j++;
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, j + 1) == 0)
		{
			data->envp[i] = var;
			return ;
		}
		i++;
	}
	data->envp[i] = data->envp[i - 1];
	data->envp[i - 1] = var;
	data->envp[i + 1] = NULL;
}

void	ft_unset(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->params[1], data->envp[i], 
			ft_strlen(data->params[1])) == 0)
			while (data->envp[i + 1])
			{
				data->envp[i] = data->envp[i + 1];
				i++;
			}
	}
	data->envp[i - 1] = NULL;
}
