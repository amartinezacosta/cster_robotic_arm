#ifndef BSP_TM4C123_RINGBUFFER_H
#define BSP_TM4C123_RINGBUFFER_H

#include <stdint.h>

typedef struct
{
  volatile uint32_t head;
  volatile uint32_t tail;
  uint8_t *buffer;
  uint32_t size;
}ringbuffer_t;

void ringbuffer_ctor(ringbuffer_t * const me,
                     uint8_t * const buffer,
                     uint32_t const size );
uint32_t ringbuffer_push(ringbuffer_t * const me,
                     uint8_t const * const data,
                     uint32_t const size);
uint32_t ringbuffer_pop(ringbuffer_t * const me,
                        uint8_t * const data,
                        uint32_t const size);
uint32_t ringbuffer_full(ringbuffer_t * const me);
uint32_t ringbuffer_empty(ringbuffer_t * const me);
uint32_t ringbuffer_available(ringbuffer_t * const me);
uint32_t ringbuffer_space(ringbuffer_t * const me);

#endif
