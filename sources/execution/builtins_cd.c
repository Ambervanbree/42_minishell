/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:17:40 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/04 09:34:36 by avan-bre         ###   ########.fr       */
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

void	handle_dots(t_data *data)
{
	char	**dir_tab;
	char	*path;
	int		i;

	dir_tab = ft_split(data->params[1], '/');
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
	//free everything
}

void	ft_cd(t_data *data)
{
	char	*oldpwd;
	char	*pwd;
	
	oldpwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	ft_export(oldpwd, data);
	if (data->params[1] == NULL)
	{
		if (getenv("HOME") != NULL)
			if (chdir(getenv("HOME")) == -1)
				perror("error - cd");
	}
	else if (data->params[1][0] == '/')
	{
		if (chdir(data->params[1]) == -1)
			perror("error - cd");
	}
	else
		handle_dots(data);
	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_export(pwd, data);
}
