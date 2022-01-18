/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_env_echo_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:18:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/18 10:29:42 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	ft_printf("%s\n", getcwd(NULL, 0));
	exit(0);
}

int	no_backslash(t_data *data)
{
	int	i;

	i = 1;
	while (data->params[1][i] == 'n')
		i++;
	if (data->params[1][i] != '\0')
		return (0);
	else
		return (1);
}

void	ft_echo(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->params[1] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	else if (ft_strncmp(data->params[1], "-n", 2) == 0)
		j = no_backslash(data);
	i = j;
	while (data->params[++i] && data->params[i + 1])
		ft_printf("%s ", data->params[i]);
	if (j)
		ft_printf("%s", data->params[i]);
	else
		ft_printf("%s\n", data->params[i]);
	exit(0);
}

void	ft_env(t_data *data)
{	
	int	i;

	i = -1;
	while (data->envp[++i])
	{
		if (ft_strrchr(data->envp[i], '='))
			ft_printf("%s\n", data->envp[i]);
	}
	exit (0);
}
