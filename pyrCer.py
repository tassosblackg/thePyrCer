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

addAble = """typedef struct {
char *fpos; /* Current position of file pointer (absolute address) */
void *base; /* Pointer to the base of the file */
unsigned short handle; /* File handle */
short flags; /* Flags (see FileFlags) */
short unget; /* 1-byte buffer for ungetc (b15=1 if non-empty) */
unsigned long alloc; /* Number of currently allocated bytes for the file */
unsigned short buffincrement; /* Number of bytes allocated at once */
} FILE;"""
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
            output.write(addAble + "\n")
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
            # Traverse function's argument list
            if function_args is not None:
                for param_decl in function_decl.type.args.params:
                    # Argument's DataType Pointer or Not
                    pointer_class, arg_data_type = detect_pointer_data_types(
                        param_decl.type
                    )
                    # Argument's DataType string
                    arg_data_type_str = (
                        str(pointer_class) + "-Ptr-" + arg_data_type.type.names[0]
                        if pointer_class >= 1
                        else arg_data_type.type.names[0]
                    )

                    # append a tuple (arg_data_type,arg_name)
                    params_namesNtypes.append((arg_data_type_str, param_decl.name))

            # Function's Return DataType Pointer or Not
            return_pointer_class, func_return_datatype = detect_pointer_data_types(
                function_decl.type.type
            )
            # Function's Return DataType string
            func_return_datatype_str = (
                str(return_pointer_class) + "-Ptr-" + func_return_datatype.type.names[0]
                if return_pointer_class >= 1
                else func_return_datatype.type.names[0]
            )

            # insert function into a dict
            functions_defined[function_decl.name] = (
                func_return_datatype_str,
                params_namesNtypes,
            )

            # search and count function calls
            count_function_calls(ext_decl)


def count_function_calls(ext_decl):
    """
    Find the function calls per function name
    Creates a dictionary with function's name as a key and value its times of appearence

    args:
    -------
    - ext_decl : AST ext object from pycparser

    """

    for b_item in ext_decl.body.block_items:
        if isinstance(b_item, pyc.c_ast.FuncCall):
            func_call_id = b_item.name
            if func_call_id.name in functions_called:
                functions_called[func_call_id.name] += 1
            else:
                functions_called[func_call_id.name] = 1


def detect_pointer_data_types(ast_dtype):
    """
    A function that detect if data type in AST is pointer, keep moving down the AST until reaching TypeDecl object

    args:
    ------
    - ast_dtype: the AST level where type isinstance of PtrDecl

    returns:
    - pointer_class:    the size of pointer (#times seeing PtrDecl, till TypeDecl hits).
    - datatype: An TypeDecl object from AST (end condition).
    """
    datatype = ast_dtype
    pointer_class = 0
    while isinstance(datatype, pyc.c_ast.PtrDecl):
        pointer_class += 1
        datatype = datatype.type
        if isinstance(datatype, pyc.c_ast.TypeDecl):
            break

    return pointer_class, datatype


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

    if args.output == "f":
        save_stats(filename, functions_defined, functions_called)
    else:
        print(
            "\n --------------------------------------- | Defined Functions | ----------------------------------------------------- :\n",
        )
        print("-" * 130)
        print(
            "\n |> Format= { function_name: ( return_type, [(arg1_data_type,arg1_name),(..,..)] ) } <|\n"
        )
        print("-" * 130)
        print("\n", functions_defined)
        print(
            "\n\n -------------------------------------- | Called Functions | ----------------------------------------------------- :\n",
        )
        print("-" * 130)
        print("\n |> Format= { function_name: #appearences } <|\n")
        print("-" * 130)
        print("Functions Called -> \n", functions_called)
