/******************************************************************************
 *
 * File: invoice.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _INVOICE_H_
#define _INVOICE_H_

typedef struct _invoice_t {
    char        customer_code[30];
    char        invoice_code[30];
    float       amount;
    char        date[12];
} invoice_t;

#endif // _INVOICE_H_

