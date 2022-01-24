/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:17:40 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/24 13:06:35 by avan-bre         ###   ########.fr       */
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

void	handle_dots(t_cmd *cmd)
{
	char	**dir_tab;
	char	*path;
	int		i;

	dir_tab = ft_split(cmd->params[1], '/');
	//dirtab needs to be freed
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
}

// void	finish_cd(t_data *data, char *pwd, char *oldpwd)
// {
// 	size_t	i;

// 	i = ft_strlen(pwd);
// 	if (ft_strlen(oldpwd) > i)
// 		i = ft_strlen(oldpwd);
// 	if (ft_strncmp(pwd, oldpwd, i) != 0)
// 	{
// 		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
// 		add_to_envp(data, oldpwd);
// 		pwd = ft_strjoin("PWD=", pwd);
// 		add_to_envp(data, pwd);
// 	}
// }

void	find_home_cd(t_data *data)
{
	int		i;

	i = -1;
	while (data->envp->next)
	{
		if (ft_strncmp("HOME\0", data->envp->name, 5) == 0
			&& data->envp->var != NULL)
		{
			if (chdir(data->envp->var) == -1)
				perror("error - cd");
		}
		data->envp = data->envp->next;
	}
}

void	ft_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	
	oldpwd = getcwd(NULL, 0);
	if (cmd->params[1] == NULL)
		find_home_cd(cmd->data);
	else if (cmd->params[1][0] == '/')
	{
		if (chdir(cmd->params[1]) == -1)
			perror("error - cd");
	}
	else
		handle_dots(cmd);
	pwd = getcwd(NULL, 0);
//	finish_cd(cmd->data, pwd, oldpwd);
}
