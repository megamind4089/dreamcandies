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

bool file_open(const char *filename, filetype_t type, file_t *file)
{
    int fd;

    if (!file || !filename) {
        return false;
    }
    memset(file, 0, sizeof(file_t));

    fd = open(filename, O_RDONLY | O_CREAT);
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

bool file_read(file_t *file, char *buf, size_t buf_size)
{
    int read_bytes = 0;

    if (file->type == FILE_WRITE)
        return false;

    read_bytes = read(file->fd, buf, buf_size);
    file->readbytes += read_bytes;
    return true;
}


