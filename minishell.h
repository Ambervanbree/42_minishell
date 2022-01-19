/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:33:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/19 16:06:19 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

enum	BI
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

struct	s_cmd;

typedef struct	s_data
{
	char			**envp;
	int				nr_cmds;
	int				nr_pipes;
	struct s_cmd	*cmd;
	int				pipe_fd[1023][2];
	int				process_id[1024];
}	t_data;

typedef struct	s_cmd
{
	char	**params;
	int		fd_i;
	int		fd_o;
	char	*i_file;
	char	*o_file;
	int		id;
	t_data	*data;
}	t_cmd;

int		exec_prefork_builtins(t_cmd *cmd);
int		fork_function(t_cmd *cmd);
int		exec_non_builtins(int process, t_cmd *cmd);
int		exec_builtins(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_export(t_cmd *cmd);
void	add_to_envp(t_data *data, char *var);
void	remove_from_envp(t_data *data, int index);
void	ft_unset(t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(t_cmd *cmd);
int		redirect_or_pipe(t_cmd *cmd);
void	close_all_except_two(t_data *data, int pipe);
void	close_all_except(t_data *data, int pipe, int index);

#endif