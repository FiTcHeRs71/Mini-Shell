
#include "../../includes/minishell.h"

int	exec_echo(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		ft_printf("\n");
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
		i = 2;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])))
		ft_printf("\n");
	return (0);
}
