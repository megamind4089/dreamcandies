/******************************************************************************
 *
 * File: str_utils_test.c
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/
#include "str_utils.h"
#include "stdio.h"
#include "assert.h"

char buffer[100] = "This,is,madness\nNo,This,is,SPARTANS\n";

int main()
{
    buffer_t buf;
    char *fields[STR_MAX_FIELDS] = {0};

    assert(buffer_init(&buf, 1024));
    assert(buffer_copy(&buf, buffer, strlen(buffer)));

    assert(str_extract_line_fields(&buf, fields));
    for (int i=0; i < STR_MAX_FIELDS; i++) {
        if (!fields[i]) {
            break;
        }
        printf("%s\n", fields[i]);
    }

    int placeholder = buf.len;

    memset(fields, 0, sizeof(fields));
    buf.len = 10;
    assert(!str_extract_line_fields(&buf, fields));

    memset(fields, 0, sizeof(fields));
    buf.len = placeholder;
    assert(str_extract_line_fields(&buf, fields));
    for (int i=0; i < STR_MAX_FIELDS; i++) {
        if (!fields[i]) {
            break;
        }
        printf("%s\n", fields[i]);
    }

    assert(buffer_free(&buf));
    return 0;
}
