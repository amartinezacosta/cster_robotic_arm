#include <shell.h>
#include <string.h>

#define TOKEN_MAX_COUNT   10
#define TOKEN_MAX_SIZE    12

#define IS_SPACE(c)   (c == ' ')
#define EOS(c)        (c == 0)
#define IS_ALPHA(c)   (((c > 64) && (c < 91)) || ((c > 96) && (c < 123)))
#define IS_NUMERIC(c) ((c > 47) && (c < 58))

static char tokens[TOKEN_MAX_COUNT][TOKEN_MAX_SIZE];

uint32_t shell_tokenize(char const * str);

void shell_ctor(shell_t * const me)
{
  me->count = 0;
}

uint32_t shell_register(shell_t *const me,
                        shell_cmd_t *cmd)
{
  if(me->count < SHELL_MAX_CMDS)
  {
    me->cmds[me->count++] = *cmd;
  }

  return 0;
}

/*shell command should use the following syntax:
 * cmd [options] [arguments]
 * example:
 * motor -i 0 -m 1023*/
uint32_t shell_run(shell_t * const me, char const * str)
{
  uint32_t result = 0;
  /*Tokenize string*/
  uint32_t tokens_found = shell_tokenize(str);

  if(tokens_found)
  {
    char *cmd = &tokens[0][0];

    for(uint32_t i = 0; i < me->count; i++)
    {
      if(strcmp(cmd, me->cmds[i].cmd) == 0)
      {
        result = me->cmds[i].cmd_callback(tokens_found, (char**)tokens);
        break;
      }
    }
  }

  return result;
}

uint32_t shell_tokenize(char const * str)
{
  /*Tokenize string*/
  uint32_t token_index = 0;
  uint32_t token_count = 0;
  while(!EOS(*str))
  {
    /*Skip all whitespace*/
    while(IS_SPACE(*str)) str++;

    /*Save token*/
    while((!IS_SPACE(*str)) && (!EOS(*str)))
    {
      if(token_index < TOKEN_MAX_SIZE)
      {
        tokens[token_count][token_index++] = *str++;
      }
    }

    if(token_count < TOKEN_MAX_COUNT)
    {
      tokens[token_count][token_index] = 0;
      token_index = 0;
      token_count++;
    }
  }

  return token_count;
}
