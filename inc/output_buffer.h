/******************************************************************************
 *
 * File: output_buffer.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _OUTPUT_BUFFER_H_
#define _OUTPUT_BUFFER_H_

#include "main.h"
#include "buffer.h"
#include <stdbool.h>

typedef struct _output_buffer_t {
    char    *buffer;
    size_t  size;
    char    *current;
    size_t  len;
    size_t  remaining;
} output_buffer_t;

bool output_buffer_init(buffer_t *, size_t);

bool output_buffer_free(buffer_t *);

#endif // _OUTPUT_BUFFER_H_


