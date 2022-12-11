#include <bsp_tm4c123_ringbuffer.h>
#include <TM4C123.h>

void ringbuffer_ctor(ringbuffer_t * const me,
                     uint8_t * const buffer,
                     uint32_t const size)
{
  me->buffer = buffer;
  me->size = size;
  me->head = 0;
  me->tail = 0;
}

uint32_t ringbuffer_push(ringbuffer_t * const me,
                     uint8_t const * const data,
                     uint32_t const size)
{
  uint32_t n = 0;
  for(; n < size; n++)
  {
    if(ringbuffer_full(me)) break;

    uint32_t head = me->head;
    me->buffer[head] = data[n];

    head = (head + 1) % me->size;

    __disable_irq();
    me->head = head;
    __enable_irq();
  }

  return n;
}

uint32_t ringbuffer_pop(ringbuffer_t * const me,
                        uint8_t * const data,
                        uint32_t const size)
{
  uint32_t n = 0;
  for(; n < size; n++)
  {
    if(ringbuffer_empty(me)) break;

    uint32_t tail = me->tail;
    data[n] = me->buffer[tail];

    tail = (tail + 1) % me->size;

    __disable_irq();
    me->tail = tail;
    __enable_irq();
  }

  return n;
}

uint32_t ringbuffer_full(ringbuffer_t * const me)
{
  uint32_t head = me->head;
  uint32_t tail = me->tail;

  return ((((head + 1) % me->size) == tail) ? 1 : 0);
}

uint32_t ringbuffer_empty(ringbuffer_t * const me)
{
  uint32_t head = me->head;
  uint32_t tail = me->tail;

  return ((head == tail) ? 1 : 0);
}

uint32_t ringbuffer_available(ringbuffer_t * const me)
{
  uint32_t head = me->head;
  uint32_t tail = me->tail;

  return ((head >= tail) ? (head - tail) :
          (me->size - (tail - head)));
}

uint32_t ringbuffer_space(ringbuffer_t * const me)
{
  return (me->size - ringbuffer_available(me));
}
