#ifndef HANDLER_H
# define HANDLER_H

void    handle_c(int sig);
void    init_handler(struct sigaction control_c);

#endif