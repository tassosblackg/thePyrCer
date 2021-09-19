# thePyrCer
Python code to parse C code and extract useful statistics
As part of reciprocal scholarship requirement for Data Structures Class, *University of Macedonia 2021*.

## Description:
Edit .c files and removes headers libraries (`#include`,`#define`,etc).
Then use pycparser module for parsing C files and store them into an AST format.
Where AST stands for Abstract Syntax Tree. After explore inside the AST and extract several interesting statistics like functions defined, number of calls per function, etc.

## Info:

 - [X] Program Developed based on https://github.com/eliben/pycparser !

 - [X] Python3.9
