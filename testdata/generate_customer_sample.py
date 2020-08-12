from random import randrange

no_of_entries = 1000

with open('customer_sample.csv', 'w', encoding='utf-8') as out_file:
    print("Writing customer_sample File")
    num = 12345
    output = '"CUSTOMER_CODE"\n'
    out_file.write(output)
    for i in range(no_of_entries):
        output=""
        output += '"CUST' + str(randrange(num, num + 500000)).zfill(10) + '"\n'
        out_file.write(output)
print("Writing customer_sample File Completed")
