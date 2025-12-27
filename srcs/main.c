
#include "../includes/minishell.h"

int main(void)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell > ");
		if(!line)
		{
			ft_printf("Exit\n");
			free(line);
			break;
		}
		if(line)
			ft_printf("%s\n", line);
		free(line);
	}
	return (0);
}