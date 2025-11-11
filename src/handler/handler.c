#include "../../includes/minishell.h"

void    init_handler(struct sigaction control_c)
{
    control_c.sa_handler = handle_c;
	sigemptyset(&control_c.sa_mask);
	control_c.sa_flags = 0;
	sigaction(SIGINT, &control_c, NULL);
    control_c.sa_handler = SIG_IGN;
    sigemptyset(&control_c.sa_mask);
    control_c.sa_flags = 0;
    sigaction(SIGQUIT, &control_c, NULL);
}

void    handle_c(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay(); 
}