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

#define FILE_BUFFER_SIZE    (1*1024*1024)

typedef enum {
    FILE_READ,
    FILE_WRITE
} filetype_t;

typedef struct _file_t {
    void        *context;
    int         fd;
    char        *current;
    int         readbytes;
    char        buffer[FILE_BUFFER_SIZE];
    filetype_t  type;
} file_t;


bool file_open(const char *filename, filetype_t type, file_t *file);

bool file_read(file_t *file, char *buf, size_t buf_size);

bool file_close(const file_t *file);

#endif // _FILE_UTILS_H_

