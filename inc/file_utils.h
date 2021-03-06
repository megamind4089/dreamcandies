/******************************************************************************
 *
 * File: file_utils.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include <stdbool.h>
#include <stddef.h>
#include "main.h"
#include "buffer.h"

#define FILE_BUFFER_SIZE    (1*1024*1024)

typedef enum {
    FILE_READ,
    FILE_WRITE
} filetype_t;

typedef struct _file_t {
    int         fd;
    filetype_t  type;
} file_t;


bool file_open(const char *filename, filetype_t type, file_t *file);

bool file_read(file_t *file, buffer_t *buf, size_t size);

bool file_write(file_t *file, buffer_t *buf);

bool file_close(const file_t *file);

#endif // _FILE_UTILS_H_

