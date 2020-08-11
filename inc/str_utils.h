/******************************************************************************
 *
 * File: str_utils.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _STR_UTILS_H_
#define _STR_UTILS_H_

#include "buffer.h"
#include <string.h>
#include <stdbool.h>

#define STR_MAX_FIELDS      10

bool str_extract_line_fields(buffer_t *buf, char *fields[]);

bool str_extract_field(char *dest, const char *src);

#endif // _STR_UTILS_H_

