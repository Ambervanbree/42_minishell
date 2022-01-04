/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:33:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/03 10:12:59 by avan-bre         ###   ########.fr       */
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

typedef struct	s_data
{
	char	**tokens;
	char	**envp;
	char	*cmd;
	char	**params;
	char	*input_file;
	int		fd_in;
	char	*output_file;
	int		fd_out;
	int		nr_cmds;
	int		nr_pipes;
	int		pipe_fd[1023][2];
	int		process_id[1024];
}	t_data;

int		execute_command(int process, t_data *data, char *command);
int		execute_non_builtin(int process, t_data *data);
int		execute_builtin(t_data *data);
void	ft_echo(t_data *data);
void	ft_env(t_data *data);
void	ft_export(char *var, t_data *data);
void	ft_unset(t_data *data);
int		redirect_input(t_data *data);
int		redirect_output(t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_data *data);
void	close_all_except_two(t_data *data, int pipe);
void	close_all_except(t_data *data, int pipe, int index);

#endif