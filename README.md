# thePyrCer
Python code to parse C code and extract useful statistics
As part of reciprocal scholarship requirement for Data Structures Class, *University of Macedonia 2021*.

## Description:
Edit .c files and removes headers libraries (`#include`,`#define`,etc).
Then use pycparser module for parsing C files and store them into an AST format.
Where AST stands for Abstract Syntax Tree. After explore inside the AST and extract several interesting statistics like functions defined, number of calls per function, etc.

## Execution:

###### Option-1:
`Prints output to console.`
> python3 pyrCer.py code_file.c


###### Option-2:
`Store Results in` *`.txt`* `file with name` ***`code_file_analytics.txt`***
> python3 pyrCer.py code_file.c --output f

## Repo Structure:
Name                 | Description
 :---:                | :---
 [C_code_examples]                              | Directory with C code examples to test on.
 [C_code_inputs]                                | Directory after #includes are removed.
 [ff.c]                                         | An example C code.
 [ff_analytics.txt]                             | An output file example with all the results.
 [pyrCer.py]                                    | The actual program.


 [C_code_examples]:                       https://github.com/tassosblackg/thePyrCer/tree/main/C_code_examples
 [C_code_inputs]:                  https://github.com/tassosblackg/thePyrCer/tree/main/C_code_inputs
 [ff.c]:            https://github.com/tassosblackg/thePyrCer/blob/main/ff.c
 [ff_analytics.txt]:           https://github.com/tassosblackg/thePyrCer/blob/main/ff_analytics.txt
 [pyrCer.py]:                    https://github.com/tassosblackg/thePyrCer/blob/main/pyrCer.py

## Info:

 - [X] Program Developed based on https://github.com/eliben/pycparser !

 - [X] Python3.9

 ## Contact:
 `@tassosblackg`
