#include "parsing.h"

static char *get_relative_path(char *cmd)
{
	char *work_dir;
	char *result;

	work_dir = get_work_dir();
	result = NULL;
	if (!cmd)
		return (NULL);
	if (cmd[0] == '~')
		result = replace_word(cmd, "~", getenv("HOME"), 0);
	else if (cmd[0] == '.')
	{
		result = replace_word(cmd, ".", work_dir, 0);
		result = replace_word(result, "~", getenv("HOME"), 1);
	}
	else if (cmd[0] == '/')
		result = ft_strdup(cmd);
	free(work_dir);
	return (result);
}

static char	*get_absolute_path(char *cmd)
{
	int		index;
	char	*result;
	char	**template;

	index = -1;
	template = ft_split(getenv("PATH"), ':');
	while (template && template[++index] && cmd)
	{
		result = replace_word("P/E", "E", cmd, 0);
		result = replace_word(result, "P", template[index], 1);
		if (!access(result, F_OK))
		{
			free2d((void **)template);
			return (result);
		}
		free(result);
	}
	free2d((void **)template);
	result = replace_word("Minishell: E: Command not found\n", "E", cmd, 0);
	ft_putstr_fd(result, 2);
	free(result);
	return (NULL);
}

static int	check_input(char *cmd)
{
	char *temp;

	if (cmd && cmd[0] == '.' && ft_strlen(cmd) == 1)
	{
		ft_putstr_fd("Minishell: .: Filename argument required\n", 2);
		return (2);
	}
	if (cmd && cmd[0] == '~' && ft_strlen(cmd) == 1)
	{
		temp = replace_word("Minishell: ~: Is a directory\n", "~", getenv("HOME"), 0);
		ft_putstr_fd(temp, 2);
		free(temp);
		return (126);
	}
	if (cmd && cmd[0] == '/' && ft_strlen(cmd) == 1)
	{
		ft_putstr_fd("Minishell: /: Is a directory\n", 2);
		return (126);
	}
	return (0);
}

char	*parse_exec(char *cmd, int *err)
{
	char	*result;

	result = NULL;
	if (!*err && cmd)
	{
		*err = check_input(cmd);
		if (!*err && ft_strchr(".~/", cmd[0]))
			result = get_relative_path(cmd);
		else if (!*err)
			result = get_absolute_path(cmd);
		if (!result || access(result, F_OK))
		{
			*err = 127;
			result = replace_word("Minishell: E: Command not found\n", "E", cmd, 0);
			ft_putstr_fd(result, 2);
			free(result);
			result = NULL;
		}
		else if (result && access(result, X_OK))
		{
			*err = 126;
			result = replace_word("Minishell: E: Permission denied\n", "E", cmd, 0);
			ft_putstr_fd(result, 2);
			free(result);
			result = NULL;
		}
	}
	if (result)
		return (result);
	return (ft_strdup(cmd));
}