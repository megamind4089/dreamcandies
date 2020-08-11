/******************************************************************************
 *
 * File: file_utils.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#include "file_utils.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

bool file_open(const char *filename,
               filetype_t type, file_t *file)
{
    int fd;
    int flags = O_CLOEXEC | O_NONBLOCK;

    if (!file || !filename) {
        return false;
    }
    memset(file, 0, sizeof(file_t));

    if (type == FILE_READ) {
        flags |= O_RDONLY;
    } else {
        flags |= O_CREAT;
        flags |= O_WRONLY;
    }

    fd = open(filename, flags);
    if (-1 == fd) {
        fprintf(stderr, "\nError opend file\n");
        return false;
    }

    file->fd = fd;
    file->current = NULL;
    file->type = type;

    return true;
}

bool file_close(const file_t *file)
{
    if (!file) {
        return false;
    }
    close(file->fd);
    return true;
}

bool file_read(file_t *file, buffer_t *buf, size_t size)
{
    int bytes_read = 0;
    if (file->type == FILE_WRITE)
        return false;

    if (buf->remaining < size)
        return false;

    bytes_read = read(file->fd, buf->current + buf->len, size);
    if (-1 == bytes_read) {
        fprintf(stderr, "File read error\n");
        return false;
    }
    if (0 == bytes_read) {
        return false;
    }
    buf->remaining -= bytes_read;
    buf->len += bytes_read;
    return true;
}


