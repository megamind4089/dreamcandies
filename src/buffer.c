/******************************************************************************
 *
 * File: buffer.c
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#include "buffer.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

bool buffer_init(buffer_t *buf, size_t size)
{
    if(!buf) return false;

    buf->buffer = calloc(sizeof(char), size);
    if (!buf->buffer) {
        fprintf(stderr, "Not enough memory");
        assert(0);
        return false;
    }

    buf->size = size;

    buf->current = buf->buffer;
    buf->remaining = size;
    buf->len = 0;
    return true;
}

bool buffer_free(buffer_t *buf)
{
    if(!buf) return false;

    free(buf->buffer);
    memset(buf, 0, sizeof(buffer_t));
    return true;
}

bool buffer_clear(buffer_t *buf)
{
    if(!buf) return false;

    memset(buf->buffer, 0, buf->size);
    buf->current = buf->buffer;
    buf->remaining = buf->size;
    buf->len = 0;

    return true;
}

bool buffer_move(buffer_t *buf, size_t size)
{
    if (!buf) return false;

    if (buf->len < size) return false;

    buf->current += size;
    buf->len -= size;

    return true;
}

bool buffer_copy(buffer_t *buf, char *ptr, size_t size)
{
    if (!buf) return false;

    if (buf->remaining < size) return false;

    memcpy(&buf->current[buf->len], ptr, size);
    buf->len += size;
    buf->remaining -= size;

    return true;
}

bool buffer_realign(buffer_t *buf)
{
    if (!buf) return false;

    if (buf->current == buf->buffer) return true;

    memmove(buf->buffer, buf->current, buf->len);
    buf->current = buf->buffer;
    memset(buf->current + buf->len, 0, buf->size - buf->len);
    buf->remaining = buf->size - buf->len;

    return true;
}
