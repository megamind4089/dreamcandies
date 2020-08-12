from pronounceable import PronounceableWord, generate_word, Pronounceablity, Complexity
import names

no_of_entries = 500000

with open('customer.csv', 'w', encoding='utf-8') as out_file:
    num = 12345
    output = '"CUSTOMER_CODE","FIRSTNAME","LASTNAME"\n'
    out_file.write(output)
    for i in range(no_of_entries):
        output=""
        output += '"CUST' + str(num).zfill(10) + '","' + names.get_first_name() + '","' + names.get_last_name() + '"\n'
        num+=1
        out_file.write(output)
        if i%50000 == 0:
            print(". ")
print("Writing customer File Completed")
