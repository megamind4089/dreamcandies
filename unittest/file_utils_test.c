/******************************************************************************
 *
 * File: file_utils_test.c
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "file_utils.h"
#include "buffer.h"

int main()
{
    file_t file;
    buffer_t    buf;

    assert(buffer_init(&buf, 1024));
    assert(file_open("./test/customer.csv", FILE_READ, &file));

    assert(file_read(&file, &buf, 50));
    for (int i=0; i<50; i++) printf("%c", buf.current[i]);

    assert(buffer_move(&buf, 50));
    assert(file_read(&file, &buf, 50));
    for (int i=0; i<50; i++) printf("%c", buf.current[i]);

    assert(buffer_move(&buf, 50));
    assert(file_read(&file, &buf, 50));
    for (int i=0; i<50; i++) printf("%c", buf.current[i]);

    assert(buffer_free(&buf));

    file_close(&file);
    return 0;
}

