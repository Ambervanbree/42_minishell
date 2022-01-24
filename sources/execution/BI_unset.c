/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:07:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/24 17:09:44 by avan-bre         ###   ########.fr       */
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

t_envp	*remove_from_envp(t_envp *envp, char *name)
{
	t_envp	*temp;
	t_envp	*temp2;

	temp2 = envp;
	while (envp)
	{
		if (ft_strncmp(envp->name, name, ft_strlen(envp->name) + 1))
		{
			temp = envp;
			envp = envp->next;
			free (temp);
			temp = NULL;
			break ;
		}
		envp = envp->next;
	}
	return (temp2);

// 	char	**temp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	printf("index is: %d\n", index);
// 	while (data->envp[i])
// 		i++;
// 	temp = data->envp;
// 	data->envp = ft_calloc(i, sizeof(char *));
// 	j = -1;
// 	while (++j < index)
// 	{
// 		data->envp[j] = temp[j];
// 		printf("copied: %d: %s\n", j, data->envp[j]);
// 	}
// 	while (j < (i - 1))
// 	{
// 		data->envp[j] = temp[j + 1];
// 		printf("alter copied: %d, %s\n", j, data->envp[j]);
// 		j++;
// 	}
// 	printf("to delete: %d, %s\n", j, data->envp[j]);
// //	exit (0);
// 	free(temp[j + 1]);
// 	temp[j] = NULL;
}

void	ft_unset(t_cmd *cmd)
{
	int		i;
	t_envp	*temp;
	
	temp = cmd->data->envp;
	i = 0;
	while (cmd->params[++i])
	{
		if (check_identifier_unset(cmd->params[i]))
		{
			while (temp)
			{
				if (ft_strncmp(temp->name, cmd->params[i], ft_strlen(temp->name)) == 0)
				{
					cmd->data->envp = remove_from_envp(cmd->data->envp, temp->name);
					return ;
				}
				temp = temp->next;
			}
		}
	}
}
