/******************************************************************************
 *
 * File: invoice_item.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _INVOICE_ITEM_H_
#define _INVOICE_ITEM_H_

typedef struct _invoice_item_t {
    char        invoice_code[30];
    char        item_code[30];
    float       amount;
    int         quantity;
} invoice_item_t;

#endif // _INVOICE_ITEM_H_


