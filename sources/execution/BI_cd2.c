/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:02:58 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/26 17:03:15 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_dir(char **path, char *dir)
{
	char	*temp;

	temp = *path;
	*path = ft_strjoin(*path, "/");
	*path = ft_strjoin(*path, dir);
	free(temp);
	temp = NULL;
}

void	one_dir_up(char **path)
{
	int		i;
	char	*temp;

	temp = *path;
	i = ft_strlen(*path);
	while (i && (*path)[i] != '/')
		i--;
	*path = ft_substr(*path, 0, i);
	free(temp);
	temp = NULL;
}

void	free_dir_tab(char **dir_tab)
{
	int	i;

	i = -1;
	while (dir_tab[++i])
	{
		if (dir_tab[i])
		{
			free(dir_tab[i]);
			dir_tab[i] = NULL;
		}
	}
	if (dir_tab)
	{
		free(dir_tab);
		dir_tab = NULL;
	}
}

void	handle_dots(t_cmd *cmd)
{
	char	**dir_tab;
	char	*path;
	int		i;

	dir_tab = ft_split(cmd->params[1], '/');
	i = 0;
	path = getcwd(NULL, 0);
	while (dir_tab[i])
	{
		if (ft_strncmp(dir_tab[i], ".\0", ft_strlen(dir_tab[i]) + 1) == 0)
			i++;
		else if (ft_strncmp(dir_tab[i], "..\0", ft_strlen(dir_tab[i]) + 1) == 0)
		{
			one_dir_up(&path);
			i++;
		}
		else
		{
			add_dir(&path, dir_tab[i]);
			i++;
		}
	}
	if (chdir(path) == -1)
		perror("error - cd");
	free_dir_tab(dir_tab);
}
