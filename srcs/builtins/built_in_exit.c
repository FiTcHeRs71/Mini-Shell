
#include "../../includes/minishell.h"

int	exec_exit(t_shell *shell, char **args)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	if (array_calculator(args) > 2)
		return (ft_putstr_fd_checked("exit : too many arguments\n", 2), 1);
	if (args[1])
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]) || i > 10)
			{
				exit_code = 2;
				break ;
			}
			i++;
		}
		if ((args[1][i]) == '\0')
			exit_code = ft_atoi(args[1]);
	}
	else
		exit_code = shell->last_exit_status;
	clean_without_exit(shell);
	exit(exit_code % 256);
}
