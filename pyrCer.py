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

import argparse
import sys
from pycparser import parse_file
import pycparser as pyc

removeAble = ["#", "/*", "//"]
new_file_sufix = "_after.c"
path_2edit_files = "C_code_inputs/"
functions_defined = {}
functions_called = {}


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


def find_def_functions(ast_data):
    """
    Search inside the AST for the defined functions

    args:
    ------
    - ast_data: The parsed AST from the .c file

    Creates/Update a dictionary with function's name, return type, arguments and arguments type
    e.g. functions_defined = {'function_name': (return_type, [ (arg1_type,arg1_name),] ) }
    """
    for ext_decl in ast.ext:
        if isinstance(ext_decl, pyc.c_ast.FuncDef):
            function_decl = ext_decl.decl  # function declaration
            function_args = function_decl.type.args
            params_namesNtypes = []
            if function_args is not None:
                for param_decl in function_decl.type.args.params:
                    # append a tuple (arg_data_type,arg_name)
                    params_namesNtypes.append(
                        (param_decl.type.type.names[0], param_decl.name)
                    )
            function_return_type = function_decl.type.type.type.names[0]
            # insert into a dict
            functions_defined[function_decl.name] = (
                function_return_type,
                params_namesNtypes,
            )
        # elif isinstance(ast.ext[i], pyc.c_ast.Typedef):
        #     pass


def function_calls(ast_data):
    """
    Find the function calls per function name
    Creates a dictionary with function's name as a key and value its times of appearence

    args:
    -------


    """
    # print(len(ast_data.ext))
    for ext_decl in ast_data.ext:
        # print(dir(i.body.coord))
        if isinstance(ext_decl, pyc.c_ast.FuncDef):
            function_decl = ext_decl.decl  # function declaration
            for b_item in ext_decl.body.block_items:
                if isinstance(b_item, pyc.c_ast.FuncCall):
                    func_call_id = b_item.name
                    if func_call_id.name in functions_called:
                        functions_called[func_call_id.name] += 1
                    else:
                        functions_called[func_call_id.name] = 1


def save_stats(filename, func_def, func_calls):
    """
    Writes all the info in .txt format file

    args:
    ------
    - filename: the actual .c file name string
    - func_def: the dictionary with the defined functions
    - func_calls: the function calls and counter
    """
    with open(filename[:-2] + "_analytics.txt", "w") as f:
        f.write("# File: " + filename)
        f.write("-" * 4 * len(filename))
        f.write("Functions Defined: ")
        f.write(
            "{ Function Name : (function_return_type, [ (argument1_data_type,argument1_name), ]), }"
        )
        for func_name, fun_details in func_def.items():
            f.write(str(func_name) + str(func_details))
        f.write("\n*")
        f.write("Function Calls : ")
        for func_name, val in func_calls.items():
            f.write(str(func_name) + "num of calls = " + str(val))


if __name__ == "__main__":
    menu_parser = argparse.ArgumentParser(
        prog="c_code_parser",
        description="Python program to parse C code and print statistics",
    )
    menu_parser.add_argument("input_file", type=str, help=" give .c file as input")
    menu_parser.add_argument(
        "-o",
        "--output",
        type=str,
        help="optional argument print output to a file (:f) or to console(:empty). Default print to console",
        default="c",
    )
    args = menu_parser.parse_args()
    print(args)
    # if len() > 2:
    filename = args.input_file
    new_file = filename[:-2] + new_file_sufix
    # edited file path
    new_file_path = path_2edit_files + new_file
    remove_include(filename, new_file_path)
    # parse the C file
    ast = pyc.parse_file(
        new_file_path,
        use_cpp=True,
        cpp_path="gcc",
        cpp_args=["-std=c99", "-E", r"-Iutils/fake_libc_include"],
    )

    find_def_functions(ast)
    function_calls(ast)
    print(functions_called)
    # if args.output == "f":
    #     # save_stats(func_def, func_calls)
    #     print(args.output)
    # else:
    #     print(
    #         "\n -------------------------| Defined Functions | ----------------------------------------------------- :\n",
    #     )
    #     print("-" * 130)
    #     print(
    #         "\n |> Format= { function_name: ( return_type, [(arg1_data_type,arg1_name),(..,..)] ) } <|\n"
    #     )
    #     print("-" * 130)
    #     print("\n", func_def)
    #     # print("Function Calls: \n", func_calls)
