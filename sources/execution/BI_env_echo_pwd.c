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

void	ft_echo(t_data *data)
{
	int	i;

	i = 0;
	if (data->params[1] == NULL)
		ft_printf("\n");
	else
	{
		i = 0;
		while (data->params[++i] && data->params[i + 1])
			ft_printf("%s ", data->params[i]);
	}
	ft_printf("%s\n", data->params[i]);
	exit(0);
}

void	ft_env(t_data *data)
{	
	int	i;

	i = -1;
	while (data->envp[++i] && ft_strrchr(data->envp[i], '='))
		ft_printf("%s\n", data->envp[i]);
	exit (0);
}
