"""
-> Info:
-------- Data Structure Courses UOM 2021 --------------------
|    Create parsing C code tool                             |
|    Extract Useful Statistics based on a code sample       |
|                                                           |
_____________________________________________________________
|                Author: @tassosblackg                      |
_____________________________________________________________
-> Appendix :
-----------------------------------------------------------------------------
| Developped used : @eliben/pycparser                                       |
| Examples explore structure:                                               |
| https://github.com/eliben/pycparser/blob/master/examples/explore_ast.py   |
| Children nodes Types of AST:                                              |
| https://github.com/eliben/pycparser/blob/master/pycparser/_c_ast.cfg      |
-----------------------------------------------------------------------------
"""


import sys
from pycparser import parse_file

removeAble = ["#", "/*", "//"]
new_file_sufix = "_after.c"


def remove_include(file2read, file2write):
    """
    args:
    ------
    - file2read: A .c file to read from
    - file2write: The new .c file created after removing #include,define etc

    """
    with open(file2edit, "r") as f:
        with open(file2write, "w") as output:
            for line in f:
                if line[0] not in removeAble:
                    output.write(line)


def convert_AST_2json():
    pass


if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
        new_file = file2edit[:-2] + new_file_name
        remove_include(filename, new_file)
