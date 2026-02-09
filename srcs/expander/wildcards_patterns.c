#include "../includes/minishell.h"
#include <dirent.h>
#include <sys/types.h>

t_token	*everything_pattern(t_shell *shell, DIR *dir)
{
	struct dirent	*entry;
	t_token			*new_list;

	new_list = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		if (!entry)
			ft_error(shell, MALLOC);
		if (!ft_strncmp(entry->d_name, ".", 1) || !ft_strncmp(entry->d_name,
				"..", 2))
			continue ;
		add_wildcards_token(shell, entry->d_name, &new_list);
	}
	return (new_list);
}

t_token	*start_with_pattern(t_shell *shell, t_token *token, DIR *dir)
{
	struct dirent	*entry;
	t_token			*new_list;
	char			*cmp;
	int				len;

	new_list = NULL;
	cmp = token->wildcards.start;
	len = ft_strlen(cmp);
	while ((entry = readdir(dir)) != NULL)
	{
		if (!entry)
			ft_error(shell, MALLOC);
		if (!ft_strncmp(entry->d_name, cmp, len))
			add_wildcards_token(shell, entry->d_name, &new_list);
	}
	return (new_list);
}

t_token	*end_with_pattern(t_shell *shell, t_token *token, DIR *dir)
{
	struct dirent	*entry;
	t_token			*new_list;
	char			*cmp;
	int				len_end;

	new_list = NULL;
	cmp = token->wildcards.end;
	len_end = ft_strlen(cmp);
	while ((entry = readdir(dir)) != NULL)
	{
		if (!entry)
			ft_error(shell, MALLOC);
		if (!ft_strncmp(cmp, "/", 2) && entry->d_type == DT_DIR
			&& !ft_strrchr(entry->d_name, '.'))
			is_directory(shell, entry, &new_list);
		else if (!ft_strncmp(entry->d_name + ft_strlen(entry->d_name) - len_end,
				cmp, len_end + 1))
			add_wildcards_token(shell, entry->d_name, &new_list);
	}
	return (new_list);
}

t_token	*anything_containing_pattern(t_shell *shell, t_token *token, DIR *dir)
{
	struct dirent	*entry;
	t_token			*new_list;
	char			*cmp;
	int				len;

	new_list = NULL;
	cmp = token->wildcards.end;
	while ((entry = readdir(dir)) != NULL)
	{
		if (!entry)
			ft_error(shell, MALLOC);
		if (!ft_strncmp(entry->d_name, ".", 1) || !ft_strncmp(entry->d_name,
				"..", 2))
			continue ;
		len = ft_strlen(entry->d_name);
		if (ft_strnstr(entry->d_name, cmp, len))
			add_wildcards_token(shell, entry->d_name, &new_list);
	}
	return (new_list);
}

t_token	*in_between_pattern(t_shell *shell, t_token *token, DIR *dir)
{
	struct dirent	*entry;
	t_token			*new_list;
	char			*cmp_start;
	char			*cmp_end;
	int				start_len;

	new_list = NULL;
	cmp_start = token->wildcards.start;
	start_len = ft_strlen(cmp_start);
	if (!start_len)
		return (NULL);
	cmp_end = token->wildcards.end;
	while ((entry = readdir(dir)) != NULL)
	{
		if (!entry)
			ft_error(shell, MALLOC);
		if (!ft_strncmp(entry->d_name, cmp_start, start_len)
			&& !strcmp_end(entry->d_name, cmp_end))
			add_wildcards_token(shell, entry->d_name, &new_list);
	}
	return (new_list);
}
