/******************************************************************************
 *
 * File: str_utils.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#include "str_utils.h"

bool str_get_line(char *buf, size_t size, char *fields[], char **next_line)
{
    int i = 0, field_index = 0;

    if (!buf || !fields || !next_line) return false;

    fields[field_index++] = buf;

    while (i<size && buf[i]) {

        if (',' == buf[i]) {
            buf[i] = '\0';
            fields[field_index++] = buf + 1;
        } else if ('\n' == buf[i]) {
            buf[i] = '\0';
            *next_line = buf + 1;
            break;
        }

        buf++;
    }
}
