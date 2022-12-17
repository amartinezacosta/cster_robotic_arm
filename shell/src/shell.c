#include <FreeRTOS.h>
#include <task.h>

#include <shell.h>
#include <string.h>

#define IS_SPACE(c)   (c == ' ')
#define EOS(c)        (c == 0)
#define IS_ALPHA(c)   (((c > 64) && (c < 91)) || ((c > 96) && (c < 123)))
#define IS_NUMERIC(c) ((c > 47) && (c < 58))

static char gTokens[TOKEN_MAX_COUNT][TOKEN_MAX_SIZE];

uint32_t shell_tokenize(char const * str);

void shell_ctor(shell_t * const me,
                uint32_t(*write)(uint8_t const *, uint32_t const),
                uint32_t(*read)(uint8_t *, uint32_t const))
{
  for(uint32_t i = 0; i < SHELL_MAX_CMDS; i++)
  {
    shell_cmd_t *cmd_list = &me->cmds[i];
    cmd_list->cmd = 0;
    cmd_list->cmd_callback = 0;
    cmd_list->help = 0;
  }

  me->write = write;
  me->read = read;
  me->size = 0;
}

uint32_t shell_register(shell_t *const me,
                        char const * const cmd,
                        uint32_t(*callback)(uint32_t,pToken_t),
                        char const * const help)
{
  uint32_t result;
  uint32_t size = me->size;

  if(size < SHELL_MAX_CMDS)
  {
    shell_cmd_t *new_cmd = &me->cmds[size + 1];
    new_cmd->cmd = cmd;
    new_cmd->cmd_callback = callback;
    new_cmd->help = help;

    result = SHELL_COMMAND_ADDED;
  }
  else
  {
    result = SHELL_COMMAND_NOT_ADDED;
  }

  return result;
}

void shell_prompt(shell_t * const me)
{
  char *str = "\x1B[32mshell:~$ \x1B[37m";
  me->write((uint8_t*)str, strlen(str));
}

uint32_t shell_gets(shell_t * const me, char *str, uint32_t size)
{
  char c;
  uint32_t n = 0;

  for( ;; )
  {
    if(me->read((uint8_t*)&c, 1))
    {
      if((c == '\n') || (c == '\r'))
      {
        str[n] = 0;
        me->write((uint8_t*)"\n", 1);
        me->write((uint8_t*)"\r", 1);

        break;
      }
      else if(c == '\b')
      {
        str[--n] = 0;
      }
      else
      {
        str[n++] = c;
      }

      /*Echo back character*/
      me->write((uint8_t*)&c, 1);
    }

    /*Delay or yield?*/
    vTaskDelay(67 / portTICK_PERIOD_MS);
  }

  return n;
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
    char *cmd_str = &gTokens[0][0];

    for(uint32_t i = 0; i < me->size; i++)
    {
      shell_cmd_t *cmd_list = &me->cmds[i];
      if(strcmp(cmd_str, cmd_list->cmd) == 0)
      {
        result = cmd_list->cmd_callback(tokens_found, gTokens);
        break;
      }
    }
  }
  else
  {
    result = SHELL_NO_TOKENS_FOUND;
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
        gTokens[token_count][token_index++] = *str++;
      }
    }

    if(token_count < TOKEN_MAX_COUNT)
    {
      gTokens[token_count][token_index] = 0;
      token_index = 0;
      token_count++;
    }
    else
    {
      token_count = 0;
      break;
    }
  }

  return token_count;
}

void shell_print_result(shell_t * const me, uint32_t result)
{
  switch(result)
  {
  case SHELL_OK:
    me->write((uint8_t*)"shell OK\r\n", 10);
    break;
  case SHELL_NO_TOKENS_FOUND:
    me->write((uint8_t*)"shell no tokens found\r\n", 23);
    break;
  case SHELL_CMD_NOT_FOUND:
    me->write((uint8_t*)"shell command not found\r\n", 25);
    break;
  case SHELL_ERROR:
    me->write((uint8_t*)"shell error\r\n", 13);
    break;
  default:
    me->write((uint8_t*)"shell invalid result\r\n", 22);
    break;
  }
}
