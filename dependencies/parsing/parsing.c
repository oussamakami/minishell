/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:42:09 by okamili           #+#    #+#             */
/*   Updated: 2023/05/30 08:26:43 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*clean_quotes(char *cmd)
{
	int		i;
	int		dquotes;
	int		squotes;
	char	*result;

	if (!cmd)
		return (NULL);
	i = 0;
	dquotes = 0;
	squotes = 0;
	result = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	while (cmd[0])
	{
		if ((cmd[0] == '"' && (!(squotes & 1) || (dquotes & 1)))
			|| (cmd[0] == '\'' && (!(dquotes & 1) || (squotes & 1))))
		{
			squotes += cmd[0] == '\'';
			dquotes += cmd[0] == '"';
		}
		else
			result[i++] = cmd[0];
		cmd++;
	}
	return (result);
}

void	parsing(t_cmd *cmd)
{
	char	*temp;

	if (!cmd)
		return ;
	temp = replace_variables(cmd->cmd, cmd->prev_error);
	cmd->args = parse_args(temp);
	free(temp);
	parse_redir(cmd);
	check_redir(cmd);
	temp = clean_quotes(cmd->args[0]);
	if (is_builtin(temp))
		cmd->exec = temp;
	else
		cmd->exec = parse_exec(temp, &cmd->error);
}
