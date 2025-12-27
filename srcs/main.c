
#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell > ");
		if(!line)
			ft_printf("Exit\n");
		if(line)
			ft_printf("%s", line);
		free(line);
	}
	return (0);
}