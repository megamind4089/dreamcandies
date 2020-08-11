/******************************************************************************
 *
 * File: str_utils.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _STR_UTILS_H_
#define _STR_UTILS_H_

#include <string.h>
#include <stdbool.h>

#define STR_MAX_FIELDS      10

bool str_get_line(char *buf, size_t size, char *fields[], char **next_line);

#endif // _STR_UTILS_H_

