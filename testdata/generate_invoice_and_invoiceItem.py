import random
from datetime import timedelta, datetime
from random import randrange
from pronounceable import PronounceableWord
import numpy as np, numpy.random


def random_date(start, end):
    delta = end - start
    int_delta = (delta.days * 24 * 60 * 60) + delta.seconds
    random_second = randrange(int_delta)
    return start + timedelta(seconds=random_second)


d1 = datetime.strptime('1-Jan-2000', '%d-%b-%Y')
d2 = datetime.strptime('11-Aug-2020', '%d-%b-%Y')
no_of_entries = 500000
num = 12345
invoicenum = 0
num_of_invoices = randrange(1, 4)
num_of_items = randrange(2,10)
output = '"CUSTOMER_CODE","INVOICE_CODE","AMOUNT","DATE"\n'
invoiceoutput = '"INVOICE_CODE","ITEM_CODE","AMOUNT","QUANTITY"\n'

with open('invoice.csv', 'w', encoding='utf-8') as out_file, open('invoice_item.csv', 'w',
                                                                  encoding='utf-8') as item_file:
    print("Writing invoice File")
    out_file.write(output)
    item_file.write(invoiceoutput)
    for i in range(no_of_entries):
        output = ""
        num_of_invoices = randrange(1, 4)
        while num_of_invoices != 0:
            invoiceoutput = ""
            invoicenum += 1
            invoiceamount = round(random.uniform(50.00, 1000.00), 2)
            output += '"CUST' + str(randrange(num, num + no_of_entries)).zfill(10) + '","' + str(invoicenum).zfill(
                7) + '","' + \
                      str(invoiceamount) + '","' + \
                      str(random_date(d1, d2).strftime('%d-%b-%Y')) + '"\n'
            num_of_items = randrange(2,10)

            a = np.random.dirichlet(np.ones(num_of_items), size=1)
            a *= invoiceamount
            while num_of_items !=0:
                itemamount = round(a[0][num_of_items-1], 2)
                invoiceoutput += '"' + str(invoicenum).zfill(7) + '","' + PronounceableWord().length(4, 7) + '","' + \
                             str(itemamount) + '","' + str(randrange(1, 10)) + '"\n'
                invoiceamount-=itemamount
                num_of_items-=1
            num_of_invoices -= 1
            item_file.write(invoiceoutput)
        out_file.write(output)
        if i%10000 ==0:
            print(".",end=" ")
print(invoicenum)
print("Writing invoice File Completed")
