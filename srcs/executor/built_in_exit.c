
#include "../../includes/minishell.h"

void	exec_exit(t_shell *shell, char **args)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	if (args[1]) // TODO : Comment il enegriste avec les quotes et simple quotes ?
	{
		while(args[1][i])
		{
			if (ft_isdigit(args[1][i]))
				break ;
			i++;

		}
		if ((args[1][i]) == '\0')
			exit_code = ft_atoi(args[1]);
	}
	else
	{
		exit_code = shell->last_exit_status;
	}
	clean_before_exit(shell);
	exit(exit_code);
}
