#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

#define SHELL_MAX_CMDS    20

typedef struct
{
  char *cmd;
  uint32_t (*cmd_callback)(uint32_t,char**);
  char const * help;
}shell_cmd_t;

typedef struct
{
  shell_cmd_t cmds[SHELL_MAX_CMDS];
  uint32_t count;
}shell_t;

void shell_ctor(shell_t * const me);
uint32_t shell_register(shell_t *const me,
                        shell_cmd_t *cmd);
uint32_t shell_run(shell_t * const me,
                   char const * const str);

#endif
