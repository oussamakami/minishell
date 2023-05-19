/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:48:10 by okamili           #+#    #+#             */
/*   Updated: 2023/05/19 12:28:14 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONS_H
# define EXECUTIONS_H

# include <sys/wait.h>
# include "../libft/libft.h"
# include "../parsing/parsing.h"

void	run_cmd(t_cmd *cmd);
t_cmd	*run_pipe_commands(t_cmd *cmds);
// t_cmd	*run_cmds_pipe(t_cmd *cmd);
#endif