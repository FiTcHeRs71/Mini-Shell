#include "../includes/minishell.h"

int	ft_envsize(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	*ft_strjoin_slash(char const *s1, char const *s2)
{
	char	*s12;
	int		s1len;
	int		s2len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s12 = (char *)ft_calloc(s1len + s2len + 2, sizeof(char));
	if (!s12)
		return (NULL);
	ft_strlcpy(s12, (const char *)s1, s1len + 1);
	if (s12[s1len - 1] != '/')
	{
		s12[s1len++] = '/';
		s12[s1len + 1] = '\0';
	}
	ft_strlcpy(s12 + s1len, (const char *)s2, s2len + 1);
	return (s12);
}

int	update_cmd(t_shell *shell, t_ast_node *node, char *cmd)
{
	t_env	*tmp_env;
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	tmp_env = shell->env;
	while (ft_strncmp(tmp_env->key, "PATH", 4) != 0 && tmp_env)
		tmp_env = tmp_env->next;
	if (!tmp_env)
		return (127);
	paths = ft_split(tmp_env->value, ':');
	while (paths[i])
	{
		path = ft_strjoin_slash(paths[i], cmd);
		if (access(path, X_OK) == 0)
		{
			node->cmd_path = path;
			return (ft_free_2d_array(paths), 0);
		}
		else
			free(path);
		i++;
	}
	ft_free_2d_array(paths);
	return (127);
}

