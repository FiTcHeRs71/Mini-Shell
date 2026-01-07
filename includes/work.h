#ifndef WORK_H
# define WORK_H

extern int	g_signal;


void	handle_sigint(int sig);
void	update_signal(t_shell *shell);
void	init_signal();
void	print_env(t_shell *shell);

#endif


