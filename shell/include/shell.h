#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

/*Shell configuration parameters*/
#define TOKEN_MAX_COUNT   10
#define TOKEN_MAX_SIZE    12
#define SHELL_MAX_CMDS    20

/*Shell return values*/
#define SHELL_OK                  0
#define SHELL_NO_TOKENS_FOUND     1
#define SHELL_COMMAND_ADDED       2
#define SHELL_COMMAND_NOT_ADDED   3
#define SHELL_CMD_NOT_FOUND       4
#define SHELL_ERROR               5

typedef char(*pToken_t)[TOKEN_MAX_SIZE];

typedef struct
{
  char const *cmd;
  uint32_t (*cmd_callback)(uint32_t, pToken_t);
  char const *help;
}shell_cmd_t;

typedef struct
{
  shell_cmd_t cmds[SHELL_MAX_CMDS];
  uint32_t(*write)(uint8_t const *, uint32_t const);
  uint32_t(*read)(uint8_t *, uint32_t const);
  uint32_t size;
}shell_t;

void shell_ctor(shell_t * const me,
                uint32_t(*write)(uint8_t const *, uint32_t const),
                uint32_t(*read)(uint8_t *, uint32_t const));
uint32_t shell_register(shell_t *const me,
                        char const * const cmd,
                        uint32_t(*callback)(uint32_t,pToken_t),
                        char const * const help);
void shell_prompt(shell_t * const me);
uint32_t shell_gets(shell_t * const me,
                    char *str,
                    uint32_t size);
uint32_t shell_run(shell_t * const me,
                   char const * const str);
void shell_print_result(shell_t * const me,
                        uint32_t result);

#endif
