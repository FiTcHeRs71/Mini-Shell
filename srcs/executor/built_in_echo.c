
#include "../../includes/minishell.h"

void	exec_echo(char **args)
{
	int	i;

	if (!args)
		return ;
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])))
	{
		i = 2;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			i++;
		}
		return ;
	}
	else if (args[1])
	{
		i = 1;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			i++;
		}
		ft_printf("\n");
		return ;
	}
}
