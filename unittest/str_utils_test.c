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
    char *line = NULL, *field = NULL;

    assert(buffer_init(&buf, 1024));
    assert(buffer_copy(&buf, text, strlen(text)));

    assert(str_extract_line_fields(&buf, fields));
    // for (int i=0; i < STR_MAX_FIELDS; i++) {
    //     if (!fields[i]) {
    //         break;
    //     }
    //     printf("%s\n", fields[i]);
    // }
    assert(!strcmp(fields[0],"This"));
    assert(!strcmp(fields[1],"is"));
    assert(!strcmp(fields[2],"madness"));
    assert(fields[3]==NULL);

    int placeholder = buf.len;

    memset(fields, 0, sizeof(fields));
    buf.len = 10;
    assert(!str_extract_line_fields(&buf, fields));

    memset(fields, 0, sizeof(fields));
    buf.len = placeholder;
    assert(str_extract_line_fields(&buf, fields));
    assert(!strcmp(fields[0],"No"));
    assert(!strcmp(fields[1],"This"));
    assert(!strcmp(fields[2],"is"));
    assert(!strcmp(fields[3],"SPARTANS"));
    assert(fields[4]==NULL);

    assert(buffer_clear(&buf));
    assert(buffer_copy(&buf, text, strlen(text)));
    assert(str_extract_line_field(&buf, 2, &line, &field));
    assert(!strcmp(line, "This,is,madness"));
    assert(!strcmp(field, "is"));
    free(field); field = NULL;
    assert(str_extract_line_field(&buf, 4, &line, &field));
    assert(!strcmp(line, "No,This,is,SPARTANS"));
    assert(!strcmp(field, "SPARTANS"));
    free(field); field = NULL;

    assert(buffer_free(&buf));

    printf("Str utils: PASSED\n");

    return 0;
}
