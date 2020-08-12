from random import randrange

no_of_entries = 1000

with open('sample.csv', 'w', encoding='utf-8') as out_file:
    print("Writing customer_sample File")
    num = 12345
    num_range = 1000
    output = '"CUSTOMER_CODE"\n'
    out_file.write(output)
    for i in range(no_of_entries):
        output=""
        output += '"CUST' + str(randrange(num, num + num_range)).zfill(10) + '"\n'
        num = num + 100
        num_range = num_range + 100
        out_file.write(output)
print("Writing customer_sample File Completed")
