#ifndef BSP_TM4C123_RINGBUFFER_H
#define BSP_TM4C123_RINGBUFFER_H

#include <stdint.h>

#define RINGBUFFER_EMPTY        0
#define RINGBUFFER_FULL         1
#define RINGBUFFER_PUSHED       2
#define RINGBUFFER_NOT_PUSHED   3
#define RINGBUFFER_POPPED       4
#define RINGBUFFER_NOT_POPPED   5

typedef struct
{
  uint32_t volatile head;
  uint32_t volatile tail;
  uint8_t* buffer;
  uint32_t size;
}ringbuffer_t;

void ringbuffer_ctor(ringbuffer_t * const me,
                     uint8_t * const buffer,
                     uint32_t const size);
uint32_t ringbuffer_push(ringbuffer_t * const me,
                     uint8_t const c);
uint32_t ringbuffer_pop(ringbuffer_t * const me,
                        uint8_t * c);
uint32_t ringbuffer_free(ringbuffer_t * const me);
uint32_t ringbuffer_available(ringbuffer_t * const me);

#endif
