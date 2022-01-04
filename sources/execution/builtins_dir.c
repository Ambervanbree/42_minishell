/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:18:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/03 10:40:28 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	if (data->output_file != NULL)
		redirect_output(data);
	printf("%s\n", getcwd(NULL, 0));
	exit (0) ;
}

void	ft_echo(t_data *data)
{
	if (data->output_file != NULL)
		redirect_output(data);
	if (data->params[1] == NULL)
		printf("\n");
	else
		printf("%s\n", data->params[1]);
	exit (0);
}
