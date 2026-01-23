#include "../includes/minishell.h"
#include <sys/types.h>
#include <dirent.h>

t_token	*everything_pattern(t_shell *shell, DIR *dir)
{
	struct dirent	*entry;
	t_token	*new_list;

	new_list = new_token(shell);
	while ((entry = readdir(dir)) != NULL)
	{
		if(!entry)
			ft_error(shell, MALLOC);
		if (!ft_strncmp(entry->d_name, ".", 1) || !ft_strncmp(entry->d_name, "..", 2))
			continue ;
		add_wildcards_token(shell, entry->d_name, &new_list);
	}
	return(new_list);
}

t_token	*start_with_pattern(t_shell *shell, t_token *token, DIR *dir)
{
	struct dirent	*entry;
	t_token			*new_list;
	char			*cmp;
	int				len;

	new_list = new_token(shell);
	cmp = token->wildcards.start;
	len = ft_strlen(cmp);
	while ((entry = readdir(dir)) != NULL)
	{
		if(!entry)
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

	new_list = new_token(shell);
	cmp = token->wildcards.end;
	len_end = ft_strlen(cmp);
	while ((entry = readdir(dir)) != NULL)
	{
		if(!entry)
			ft_error(shell, MALLOC);
		if (!ft_strncmp(cmp, "/", 2) && entry->d_type == DT_DIR && !ft_strrchr(entry->d_name, '.'))
			add_wildcards_token(shell, ft_strjoin(entry->d_name, "/"), &new_list);
		else if (!ft_strncmp(entry->d_name + ft_strlen(entry->d_name) - len_end, cmp, len_end + 1))
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

	new_list = new_token(shell);
	cmp = token->wildcards.end;
	while ((entry = readdir(dir)) != NULL)
	{
		if(!entry)
			ft_error(shell, MALLOC);
		if (!ft_strncmp(entry->d_name, ".", 1) || !ft_strncmp(entry->d_name, "..", 2))
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

	new_list = new_token(shell);
	cmp_start = token->wildcards.start;
	cmp_end = token->wildcards.end;
	while ((entry = readdir(dir)) != NULL)
	{
		if(!entry)
			ft_error(shell, MALLOC);
		if (!strcmp_start(entry->d_name, cmp_start) && !strcmp_end(entry->d_name, cmp_end))
			add_wildcards_token(shell, entry->d_name, &new_list);
	}
	return (new_list);
}
