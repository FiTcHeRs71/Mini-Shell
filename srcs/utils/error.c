
#include "../../includes/minishell.h"

void	syntaxe_error(char *msg)
{
	ft_putstr_fd("Minishell : syntax error near unexpected token ", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	g_signal = 2;
}

void	ft_error(t_shell *shell, int error)
{
	if (error == MALLOC)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		clean_before_exit(shell);
		exit(EXIT_FAILURE);
	}
	else if (error == CD)
	{
		ft_putstr_fd("Unable to find or acces at directory\n", 2);
	}
	else if (error == CD_ENTRY)
	{
		ft_putstr_fd("error retrieving current directory\n", 2);
	}
}
