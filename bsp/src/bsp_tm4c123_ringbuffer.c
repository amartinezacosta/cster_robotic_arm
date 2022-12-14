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
                     uint8_t const c)
{
  uint32_t result;
  uint32_t head = me->head + 1;

  if(head == me->size)
  {
    head = 0;
  }

  if(head != me->tail)
  {
    me->buffer[me->head] = c;
    me->head = head;

    result = RINGBUFFER_PUSHED;
  }
  else
  {
    result = RINGBUFFER_NOT_PUSHED;
  }

  return result;
}

uint32_t ringbuffer_pop(ringbuffer_t * const me,
                        uint8_t * c)
{
  uint32_t result;
  uint32_t tail = me->tail;

  if(me->head != tail)
  {
    *c = me->buffer[tail];
    ++tail;
    if(tail == me->size)
    {
      tail = 0;
    }
    me->tail = tail;

    result = RINGBUFFER_POPPED;
  }
  else
  {
    result = RINGBUFFER_NOT_POPPED;
  }

  return result;
}

uint32_t ringbuffer_free(ringbuffer_t * const me)
{
  uint32_t head = me->head;
  uint32_t tail = me->tail;
  uint32_t free;

  if(head == tail)
  {
    free = me->size - 1;
  }
  else if(head < tail)
  {
    free = tail - head - 1;
  }
  else
  {
    free = me->size + tail - head - 1;
  }

  return free;
}

uint32_t ringbuffer_available(ringbuffer_t * const me)
{
  uint32_t head = me->head;
  uint32_t tail = me->tail;
  uint32_t available;

  if(head >= tail)
  {
    available = head - tail;
  }
  else
  {
    available = me->size - (tail - head);
  }

  return available;
}
