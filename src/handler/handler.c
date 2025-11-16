#include "../../includes/minishell.h"

int g_sig = 0;

void    handle_c(int sig)
{
    (void)sig;
    g_sig = 1;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay(); 
}

void    init_sig(void)
{
    struct sigaction sig;

	sig.sa_handler = handle_c;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig, NULL);
    sig.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sig, NULL);
}