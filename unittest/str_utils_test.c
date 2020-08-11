/******************************************************************************
 *
 * File: str_utils_test.c
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/
#include "str_utils.h"
#include "stdio.h"

char buf[100] = "This,is,madness\nThis,is,SPARTANS\n";

int main()
{
    char *fields[STR_MAX_FIELDS] = {0}, *next_line = NULL;

    if (!str_get_line(buf, strlen(buf), fields, &next_line)) {
        printf("Get line failed\n");
        return -1;
    }

    for (int i=0; i < STR_MAX_FIELDS; i++) {
        if (!fields[i]) {
            break;
        }
        printf("%s\n", fields[i]);
    }
    printf("%s", next_line);

    return 0;
}
