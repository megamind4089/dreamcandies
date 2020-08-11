/******************************************************************************
 *
 * File: customer.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "main.h"

typedef struct _customer_t {
    char        customer_code[CODE_SIZE];
    char        first_name[NAME_SIZE];
    char        last_name[NAME_SIZE];
} customer_t;

#endif // _CUSTOMER_H_
