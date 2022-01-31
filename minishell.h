/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:33:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/31 16:58:48 by avan-bre         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

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

typedef struct	s_envp
{
	char			*name;
	char			*var;
	int				printed;
	struct s_envp	*next;
	struct s_envp	*previous;
}	t_envp;

typedef struct	s_data
{
	t_envp			*envp;
	int				nr_cmds;
	struct s_cmd	*cmd;
	int				pipe[2];
	int				pipe_fd[1023][2];
	int				process_id[1024];
}	t_data;

typedef struct	s_cmd
{
	char	**params;
	char	*i[2];
	char	*o[2];
	int		out[2];
	int		fd_i[2];
	int		fd_o[2];
	int		id;
	t_data	*data;
}	t_cmd;

int		init_envp(t_data *data, char *envp[]);
void	free_envp(t_cmd *cmd);
t_envp	*new_item(char *string);
void	add_item_back(t_envp **list, t_envp *new);
int		size_list(t_envp *head);
void	add_to_envp(t_envp *envp, char *var);
void	remove_from_envp(t_envp *envp, char *name);
int		check_identifier(char *id, int code);
int		exec_prefork_builtins(t_cmd *cmd);
int		fork_function(t_cmd *cmd);
int		exec_non_builtins(int process, t_cmd *cmd);
int		exec_builtins(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_export(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(t_cmd *cmd);
void	handle_dots(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
int		redirect_io(t_cmd *cmd);
void	reverse_redirection(t_cmd *cmd, int in, int out);
int		init_pipes(t_data *data);
int		pipe_function(t_cmd *cmd);
void	close_all_except_two(t_data *data, int pipe);
//void	close_all_except(t_data *data, int pipe, int index);

#endif