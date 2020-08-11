/******************************************************************************
 *
 * File: file_utils_test.c
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "file_utils.h"

int main()
{
    file_t file;

    if (!file_open("./test/customer.csv", FILE_READ, &file)) {
        fprintf(stderr, "\nFile open failed\n");
        return -1;
    }

    char buf[50] = {0};
    if (!file_read(&file, buf, sizeof(buf))) {
        fprintf(stderr, "\nFile open failed\n");
        return -1;
    }
    for (int i=0; i<50; i++) printf("%c", buf[i]);
    printf("\n\n");

    memset(buf, 0, sizeof buf);
    if (!file_read(&file, buf, sizeof(buf))) {
        fprintf(stderr, "\nFile open failed\n");
        return -1;
    }
    for (int i=0; i<50; i++) printf("%c", buf[i]);
    printf("\n\n");

    memset(buf, 0, sizeof buf);
    if (!file_read(&file, buf, sizeof(buf))) {
        fprintf(stderr, "\nFile open failed\n");
        return -1;
    }
    for (int i=0; i<50; i++) printf("%c", buf[i]);
    printf("\n\n");

    file_close(&file);
    return 0;
}

