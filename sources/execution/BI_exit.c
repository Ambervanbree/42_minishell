/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:57:26 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/26 12:37:50 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	numeric_string(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
	}
	return (1);
}

int	calculate_status(char *string)
{
	long long	code;
	int			ret;
	int			i;
	
	i = -1;
	while (ft_isdigit(string[i]))
		code = code * 10 + (string[i] - '0');
	if (code < 256 && code >= 0)
		ret = code;
	else
		ret = code % 256;
	return (ret);
}

void	ft_exit(t_cmd *cmd)
{
	int	code;
	
	ft_printf("%s\n", "exit");
	code = 0;
	if (cmd->params[2] != NULL)
	{
		ft_printf("%s\n", "exit: too many argurments");
		return ;
	}
	if (!numeric_string(cmd->params[1]))
	{
		ft_printf("%s\n", "exit: numeric argument required");
		code = 2;
	}
	else
		code = calculate_status(cmd->params[1]);
	free_envp(cmd);
	exit (code);
}