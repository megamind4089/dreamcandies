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
    int flags = O_CLOEXEC;
    mode_t mode = 0;

    if (!file || !filename) {
        return false;
    }
    memset(file, 0, sizeof(file_t));

    if (type == FILE_READ) {
        flags |= O_RDONLY;
    } else {
        flags |= O_CREAT;
        flags |= O_WRONLY;
        flags |= O_TRUNC;
        mode = S_IRWXU;
    }

    fd = open(filename, flags, mode);
    if (-1 == fd) {
        perror("Error: ");
        return false;
    }

    file->fd = fd;
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
        perror("Error: ");
        return false;
    }
    if (0 == bytes_read) {
        return false;
    }
    buf->remaining -= bytes_read;
    buf->len += bytes_read;
    return true;
}

bool file_write(file_t *file, buffer_t *buf)
{
    int ret;
    size_t bytes_write = 0;
    if (file->type == FILE_READ)
        return false;

    if (!buf->len)
        return true;

    while (bytes_write < buf->len) {
        ret = write(file->fd, buf->current + bytes_write, buf->len - bytes_write);
        if (-1 == ret) {
            fprintf(stderr, "File read error\n");
            return false;
        }
        if (0 == ret) {
            fprintf(stderr, "File read ZERO\n");
            return false;
        }
        bytes_write += ret;
    }
    buffer_clear(buf);
    return true;
}

