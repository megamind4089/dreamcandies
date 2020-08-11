/******************************************************************************
 *
 * File: invoice_item.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _INVOICE_ITEM_H_
#define _INVOICE_ITEM_H_

#include "main.h"

typedef struct _invoice_item_t {
    char        invoice_code[CODE_SIZE];
    char        item_code[CODE_SIZE];
    float       amount;
    int         quantity;
} invoice_item_t;

#endif // _INVOICE_ITEM_H_


