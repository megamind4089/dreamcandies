/******************************************************************************
 *
 * File: invoice.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _INVOICE_H_
#define _INVOICE_H_

#include "main.h"

typedef struct _invoice_t {
    char        customer_code[CODE_SIZE];
    char        invoice_code[CODE_SIZE];
    float       amount;
    char        date[DATE_SIZE];
} invoice_t;

#endif // _INVOICE_H_

