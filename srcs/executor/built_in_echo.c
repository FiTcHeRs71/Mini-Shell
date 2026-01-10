
#include "../../includes/minishell.h"

int	exec_echo(char **args)
{
	int	i;

	if (!args)
		ft_printf("\n");
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])))
	{
		i = 2;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			i++;
		}
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
	}
	return (0);
}
