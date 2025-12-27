#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct	s_env //TODO : ajouter un valeur qui save le debut.
{
	char			*key;
	char			*value;
	struct	s_env	*prev;
	struct	s_env	*next;
}				t_env;
















typedef struct	s_shell
{
	t_env	**env;
}				t_shell;


#endif