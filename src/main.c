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
#include <stdlib.h>

static const char customer_file[] = "./testdata/customer.csv";
static const char invoice_file[] = "./testdata/invoice.csv";
static const char invoice_item_file[] = "./testdata/invoice_item.csv";
static char _sample_file[] = "testdata/sample.csv";
static char *sample_file = _sample_file;

static const char o_customer_file[] = "./output/customer.csv";
static const char o_invoice_file[] = "./output/invoice.csv";
static const char o_invoice_item_file[] = "./output/invoice_item.csv";

#define BUFFER_SIZE     (10*1024*1024)

static const char NEWLINE[] = "\n";
static char sample_customers[NUM_SHORTLISTED][CODE_SIZE] = {0};
static buffer_t    buffer, out_buffer;

typedef struct _item_t {
    struct _item_t *next;
    char *data;
} item_t;

typedef struct _list_t {
    struct _item_t  *head;
    struct _item_t  *tail;
    size_t len;
} list_t;

list_t  invoice_list = {0};

static bool add_invoice(char *invoice_code, size_t len)
{
    item_t *item = calloc(sizeof(item_t), 1);
    item->data = strndup(invoice_code, len);
    item->next = NULL;

    if (!invoice_list.head)
        invoice_list.head = item;

    if (invoice_list.tail)
        invoice_list.tail->next = item;
    invoice_list.tail = item;

    invoice_list.len++;
    return true;
}

static bool is_invoice_in_sample_data(char *match, size_t match_len)
{
    item_t *item = invoice_list.head;

    while (item) {
        if (!strncmp(item->data, match, match_len)) {
            return true;
        }
        item = item->next;
    }
    return false;
}

static void free_invoice_list()
{
    item_t *item = invoice_list.head, *next;
    while (item) {
        free(item->data);
        next = item->next;
        free(item);
        item = next;
    }
}

static void dump_invoice_list()
{
    item_t *item = invoice_list.head, *next;
    printf("Invoice List:\n");
    while (item) {
        printf("%s\n", item->data);
        item = item->next;
    }
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

bool load_sample_customers()
{
    file_t file;
    char *fields[STR_MAX_FIELDS], *line = NULL;
    size_t line_len = 0, fields_len[STR_MAX_FIELDS] = {0};
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
    if (!str_extract_line_fields(&buffer, &line, &line_len, fields, fields_len)) {
        printf("Extracting header failed\n");
        return false;
    }

    while (true) {

        if (!str_extract_line_fields(&buffer, &line, &line_len, fields, fields_len)) {
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
        strncpy(sample_customers[sample_index++], fields[0], fields_len[0]);

    }

    file_close(&file);

    return true;
}

bool extract_customer()
{
    file_t file, out_file;
    char *fields[STR_MAX_FIELDS], *line = NULL;
    size_t line_len = 0, fields_len[STR_MAX_FIELDS] = {0};
    const int field_idx_cust = 0;
    int sample_index = 0;

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
        fprintf(stderr, "\nCustomer file read failed\n");
        return false;
    }

    // COPY the header in first line
    if (!str_extract_line_fields(&buffer, &line, &line_len, fields, fields_len)) {
        printf("Extracting header failed\n");
        return false;
    }
    if (!buffer_copy(&out_buffer, line, line_len+1)) {
        if (!file_write(&out_file, &out_buffer)) {
            fprintf(stderr, "\nFile write failed\n");
        }
    }

    while (true) {

        if (!str_extract_line_fields(&buffer, &line, &line_len, fields, fields_len)) {
            buffer_realign(&buffer);
            if (!file_read(&file, &buffer, buffer.remaining)) {
                break;
            }
            continue;
        }

        if (!strncmp(sample_customers[sample_index], fields[field_idx_cust], fields_len[field_idx_cust])) {
            if (!buffer_copy(&out_buffer, line, line_len+1)) {
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

bool extract_invoice()
{
    file_t file, out_file;
    char *fields[STR_MAX_FIELDS], *line = NULL;
    size_t line_len = 0, fields_len[STR_MAX_FIELDS] = {0};
    const int field_idx_cust = 0, field_idx_invoice = 1;

    buffer_clear(&buffer);
    buffer_clear(&out_buffer);

    if (!file_open(invoice_file, FILE_READ, &file)) {
        fprintf(stderr, "\nInvoice file not found\n");
        return false;
    }

    if (!file_open(o_invoice_file, FILE_WRITE, &out_file)) {
        fprintf(stderr, "\nNot able to create invoice file\n");
        return false;
    }

    if (!file_read(&file, &buffer, buffer.remaining)) {
        fprintf(stderr, "\nInvoice file read failed\n");
        return false;
    }

    // COPY the header in first line
    if (!str_extract_line_fields(&buffer, &line, &line_len, fields, fields_len)) {
        printf("Extracting header failed\n");
        return false;
    }
    if (!buffer_copy(&out_buffer, line, line_len+1)) {
        if (!file_write(&out_file, &out_buffer)) {
            fprintf(stderr, "\nFile write failed\n");
        }
    }

    while (true) {

        if (!str_extract_line_fields(&buffer, &line, &line_len, fields, fields_len)) {
            buffer_realign(&buffer);
            if (!file_read(&file, &buffer, buffer.remaining)) {
                break;
            }
            continue;
        }

        if (is_customer_in_sample_data(fields[field_idx_cust], fields_len[field_idx_cust])) {

            if (!add_invoice(fields[field_idx_invoice], fields_len[field_idx_invoice])) {
                fprintf(stderr, "Adding invoice to list failed\n");
            }
            if (!buffer_copy(&out_buffer, line, line_len+1)) {
                if (!file_write(&out_file, &out_buffer)) {
                    fprintf(stderr, "\nFile write failed\n");
                }
            }
        }
    }
    if (!file_write(&out_file, &out_buffer)) {
        fprintf(stderr, "\nFile write failed\n");
    }

    file_close(&out_file);
    file_close(&file);

    return true;
}

bool extract_invoice_items()
{
    file_t file, out_file;
    char *fields[STR_MAX_FIELDS], *line = NULL;
    size_t line_len = 0, fields_len[STR_MAX_FIELDS] = {0};
    const int field_idx_invoice = 0;

    buffer_clear(&buffer);
    buffer_clear(&out_buffer);

    if (!file_open(invoice_item_file, FILE_READ, &file)) {
        fprintf(stderr, "\nInvoice file not found\n");
        return false;
    }

    if (!file_open(o_invoice_item_file, FILE_WRITE, &out_file)) {
        fprintf(stderr, "\nNot able to create invoice file\n");
        return false;
    }

    if (!file_read(&file, &buffer, buffer.remaining)) {
        fprintf(stderr, "\nInvoice file read failed\n");
        return false;
    }

    // COPY the header in first line
    if (!str_extract_line_fields(&buffer, &line, &line_len, fields, fields_len)) {
        printf("Extracting header failed\n");
        return false;
    }
    if (!buffer_copy(&out_buffer, line, line_len+1)) {
        if (!file_write(&out_file, &out_buffer)) {
            fprintf(stderr, "\nFile write failed\n");
        }
    }

    while (true) {

        if (!str_extract_line_fields(&buffer, &line, &line_len, fields, fields_len)) {
            buffer_realign(&buffer);
            if (!file_read(&file, &buffer, buffer.remaining)) {
                break;
            }
            continue;
        }

        if (is_invoice_in_sample_data(fields[field_idx_invoice], fields_len[field_idx_invoice])) {

            if (!buffer_copy(&out_buffer, line, line_len+1)) {
                if (!file_write(&out_file, &out_buffer)) {
                    fprintf(stderr, "\nFile write failed\n");
                }
            }
        }
    }
    if (!file_write(&out_file, &out_buffer)) {
        fprintf(stderr, "\nFile write failed\n");
    }

    file_close(&out_file);
    file_close(&file);

    return true;
}

int main(int argc,char* argv[])
{
    if (argc >= 2)
    {
        if (!strcmp(argv[1], "-h")) {
            printf("Usage: %s <sample_file> \n\n", argv[0]);
            printf("If the sample file is not provided, will load default sample file: ");
            printf("\"./testdata/sample.csv\"\n");
            return 0;
        }
        sample_file = argv[1];
    }

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
    printf("Loaded sample customers in memory\n");

    if (!extract_customer()) {
        fprintf(stderr, "Generating shortlist customers failed\n");
        return -1;
    }
    printf("Extracted sample customers\n");

    if (!extract_invoice()) {
        fprintf(stderr, "Generating shortlist customers failed\n");
        return -1;
    }
    printf("Extracted invoice of sample customers\n");
    // dump_invoice_list();

    if (!extract_invoice_items()) {
        fprintf(stderr, "Generating shortlist customers failed\n");
        return -1;
    }
    printf("Extracted invoice items of sample customers\n");

    free_invoice_list();
    buffer_free(&buffer);
    buffer_free(&out_buffer);

    return 0;
}
