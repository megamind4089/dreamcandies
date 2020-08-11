/******************************************************************************
 *
 * File: str_utils.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#include "str_utils.h"
#include <assert.h>

bool str_extract_line_fields(buffer_t *buf, char *fields[])
{
    int field_index = 0, delim_index = 0;
    char *delimiters[STR_MAX_FIELDS] = {0};

    if (!buf || !buf->len || !fields)
        return false;

    fields[field_index++] = buf->current;

    for (int i = 0; i < buf->len; i++) {
        char ch = buf->current[i];

        if (',' == ch) {
            delimiters[delim_index++] = &buf->current[i];
            fields[field_index++] = &buf->current[i + 1];
        } else if ('\n' == ch || '\0' == ch) {
            buf->current[i] = '\0';

            // Add Null terminator for fields
            for (int j = 0; j < STR_MAX_FIELDS; j++) {
                if (!delimiters[j]) break;
                *delimiters[j] = '\0';
            }
            if (i < buf->len) {
                buffer_move(buf, i+1);
            }
            return true;
        }
    }

    memset(fields, 0, sizeof(char *) * STR_MAX_FIELDS);
    return false;
}

bool str_extract_field(char *dest, const char *src)
{
    if (!src || !dest) return false;
    assert(src[0] == '"' || src[0] == '“');

    src++;
    while('"' != *src && '“' != *src) {
        *dest++ = *src++;
    }
}
