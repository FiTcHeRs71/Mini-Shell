#include "../includes/minishell.h"

static char	*expanded_value(t_shell *shell, char *varname, char *line)
{
	char	*var_value;
	char	*buffer;
	char	*value;
	char	*res;
	int	i;

	i = 0;
	value = line;
	buffer = ft_calloc(increment_len(line, '$', 0) + 1, sizeof(char));
	if (!buffer)
		ft_error(shell, MALLOC);
	while (*value != '$' && *value)
		buffer[i++] = *value++;
	buffer[i] = '\0';
	var_value = get_env_varname(shell, varname);
	if (!var_value)
		var_value = "";
	res = ft_strjoin(buffer, var_value);
	if (!res)
		ft_error(shell, MALLOC);
	free(buffer);
	return (res);
}

char	*find_varname(t_shell *shell, char *value, int i)
{
	char	*varname;
	int		j;

	j = 0;
	varname = ft_calloc(increment_len(value, '$', i) + 1, sizeof(char));
	if (!varname)
		ft_error(shell, MALLOC);
	while (value[i])
	{
		if (!value[i] || value[i] == '$')
			break ;
		varname[j++] = value[i++];
	}
	varname[j] = '\0';
	return (varname);
}

static char	*process_expand_heredoc(t_shell *shell, char *value, char *line)
{
	char	*varname;
	char	*new_value;
	int		i;

	i = 0;
	while (value[i] != '$' && value[i])
		i++;
	if (value[i] == '$' && value[i + 1] == '?')
	{
		free(value);
		return (ft_itoa(shell->last_exit_status));
	}
	varname = find_varname(shell, value, i);
	if (!varname)
		return (NULL);
	new_value = expanded_value(shell, varname, line);
	free(varname);
	if (!new_value)
		return (NULL);
	return (new_value);
}

char	*expand_heredoc(t_shell *shell, char *line)
{
	char	*tmp;
	char	*res;
	char	*expanded;

	tmp = line;
	if (ft_strchr(tmp, '$'))
	{
		expanded = process_expand_heredoc(shell, tmp, line);
		if(!expanded)
			ft_error(shell, MALLOC);
		res = ft_strjoin(expanded, "\n");
		if (!res)
			ft_error(shell, MALLOC);
		free(expanded);
		return (res);
	}
	return (NULL);
}
