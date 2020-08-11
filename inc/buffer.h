/******************************************************************************
 *
 * File: buffer.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "main.h"
#include "stdbool.h"

typedef struct _buffer_t {
    char    *buffer;
    size_t  size;
    char    *current;
    size_t  len;
    size_t  remaining;
} buffer_t;

bool buffer_init(buffer_t *, size_t);

bool buffer_clear(buffer_t *);

bool buffer_free(buffer_t *);

bool buffer_move(buffer_t *, size_t);

bool buffer_copy(buffer_t *, char *, size_t);

bool buffer_realign(buffer_t *buf);

#endif // _BUFFER_H_

