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

static const char customer_file[] = "./testdata/customer.csv";
static const char invoice_file[] = "./testdata/invoice.csv";
static const char invoice_item_file[] = "./testdata/invoice_item.csv";
static const char sample_file[] = "testdata/sample.csv";

static const char o_customer_file[] = "./output/customer.csv";
static const char o_invoice_file[] = "./output/invoice.csv";
static const char o_invoice_item_file[] = "./output/invoice_item.csv";

#define BUFFER_SIZE     (1*1024*1024)

static const char NEWLINE[] = "\n";
static char sample_customers[NUM_SHORTLISTED][CODE_SIZE] = {0};
static buffer_t    buffer, out_buffer;

bool load_sample_customers()
{
    file_t file;
    char *fields[STR_MAX_FIELDS];
    int sample_index = 0;

    buffer_clear(&buffer);

    if (!file_open(sample_file, FILE_READ, &file)) {
        fprintf(stderr, "\nSample customer file not found\n");
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
        str_extract_field(sample_customers[sample_index++], fields[0]);

    }

    // for (int i = 0; i < NUM_SHORTLISTED; i++) {
    //     if (sample_customers[i][0] == '\0') break;
    //     printf("%s\n", sample_customers[i]);
    // }

    file_close(&file);

    return true;
}

bool extract_customer()
{
    file_t file, out_file;
    const int code_index = 1;
    int sample_index = 0;
    size_t len;

    buffer_clear(&buffer);
    buffer_clear(&out_buffer);

    if (!file_open(customer_file, FILE_READ, &file)) {
        fprintf(stderr, "\nCustomer file not found\n");
        return false;
    }

    if (!file_open(o_customer_file, FILE_WRITE, &out_file)) {
        fprintf(stderr, "\nNot able to create customer file\n");
        return false;
    }

    if (!file_read(&file, &buffer, buffer.remaining)) {
        fprintf(stderr, "\nFile open failed\n");
        return false;
    }

    // SKIP the header in first line
    char *line = NULL, *field = NULL;
    size_t line_len = 0, field_len = 0;
    if ( !str_extract_line_field(&buffer, code_index, &line, &line_len, &field, &field_len)) {
        printf("Extracting header failed\n");
        return false;
    }
    if (!buffer_copy(&out_buffer, line, buffer.current - line)) {
        if (!file_write(&out_file, &out_buffer)) {
            fprintf(stderr, "\nFile write failed\n");
        }
    }
    if (!buffer_copy(&out_buffer, NEWLINE, 1)) {
        if (!file_write(&out_file, &out_buffer)) {
            fprintf(stderr, "\nFile write failed\n");
        }
    }

    while (true) {
        char *line = NULL, *field = NULL;
        size_t line_len = 0, field_len = 0;
        if (!str_extract_line_field(&buffer, code_index, &line,
                                    &line_len, &field, &field_len)) {
            buffer_realign(&buffer);
            if (!file_read(&file, &buffer, buffer.remaining)) {
                break;
            }
            continue;
        }

        if (!strncmp(sample_customers[sample_index], field, field_len)) {
            if (!buffer_copy(&out_buffer, line, line_len)) {
                if (!file_write(&out_file, &out_buffer)) {
                    fprintf(stderr, "\nFile write failed\n");
                }
            }
            if (!buffer_copy(&out_buffer, NEWLINE, 1)) {
                if (!file_write(&out_file, &out_buffer)) {
                    fprintf(stderr, "\nFile write failed\n");
                }
            }
            sample_index++;
        }
    }
    if (!file_write(&out_file, &out_buffer)) {
        fprintf(stderr, "\nFile write failed\n");
    }

    file_close(&out_file);
    file_close(&file);

    return true;
}

static bool is_customer_in_sample_data(char *match, size_t match_len)
{
    for (int i = 0; i < NUM_SHORTLISTED; i++) {
        if (sample_customers[i][0] == '\0')
            break;

        if (!strncmp(sample_customers[i], match, match_len)) {
            return true;
        }
    }
    return false;
}

bool extract_invoice()
{
    file_t file, out_file;
    const int code_index = 1;
    size_t len;

    buffer_clear(&buffer);
    buffer_clear(&out_buffer);

    if (!file_open(invoice_file, FILE_READ, &file)) {
        fprintf(stderr, "\nCustomer file not found\n");
        return false;
    }

    if (!file_open(o_invoice_file, FILE_WRITE, &out_file)) {
        fprintf(stderr, "\nNot able to create invoice file\n");
        return false;
    }

    if (!file_read(&file, &buffer, buffer.remaining)) {
        fprintf(stderr, "\nFile open failed\n");
        return false;
    }

    // SKIP the header in first line
    char *line = NULL, *field = NULL;
    size_t line_len = 0, field_len = 0;
    if ( !str_extract_line_field(&buffer, code_index, &line, &line_len, &field, &field_len)) {
        printf("Extracting header failed\n");
        return false;
    }
    if (!buffer_copy(&out_buffer, line, buffer.current - line)) {
        if (!file_write(&out_file, &out_buffer)) {
            fprintf(stderr, "\nFile write failed\n");
        }
    }
    if (!buffer_copy(&out_buffer, NEWLINE, 1)) {
        if (!file_write(&out_file, &out_buffer)) {
            fprintf(stderr, "\nFile write failed\n");
        }
    }

    while (true) {
        char *line = NULL, *field = NULL;
        size_t line_len = 0, field_len = 0;

        if (!str_extract_line_field(&buffer, code_index, &line,
                                    &line_len, &field, &field_len)) {
            buffer_realign(&buffer);
            if (!file_read(&file, &buffer, buffer.remaining)) {
                break;
            }
            continue;
        }

        if (is_customer_in_sample_data(field, field_len)) {
            if (!buffer_copy(&out_buffer, line, line_len)) {
                if (!file_write(&out_file, &out_buffer)) {
                    fprintf(stderr, "\nFile write failed\n");
                }
            }
            if (!buffer_copy(&out_buffer, NEWLINE, 1)) {
                if (!file_write(&out_file, &out_buffer)) {
                    fprintf(stderr, "\nFile write failed\n");
                }
            }
        }
    }
    if (!file_write(&out_file, &buffer)) {
        fprintf(stderr, "\nFile write failed\n");
    }

    file_close(&out_file);
    file_close(&file);

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

    if (!load_sample_customers()) {
        fprintf(stderr, "Generating sample customers failed\n");
        return -1;
    }

    if (!extract_customer()) {
        fprintf(stderr, "Generating shortlist customers failed\n");
        return -1;
    }

    buffer_free(&buffer);
    buffer_free(&out_buffer);
    return 0;
}
