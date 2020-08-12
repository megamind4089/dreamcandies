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

#define BUFFER_SIZE     (1024*1024)

char    shortlisted[NUM_SHORTLISTED][CODE_SIZE] = {0};
buffer_t    buffer, out_buffer;

bool generate_shortlisted_customers()
{
    file_t file;
    char *fields[STR_MAX_FIELDS];
    int sample_index = 0;

    if (!file_open(sample_file, FILE_READ, &file)) {
        fprintf(stderr, "\nCustomer file not found\n");
        return false;
    }

    if (!file_read(&file, &buffer, buffer.remaining)) {
        fprintf(stderr, "\nFile open failed\n");
        return false;
    }

    // SKIP the header in first line
    if (!str_extract_line_fields(&buffer, fields)) {
        printf("Extracting header failed\n");
        return false;
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

    return true;
}

bool extract_customer_details()
{
    file_t file;
    const int customer_code_index = 1;
    int sample_index = 0;
    size_t len;

    if (!file_open(customer_file, FILE_READ, &file)) {
        fprintf(stderr, "\nCustomer file not found\n");
        return false;
    }

    if (!file_read(&file, &buffer, buffer.remaining)) {
        fprintf(stderr, "\nFile open failed\n");
        return false;
    }

    // SKIP the header in first line
    char *line = NULL, *field = NULL;
    if (!str_extract_line_field(&buffer, customer_code_index, &line, &field)) {
        printf("Extracting header failed\n");
        return false;
    }

    while (true) {
        char *line = NULL, *field = NULL;
        if (!str_extract_line_field(&buffer, customer_code_index, &line, &field)) {
            buffer_realign(&buffer);
            if (!file_read(&file, &buffer, buffer.remaining)) {
                break;
            }
            continue;
        }
        // TODO: Fix the strlen calling
        if (!strncmp(shortlisted[sample_index], &field[1], strlen(field)-2)) {
            printf("%s\n", line);
            sample_index++;
        }
    }

    return true;
}

int main()
{
    if (!buffer_init(&buffer, BUFFER_SIZE)) {
        fprintf(stderr, "Buffer init failed\n");
        return -1;
    }

    if (!buffer_init(&out_buffer, BUFFER_SIZE)) {
        fprintf(stderr, "Buffer init failed\n");
        return -1;
    }

    if (!generate_shortlisted_customers()) {
        fprintf(stderr, "Generating shortlist customers failed\n");
        return -1;
    }

    if (!extract_customer_details()) {
        fprintf(stderr, "Generating shortlist customers failed\n");
        return -1;
    }

    buffer_free(&buffer);
    buffer_free(&out_buffer);
    return 0;
}
