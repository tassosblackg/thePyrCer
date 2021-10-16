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
import os
import argparse
from pycparser import parse_file
import pycparser as pyc

removeAble = ["#"]
new_file_sufix = "_after.c"
path_2edit_files = "C_code_inputs/"
path2output_results = "Analytics_results_in_txt/"
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
                    arg_type = param_decl.type
                    pointer_class = 0  # counter single, double etc pointer

                    # while argument type is pointer(single,double,etc)
                    while isinstance(arg_type, pyc.c_ast.PtrDecl):
                        pointer_class += 1
                        arg_type = arg_type.type  # get next type
                        if isinstance(arg_type, pyc.c_ast.TypeDecl):
                            break
                    if pointer_class >= 1:
                        params_namesNtypes.append(
                            (
                                str(pointer_class) + "-Ptr-" + arg_type.type.names[0],
                                param_decl.name,
                            )
                        )
                    else:
                        params_namesNtypes.append(
                            (arg_type.type.names[0], param_decl.name)
                        )
            func_return_datatype = function_decl.type.type
            return_pointer_class = 0
            while isinstance(func_return_datatype, pyc.c_ast.PtrDecl):
                return_pointer_class += 1
                func_return_datatype = func_return_datatype.type
                if isinstance(func_return_datatype, pyc.c_ast.TypeDecl):
                    break
            print(
                str(return_pointer_class) + "-PTR-" + func_return_datatype.type.names[0]
            )
            # function_return_type = function_decl.type.type.type.names[0]
            # # insert into a dict
            # functions_defined[function_decl.name] = (
            #     function_return_type,
            #     params_namesNtypes,
            # )
            # search and count function calls
            count_function_calls(ext_decl)


def count_function_calls(ext_decl):
    """
    Find the function calls per function name
    Creates a dictionary with function's name as a key and value its times of appearence

    args:
    -------


    """

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
    h1 = "Functions Defined: "
    h2 = "Function Calls : "
    format_info = "FORMAT => { Function Name : (function_return_type, [ (argument1_data_type,argument1_name), ]), }"
    path2save = path2output_results + os.path.basename(filename)

    with open(path2save[:-2] + "_analytics.txt", "w") as f:
        f.write("# File: " + filename + "\n")
        f.write("-" * 10 * len(filename) + "\n")
        f.write(h1 + "\n")
        f.write(format_info + "\n")
        f.write("-" * 10 * len(format_info))
        for index_i, (func_name, func_details) in enumerate(func_def.items()):
            f.write(
                "\n  ("
                + str(index_i + 1)
                + "). "
                + str(func_name)
                + str(func_details)
                + "\n"
            )
        f.write("*" * 10 * len(format_info))
        f.write("\n" + h2 + "\n")
        for index_j, (func_name, val) in enumerate(func_calls.items()):
            f.write(
                "\n  ("
                + str(index_j + 1)
                + "). "
                + str(func_name)
                + "()"
                + ", num of calls = "
                + str(val)
            )
        f.write("\n \n \n" + "That's all folks!" + "\n" + "END")


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
    filename = args.input_file
    new_file = filename[:-2] + new_file_sufix

    # edited file path
    new_file_path = path_2edit_files + os.path.basename(new_file)

    remove_include(filename, new_file_path)
    # parse the C file
    ast = pyc.parse_file(
        new_file_path,
        use_cpp=True,
        cpp_path="gcc",
        cpp_args=["-std=c99", "-E", r"-Iutils/fake_libc_include"],
    )
    # ast.show(showcoord=True)

    find_def_functions(ast)
    #
    # if args.output == "f":
    #     save_stats(filename, functions_defined, functions_called)
    # else:
    #     print(
    #         "\n --------------------------------------- | Defined Functions | ----------------------------------------------------- :\n",
    #     )
    #     print("-" * 130)
    #     print(
    #         "\n |> Format= { function_name: ( return_type, [(arg1_data_type,arg1_name),(..,..)] ) } <|\n"
    #     )
    #     print("-" * 130)
    #     print("\n", functions_defined)
    #     print(
    #         "\n\n -------------------------------------- | Called Functions | ----------------------------------------------------- :\n",
    #     )
    #     print("-" * 130)
    #     print("\n |> Format= { function_name: #appearences } <|\n")
    #     print("-" * 130)
    #     print("Functions Called -> \n", functions_called)
