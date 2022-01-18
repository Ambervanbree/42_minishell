/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:33:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/17 10:37:07 by avan-bre         ###   ########.fr       */
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

typedef struct	s_data
{
	char	**tokens;
	char	**envp;
	char	*cmd;
	char	**params;
	char	*i_file;
	int		fd_i;
	char	*o_file;
	int		fd_o;
	int		cmd_nr;
	int		nr_cmds;
	int		nr_pipes;
	int		pipe_fd[1023][2];
	int		process_id[1024];
}	t_data;

int		exec_prefork_builtins(t_data *data);
int		fork_function(t_data *data);
int		exec_non_builtins(int process, t_data *data);
int		exec_builtins(t_data *data);
void	ft_echo(t_data *data);
void	ft_env(t_data *data);
void	ft_export(t_data *data);
void	add_to_envp(t_data *data, char *var);
void	ft_unset(t_data *data);
void	ft_pwd(void);
void	ft_cd(t_data *data);
int		redirect_or_pipe(t_data *data);
void	close_all_except_two(t_data *data, int pipe);
void	close_all_except(t_data *data, int pipe, int index);

#endif