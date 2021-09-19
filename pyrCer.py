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
import pycparser as pyc

removeAble = ["#", "/*", "//"]
new_file_sufix = "_after.c"
path_2edit_files = "C_code_inputs/"
functions_defined = {}


def remove_include(file2read, file2write):
    """
    args:
    ------
    - file2read: A .c file to read from
    - file2write: The new .c file created after removing #include,define etc

    """
    with open(file2read, "r") as f:
        with open(file2write, "w") as output:
            for line in f:
                if line[0] not in removeAble:
                    output.write(line)


def extract_stats(ast_data):
    for ext_decl in ast.ext:
        if isinstance(ext_decl, pyc.c_ast.FuncDef):
            function_decl = ext_decl.decl  # function declaration
            function_args = function_decl.type.args
            params_namesNtypes = []
            if function_args is not None:
                for param_decl in function_decl.type.args.params:
                    # print(type(param_decl), dir(param_decl))
                    params_namesNtypes.append(
                        (param_decl.type.type.names[0], param_decl.name)
                    )
            functions_defined[function_decl.name] = params_namesNtypes
        # elif isinstance(ast.ext[i], pyc.c_ast.Typedef):
        #     pass
        print(functions_defined)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
        new_file = filename[:-2] + new_file_sufix
        print(filename, new_file)
        remove_include(filename, path_2edit_files + new_file)
        # parse the C file
        ast = pyc.parse_file(
            new_file,
            use_cpp=True,
            cpp_path="gcc",
            cpp_args=["-std=c99", "-E", r"-Iutils/fake_libc_include"],
        )
        ast.show(showcoord=True)
        print("AST type {}".format(type(ast)))
        extract_stats(ast)
        # print(ast.ext[0].decl.name)  # get fumctions' name
