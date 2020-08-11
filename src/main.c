/******************************************************************************
 *
 * File: main.c
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#include "main.h"
#include "file_utils.h"
#include "str_utils.h"
#include "buffer.h"

static const char customer_file[] = "./test/customer.csv";
static const char invoice_file[] = "./test/invoice.csv";
static const char invoice_item_file[] = "./test/invoice_item.csv";
static const char sample_file[] = "./test/sample.csv";

#define BUFFER_SIZE     (20)

char    shortlisted[NUM_SHORTLISTED][CODE_SIZE] = {0};
buffer_t    buffer;

int main()
{
    file_t file;
    char *fields[STR_MAX_FIELDS];
    int sample_index = 0;

    if (!buffer_init(&buffer, BUFFER_SIZE)) {
        fprintf(stderr, "Buffer init failed\n");
        return -1;
    }

    if (!file_open(sample_file, FILE_READ, &file)) {
        fprintf(stderr, "\nCustomer file not found\n");
        return -1;
    }

    if (!file_read(&file, &buffer, buffer.remaining)) {
        fprintf(stderr, "\nFile open failed\n");
        return -1;
    }

    // SKIP the header in first line
    if (!str_extract_line_fields(&buffer, fields)) {
        printf("Extracting header failed\n");
        return -1;
    }

    while (true) {
        memset(fields, 0, sizeof(fields));
        if (!str_extract_line_fields(&buffer, fields)) {
            buffer_realign(&buffer);
            if (!file_read(&file, &buffer, buffer.remaining)) {
                break;
            }
            continue;
        }

        if (!fields[0]) {
            fprintf(stderr, "Error parsing the sample file\n");
            break;
        }
        str_extract_field(shortlisted[sample_index++], fields[0]);

    }

    for (int i = 0; i < NUM_SHORTLISTED; i++) {
        if (shortlisted[i][0] == '\0') break;
        printf("%s\n", shortlisted[i]);
    }

    buffer_free(&buffer);

    return 0;
}

