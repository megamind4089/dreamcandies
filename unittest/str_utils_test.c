/******************************************************************************
 *
 * File: str_utils_test.c
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/
#include "str_utils.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

char *text = "This,is,madness\nNo,This,is,SPARTANS\n";

int main()
{
    buffer_t buf;
    char *fields[STR_MAX_FIELDS] = {0};
    size_t line_len = 0, fields_len[STR_MAX_FIELDS] = {0};
    char *line = NULL, *field = NULL;

    assert(buffer_init(&buf, 1024));
    assert(buffer_copy(&buf, text, strlen(text)));

    assert(str_extract_line_fields_old(&buf, fields));
    assert(!strcmp(fields[0],"This"));
    assert(!strcmp(fields[1],"is"));
    assert(!strcmp(fields[2],"madness"));
    assert(fields[3]==NULL);

    int placeholder = buf.len;

    memset(fields, 0, sizeof(fields));
    buf.len = 10;
    assert(!str_extract_line_fields_old(&buf, fields));

    memset(fields, 0, sizeof(fields));
    buf.len = placeholder;
    assert(str_extract_line_fields_old(&buf, fields));
    assert(!strcmp(fields[0],"No"));
    assert(!strcmp(fields[1],"This"));
    assert(!strcmp(fields[2],"is"));
    assert(!strcmp(fields[3],"SPARTANS"));
    assert(fields[4]==NULL);

    assert(buffer_clear(&buf));
    memset(fields, 0, sizeof(fields));
    memset(fields_len, 0, sizeof(fields_len));
    assert(buffer_copy(&buf, text, strlen(text)));
    assert(str_extract_line_fields(&buf, &line, &line_len, fields, fields_len));
    assert(!strncmp(line, "This,is,madness", line_len));
    assert(!strncmp(fields[0], "This", fields_len[0]));
    assert(fields_len[0]==strlen("This"));
    assert(!strncmp(fields[1], "is", fields_len[1]));
    assert(fields_len[1]==strlen("is"));
    assert(!strncmp(fields[2], "madness", fields_len[2]));
    assert(fields_len[2]==strlen("madness"));
    assert(fields[3]==NULL);
    assert(str_extract_line_fields(&buf, &line, &line_len, fields, fields_len));
    assert(!strncmp(line, "No,This,is,SPARTANS", line_len));
    assert(!strncmp(fields[0], "No", fields_len[0]));
    assert(!strncmp(fields[1], "This", fields_len[1]));
    assert(!strncmp(fields[2], "is", fields_len[2]));
    assert(!strncmp(fields[3], "SPARTANS", fields_len[3]));
    assert(fields[4]==NULL);

    assert(buffer_free(&buf));

    printf("Str utils: PASSED\n");

    return 0;
}
