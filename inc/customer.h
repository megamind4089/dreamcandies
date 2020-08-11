/******************************************************************************
 *
 * File: customer.h
 *
 * Author: Mariappan Ramasamy
 *
 *****************************************************************************/

#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

typedef struct _customer_t {
    char        customer_code[30];
    char        first_name[100];
    char        last_name[100];
} customer_t;

#endif // _CUSTOMER_H_
