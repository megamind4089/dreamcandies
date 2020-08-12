DreamCandies

This repo contains solution to the dreamcandies problem.

Design choices:

Based on the requirements, this tool has been designed to work with only strings
and no parsing of values is done to improve the efficiency.


The following assumptions has been made:
* Customer code is present in increment order in customer.csv and sample.csv
* Invoice Code is again in incremental order

Based on the above assumption, had some optimisation in lookup of sample customers.
If the assumption is not true, we need to check for the entire sample data against each entry in customer.csv

And the invoice implements the full search instead of the above optimisation.

To efficiently use resources, a buffer of type buffer_t is used to read and write data from files
instead of reading full files.
The buffer size is compile time configurable and can be adjusted based on the availability of resources.

The entire tool reads the input file only once and output it to a file directly without parsing or calculating strlen.

Since the strutils extracts all the fields from the row, this can be extended to parse the individual fields
based on the future requirements.


TestData:
Test data can be generated using the scripts inside the directory 'testdata'.
The generated test data should be inside this 'testdata' directory.

The sample file path can be given as either the command line argument or it will use the default file

Improvements:
Can add test cases for boundary condition checks.

