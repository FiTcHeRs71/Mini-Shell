#include "../includes/minishell.h"

static char	*get_env_varname(t_shell *shell, char *key)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);	
}

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

void find_varname(char *varname, char *value, int i, int j)
{
	while (value[i])
	{
		if (value[i] == '$')
			i++;
		if (!value[i])
			break ;
		varname[j++] = value[i++];
	}
	varname[j] = '\0';
}

static char	*process_expand_heredoc(t_shell *shell, char *value, char *line)
{
	char	*varname;
	char	*new_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (value[i] != '$' && value[i])
		i++;
	if (value[i] == '$' && value[i + 1] == '?')
	{
		free(value);
		return (ft_itoa(shell->last_exit_status));
	}
	varname = ft_calloc(increment_len(value, ' ', i), sizeof(char));
	if (!varname)
		return (NULL);
	find_varname(varname, value, i, j);
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
